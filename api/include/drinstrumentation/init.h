#pragma once

#include <memory>

#include "dr_api.h"
#include "drcallstack.h"
#include "drinstrumentation/instrumentation/instrumentation.h"
#include "drmgr.h"
#include "droption.h"
#include "drsyms.h"
#include "drwrap.h"

namespace drinstrumentation {

static std::shared_ptr<instrumentation::Instrumentation> ptr;

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

  ptr->insert_instrumentation_point(symbol::Symbol{
      info->file, (char*)data, info->line, info->line_offs, info->start_offs,
      info->end_offs, info->name, demangled_name, full_demangle_name});

  return true;
}

static void module_load(void* drcontext, const module_data_t* info,
                        bool loaded) {
  drsym_enumerate_symbols_ex(
      info->full_path, enumerate_symbols, sizeof(drsym_info_t),
      (void*)info->names.module_name, DRSYM_LEAVE_MANGLED);
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