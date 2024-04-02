#pragma once

#include "drinstrumentation/trace/span_context.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class SpanExporter {
 public:
  virtual void Export(drinstrumentation::trace::SpanContext context) = 0;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation