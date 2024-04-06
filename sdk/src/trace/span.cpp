#include "sdk/drinstrumentation/trace/span.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

Span::Span(std::shared_ptr<Tracer> tracer, std::string name,
           drinstrumentation::trace::SpanId parent_id,
           std::unique_ptr<drinstrumentation::trace::SpanContext> span_context)
    : tracer_(tracer),
      name_(name),
      parent_id_(parent_id),
      span_context_(std::move(span_context)),
      has_ended_(false),
      start_time_(std::chrono::system_clock::now()) {}

Span::~Span() { End(); }

const drinstrumentation::trace::SpanContext& Span::getContext() {
  return *span_context_;
}

void Span::setAttribute(std::string key, std::string value) {
  attribute_[key] = value;
}

void Span::End() {
  if (has_ended_) {
    return;
  }
  has_ended_ = true;
  tracer_->getProcessor().onEnd(*this);
}

std::string Span::getSpanJson() const {
  std::string json;
  json += R"([{)";
  json += R"("id":")" + span_context_->getSpanId().toLowerBase16() + R"(",)";
  json +=
      R"("traceId":")" + span_context_->getTraceId().toLowerBase16() + R"(",)";
  if (parent_id_.isValid()) {
    json += R"("parentId":")" + parent_id_.toLowerBase16() + R"(",)";
  }
  json += R"("name":")" + name_ + R"(",)";
  json +=
      R"("timestamp":)" +
      std::to_string(
          std::chrono::time_point_cast<std::chrono::microseconds>(start_time_)
              .time_since_epoch()
              .count()) +
      ",";
  json += R"("duration":)" +
          std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(
                             std::chrono::system_clock::now() - start_time_)
                             .count());
  json += R"(}])";
  return json;
}

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation