#pragma once

#include "drinstrumentation/trace/span_id.h"
#include "drinstrumentation/trace/trace_id.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class IdGenerator {
 public:
  virtual ~IdGenerator() = default;
  virtual drinstrumentation::trace::TraceId generateTraceId() = 0;
  virtual drinstrumentation::trace::SpanId generateSpanId() = 0;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation