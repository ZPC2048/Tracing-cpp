#pragma once

#include <chrono>
#include <map>
#include <memory>

#include "drinstrumentation/trace/span.h"
#include "drinstrumentation/trace/span_context.h"
#include "sdk/drinstrumentation/trace/tracer.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class Span : public drinstrumentation::trace::Span {
 public:
  Span(std::shared_ptr<Tracer> tracer, std::string name, drinstrumentation::trace::SpanId parent_id,
       std::unique_ptr<drinstrumentation::trace::SpanContext> span_context);
  ~Span() override;
  const drinstrumentation::trace::SpanContext& getContext() override;
  void setAttribute(std::string key, std::string value) override;
  void End() override;
  std::string getSpanJson() const override;

 private:
  std::string name_;
  std::shared_ptr<Tracer> tracer_;
  std::unique_ptr<drinstrumentation::trace::SpanContext> span_context_;
  std::chrono::system_clock::time_point start_time_;
  std::map<std::string, std::string> attribute_;
  drinstrumentation::trace::SpanId parent_id_;
  bool has_ended_;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation