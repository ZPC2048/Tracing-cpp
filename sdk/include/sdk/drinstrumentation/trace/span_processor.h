#pragma once

#include "drinstrumentation/trace/span_context.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class SpanProcessor {
 public:
  virtual void onStart() = 0;
  virtual void onEnd(drinstrumentation::trace::SpanContext context) = 0;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation