#pragma once

#include <memory>

#include "dr_api.h"
#include "drinstrumentation/defines.h"
#include "drinstrumentation/instrumentation/instrumentation.h"
#include "drmgr.h"
#include "drsyms.h"
#include "drwrap.h"

namespace drinstrumentation {

static std::shared_ptr<instrumentation::Instrumentation> ptr;

struct PassToEnumerateSymbols {
  const char* module_name;
  pointer start_pos;
};

static bool enumerate_symbols(drsym_info_t* info, drsym_error_t status,
                              void* data) {
  if (info->name == nullptr) return true;

  static char demangled_name[500];
  static char full_demangle_name[500];
  // demangle name without template type
  drsym_demangle_symbol(demangled_name, 500, info->name, DRSYM_DEMANGLE);
  // full demangle name
  drsym_demangle_symbol(full_demangle_name, 500, info->name,
                        DRSYM_DEMANGLE_FULL);

  PassToEnumerateSymbols* module_data = (PassToEnumerateSymbols*)data;
  ptr->tryToInsertTracerInto(symbol::Symbol{
      info->file ? info->file : "",
      module_data->module_name ? module_data->module_name : "", info->line,
      info->line_offs, module_data->start_pos, info->start_offs, info->end_offs,
      info->name ? info->name : "", demangled_name, full_demangle_name});

  return true;
}

static void module_load(void* drcontext, const module_data_t* info,
                        bool loaded) {
  PassToEnumerateSymbols data{info->names.module_name, info->start};
  drsym_enumerate_symbols_ex(info->full_path, enumerate_symbols,
                             sizeof(drsym_info_t), (void*)&data,
                             DRSYM_LEAVE_MANGLED);
}

bool init_client(
    std::shared_ptr<instrumentation::Instrumentation> instrumentation) {
#ifndef X64
  static_assert(false, "only support x64");
#endif
  if (drsym_init(0) != DRSYM_SUCCESS || !drmgr_init() || !drwrap_init() ||
      !drmgr_register_module_load_event(module_load)) {
    dr_abort();
    return false;
  }
  ptr = instrumentation;
  return true;
}

}  // namespace drinstrumentation