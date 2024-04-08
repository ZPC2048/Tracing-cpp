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

    std::string *func_name = new std::string(insertPoint.full_demangled_name);
    drwrap_wrap_ex(insertPoint.module_start + insertPoint.start_offs,
                   prehookFunc, posthookFunc, func_name, 0);
  }
}

void Instrumentation::prehookFunc(void *wrapcxt, void **user_data) {
  // DEBUG
  // dr_fprintf(STDERR, "get arg %d: %\n");
  std::string func_name = *(std::string *)*user_data;

  std::shared_ptr<drinstrumentation::trace::Span> span =
      drinstrumentation::trace::Provider::getTracerProvider()
          ->getTracer("default")
          ->startSpan(func_name);

  if (span->getContext().getTraceState()->empty()) {
    span->getContext().getTraceState()->set("serviceName", "default_service");
    span->getContext().getTraceState()->set("ipv4", "127.0.0.1");
  }

  *user_data = new drinstrumentation::trace::Scope{span};

  // DEBUG
  // dr_fprintf(STDERR, "prehookFunc End\n");
}

void Instrumentation::posthookFunc(void *wrapcxt, void *user_data) {
  // DEBUG
  // dr_fprintf(STDERR, "posthookFunc Begin\n");

  delete (drinstrumentation::trace::Scope *)user_data;

  // DEBUG
  // dr_fprintf(STDERR, "posthookFunc End\n");
}

}  // namespace instrumentation
}  // namespace sdk
}  // namespace drinstrumentation