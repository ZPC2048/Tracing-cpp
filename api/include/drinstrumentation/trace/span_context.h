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
  bool isSampled() {}

 private:
  TraceId trace_id;
  SpanId span_id;
  std::shared_ptr<TraceState> trace_state_;
};

}  // namespace trace
}  // namespace drinstrumentation