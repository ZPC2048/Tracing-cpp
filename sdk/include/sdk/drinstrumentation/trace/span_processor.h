#pragma once

#include "drinstrumentation/trace/span.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class SpanProcessor {
 public:
  virtual ~SpanProcessor() = default;
  virtual void onEnd(const drinstrumentation::trace::Span& span) = 0;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation