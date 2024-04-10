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
    drwrap_wrap_ex(insertPoint.module_start + insertPoint.start_offs,
                   prehookFunc, posthookFunc,
                   new DataBetweenPreAndPost{insertPoint.full_demangled_name,
                                             nullptr, &public_scope},
                   0);
  }
}

void Instrumentation::prehookFunc(void *wrapcxt, void **user_data) {
  DataBetweenPreAndPost *data = (DataBetweenPreAndPost *)*user_data;
  std::string func_name = data->func_name;

  if (func_name.find("Post") != std::string::npos) {
    std::shared_ptr<drinstrumentation::trace::Span> span =
        drinstrumentation::trace::Provider::getTracerProvider()
            ->getTracer("default")
            ->startSpan(func_name,
                        drinstrumentation::trace::SpanContext::getInvalid());

    std::string *origin = new std::string((char *)drwrap_get_arg(wrapcxt, 1));
    int pos = origin->find("\r\n\r\n");
    origin->insert(pos, "\r\nParent-Id: " +
                            span->getContext().getSpanId().toLowerBase16());
    origin->insert(pos, "\r\nTrace-Id: " +
                            span->getContext().getTraceId().toLowerBase16());
    origin->insert(pos, "\r\nIs-Sampled: " +
                            std::to_string(span->getContext().isSampled()));
    drwrap_set_arg(wrapcxt, 1, (void *)origin->data());
    drwrap_set_arg(wrapcxt, 2, (void *)origin->length());

    if (span->getContext().getTraceState()->empty()) {
      span->getContext().getTraceState()->set("serviceName", "client_service");
      span->getContext().getTraceState()->set("ipv4", "127.0.0.1");
    }

    data->scope = new drinstrumentation::trace::Scope{span};
  } else if (func_name.find("receive") != std::string::npos) {
    return;
  } else if (func_name.find("response") != std::string::npos) {
    return;
  }
}

// trim from end of string (right)
static std::string rtrim(std::string s) {
  static char t[] = " \t\n\r\f\v";
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

// trim from beginning of string (left)
static std::string ltrim(std::string s) {
  static char t[] = " \t\n\r\f\v";
  s.erase(0, s.find_first_not_of(t));
  return s;
}

// trim from both ends of string (right then left)
static std::string trim(std::string s) { return ltrim(rtrim(s)); }

static std::string getHeaderInfo(std::string &payload, std::string key) {
  int start_pos = payload.find(':', payload.find(key)) + 1;
  int end_pos = payload.find("\r\n", start_pos);
  return trim(payload.substr(start_pos, end_pos - start_pos));
}

void Instrumentation::posthookFunc(void *wrapcxt, void *user_data) {
  DataBetweenPreAndPost *data = (DataBetweenPreAndPost *)user_data;
  std::string func_name = data->func_name;

  if (func_name.find("Post") != std::string::npos) {
    delete data->scope;
    data->scope = nullptr;
  } else if (func_name.find("receive") != std::string::npos) {
    std::string *payload = (std::string *)drwrap_get_retval(wrapcxt);

    if (payload->find("Parent-Id") == std::string::npos ||
        payload->find("Trace-Id") == std::string::npos ||
        payload->find("Is-Sampled") == std::string::npos) {
      return;
    }

    drinstrumentation::trace::SpanContext parent_span{
        drinstrumentation::trace::TraceId::fromString(
            getHeaderInfo(*payload, "Trace-Id")),
        drinstrumentation::trace::SpanId::fromString(
            getHeaderInfo(*payload, "Parent-Id")),
        getHeaderInfo(*payload, "Is-Sampled") == "1"};
    std::shared_ptr<drinstrumentation::trace::Span> span =
        drinstrumentation::trace::Provider::getTracerProvider()
            ->getTracer("default")
            ->startSpan(func_name, parent_span);

    if (span->getContext().getTraceState()->empty()) {
      span->getContext().getTraceState()->set("serviceName", "server_service");
      span->getContext().getTraceState()->set("ipv4", "127.0.0.1");
    }

    *(data->public_scope) = new drinstrumentation::trace::Scope{span};
  } else if (func_name.find("response") != std::string::npos) {
    delete *(data->public_scope);
    *(data->public_scope) = nullptr;
  }
}

}  // namespace instrumentation
}  // namespace sdk
}  // namespace drinstrumentation