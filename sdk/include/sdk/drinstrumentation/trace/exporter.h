#pragma once

#include "drinstrumentation/trace/span_context.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class SpanExporter {
 public:
  void Export(drinstrumentation::trace::SpanContext context);
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation