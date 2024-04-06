#pragma once

#include <memory>
#include <string>

#include "drinstrumentation/trace/span_id.h"
#include "drinstrumentation/trace/trace_id.h"
#include "drinstrumentation/trace/trace_state.h"

namespace drinstrumentation {
namespace trace {

class SpanContext final {
 public:
  SpanContext(
      TraceId trace_id, SpanId span_id, bool is_sampled,
      std::shared_ptr<TraceState> trace_state = TraceState::getDefault())
      : trace_id_(trace_id),
        span_id_(span_id),
        is_sampled_(is_sampled),
        trace_state_(trace_state) {}

  const TraceId& getTraceId() const { return trace_id_; }

  const SpanId& getSpanId() const { return span_id_; }

  bool isSampled() const { return is_sampled_; }

  std::shared_ptr<TraceState> getTraceState() const { return trace_state_; }

  static SpanContext getInvalid() {
    return SpanContext{TraceId{}, SpanId{}, false, TraceState::getDefault()};
  }

 private:
  TraceId trace_id_;
  SpanId span_id_;
  bool is_sampled_;
  std::shared_ptr<TraceState> trace_state_;
};

}  // namespace trace
}  // namespace drinstrumentation