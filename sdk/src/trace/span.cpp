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

const drinstrumentation::trace::SpanContext Span::getContext() const {
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
  if (span_context_->isSampled()) {
    tracer_->getProcessor().onEnd(*this);
  }
}

static std::string getKeyValuJson(std::string key, std::string value) {
  return "\"" + key + "\":\"" + value + "\"";
}

static std::string getMapJson(std::map<std::string, std::string> m) {
  std::string json = "{";
  for (auto item : m) {
    json += getKeyValuJson(item.first, item.second);
  }
  json += "}";
  return json;
}

std::string Span::getSpanJson() const {
  std::string json;
  json += "[{";
  json +=
      getKeyValuJson("id", span_context_->getSpanId().toLowerBase16()) + ",";
  json +=
      getKeyValuJson("traceId", span_context_->getTraceId().toLowerBase16()) +
      ",";
  if (parent_id_.isValid()) {
    json += getKeyValuJson("parentId", parent_id_.toLowerBase16()) + ",";
  }
  json += getKeyValuJson("name", name_) + ",";
  if (!attribute_.empty()) {
    json += "tags:" + getMapJson(attribute_) + ",";
  }
  std::string service_name, service_addr;
  if (getContext().getTraceState()->get("serviceName", service_name) &&
      getContext().getTraceState()->get("ipv4", service_addr)) {
    json += "\"localEndpoint\":{" +
            getKeyValuJson("serviceName", service_name) + "," +
            getKeyValuJson("ipv4", service_addr) + "},";
  }
  json += getKeyValuJson(
              "timestamp",
              std::to_string(
                  std::chrono::time_point_cast<std::chrono::microseconds>(
                      start_time_)
                      .time_since_epoch()
                      .count())) +
          ",";
  json += getKeyValuJson(
      "duration",
      std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(
                         std::chrono::system_clock::now() - start_time_)
                         .count()));
  json += "}]";
  return json;
}

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation