#include "sdk/drinstrumentation/instrumentation/instrumentation.h"

namespace drinstrumentation {
namespace sdk {
namespace instrumentation {

Instrumentation::Instrumentation(
    std::shared_ptr<drinstrumentation::checker::Checker> checker)
    : checker_(checker) {}

void Instrumentation::tryToInsertTracerInto(symbol::Symbol insertPoint) {
  // DEBUG
  // int fd = dr_open_file("ls_sym.txt", DR_FILE_WRITE_APPEND);
  // dr_fprintf(fd, "file name: %s module name: %s demangle name: %s\n",
  //            insertPoint.file_name.data(), insertPoint.module_name.data(),
  //            insertPoint.demangled_name.data());

  if (checker_->shouldInstrumentSymbol(insertPoint)) {
    // DEBUG
    // dr_fprintf(STDERR, "insertPoint: %s", insertPoint.demangled_name.data());

    drwrap_wrap_ex(insertPoint.module_start + insertPoint.start_offs,
                   prehookFunc, posthookFunc, nullptr, 0);
  }
}

void Instrumentation::prehookFunc(void *wrapcxt, void **user_data) {
  // DEBUG
  dr_fprintf(STDERR, "prehookFunc Begin\n");

  *user_data = new drinstrumentation::trace::Scope{
      drinstrumentation::trace::Provider::getTracerProvider()
          ->getTracer("default")
          ->startSpan("default")};
          
  // DEBUG
  dr_fprintf(STDERR, "prehookFunc End\n");
}

void Instrumentation::posthookFunc(void *wrapcxt, void *user_data) {
  // DEBUG
  dr_fprintf(STDERR, "posthookFunc Begin\n");

  delete (drinstrumentation::trace::Scope *)user_data;

  // DEBUG
  dr_fprintf(STDERR, "posthookFunc End\n");
}

}  // namespace instrumentation
}  // namespace sdk
}  // namespace drinstrumentation