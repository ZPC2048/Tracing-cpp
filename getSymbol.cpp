#include "dr_api.h"
#include "drmgr.h"
#include "drsyms.h"
#include "droption.h"
#include <cstdio>
#include <cstring>
#include <string>

using std::string;
using dynamorio::droption::DROPTION_SCOPE_CLIENT;
using dynamorio::droption::droption_parser_t;
using dynamorio::droption::droption_t;

static droption_t<string> g_output_file(DROPTION_SCOPE_CLIENT, "output file", R"(./output_file.txt)", "output file location", "output file location");
static int g_output_file_fd;

static bool
enumerate_symbols(drsym_info_t *info, drsym_error_t status, void *data) {
  if (info->name == nullptr) return true;

  // mangle name
  dr_fprintf(g_output_file_fd, "\tmangle name: %s\n", info->name);

  // demangle name without template type
  char newName[200];
  drsym_demangle_symbol(newName, 200, info->name, DRSYM_DEMANGLE);
  dr_fprintf(g_output_file_fd, "\tdemangle name: %s\n", newName);

  // full demangle name
  drsym_demangle_symbol(newName, 200, info->name, DRSYM_DEMANGLE_FULL);
  dr_fprintf(g_output_file_fd, "\tfull demangle name: %s\n\n", newName);

  return true;
}

static void
module_load(void* drcontext, const module_data_t* info, bool loaded) {
  dr_fprintf(g_output_file_fd, "file name: %s module name: %s\n\n", info->names.file_name == nullptr ? "NULL" : info->names.file_name,
                                                                    info->names.module_name == nullptr ? "NULL" : info->names.module_name);
  drsym_enumerate_symbols_ex(info->full_path, enumerate_symbols, sizeof(drsym_info_t), nullptr, DRSYM_LEAVE_MANGLED);
}

DR_EXPORT void
dr_client_main(client_id_t id, int argc, const char *argv[])
{
  drsym_init(0);
  drmgr_init();

  std::string parse_err;
  int last_index;
  if (!droption_parser_t::parse_argv(DROPTION_SCOPE_CLIENT, argc, argv, &parse_err, &last_index)) {
    dr_fprintf(STDERR, "Usage error: %s\n", parse_err.c_str());
    dr_abort();
  }

  g_output_file_fd = dr_open_file(g_output_file.get_value().c_str(), DR_FILE_WRITE_OVERWRITE);
  if (g_output_file_fd == INVALID_FILE) {
    dr_fprintf(STDERR, "file %s open failed\n", g_output_file.get_value().c_str());
    dr_abort();
  }

  drmgr_register_module_load_event(module_load);
}