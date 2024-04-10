#include "sdk/drinstrumentation/instrumentation/instrumentation.h"
#include "sdk/drinstrumentation/trace/span.h"

namespace drinstrumentation {
namespace sdk {
namespace instrumentation {

Instrumentation::Instrumentation(
    std::shared_ptr<drinstrumentation::checker::Checker> checker)
    : checker_(checker) {}

static drinstrumentation::trace::Scope *public_scope = nullptr;

struct DataBetweenPreAndPost {
  std::string func_name;
  drinstrumentation::trace::Scope *scope;
  drinstrumentation::trace::Scope **public_scope;
};

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
                   prehookFunc, posthookFunc,
                   new DataBetweenPreAndPost{insertPoint.full_demangled_name,
                                             nullptr, &public_scope},
                   0);
  }
}

void Instrumentation::prehookFunc(void *wrapcxt, void **user_data) {
  // DEBUG
  // dr_fprintf(STDERR, "get arg %d: %\n");
  DataBetweenPreAndPost* data = (DataBetweenPreAndPost*)*user_data;
  std::string func_name = data->func_name;

  if (func_name.find("Post") != std::string::npos) {
    std::shared_ptr<drinstrumentation::trace::Span> span =
        drinstrumentation::trace::Provider::getTracerProvider()
            ->getTracer("default")
            ->startSpan(func_name);

    std::string *origin = new std::string((char *)drwrap_get_arg(wrapcxt, 1));
    int pos = origin->find("\r\n\r\n");
    origin->insert(
        pos, "\r\nParentId: " + span->getContext().getSpanId().toLowerBase16());
    origin->insert(
        pos, "\r\nTraceId: " + span->getContext().getTraceId().toLowerBase16());
    drwrap_set_arg(wrapcxt, 1, (void *)origin->data());
    drwrap_set_arg(wrapcxt, 2, (void *)origin->length());

    span->getContext().getTraceState()->set("serviceName", "client_service");
    span->getContext().getTraceState()->set("ipv4", "127.0.0.1");

    if (span->getContext().getTraceState()->empty()) {
      span->getContext().getTraceState()->set("serviceName", "default_service");
      span->getContext().getTraceState()->set("ipv4", "127.0.0.1");
    }

    data->scope = new drinstrumentation::trace::Scope{span};
  } else if (func_name.find("receive") != std::string::npos) {
    std::shared_ptr<drinstrumentation::trace::Span> span = new drinstrumentation::sdk::trace::Span(drinstrumentation::trace::Provider::getTracerProvider()
            ->getTracer("default"), "http client", drinstrumentation::trace::SpanId{}, std::unique_ptr<>);
    return;
  } else if (func_name.find("response") != std::string::npos) {
    return;
  }

  // DEBUG
  // dr_fprintf(STDERR, "prehookFunc End\n");
}

void Instrumentation::posthookFunc(void *wrapcxt, void *user_data) {
  // DEBUG
  // dr_fprintf(STDERR, "posthookFunc Begin\n");

  DataBetweenPreAndPost* data = (DataBetweenPreAndPost*)user_data;
  std::string func_name = data->func_name;

  if (func_name.find("Post") != std::string::npos) {
    delete data->scope;
    data->scope = nullptr;
  } else if (func_name.find("receive") != std::string::npos) {
    
  } else if (func_name.find("response") != std::string::npos) {
    delete *(data->public_scope);
    *(data->public_scope) = nullptr;
  }

  // DEBUG
  // dr_fprintf(STDERR, "posthookFunc End\n");
}

}  // namespace instrumentation
}  // namespace sdk
}  // namespace drinstrumentation