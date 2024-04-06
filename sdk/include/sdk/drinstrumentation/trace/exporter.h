#pragma once

#include "drinstrumentation/trace/span.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class SpanExporter {
 public:
  virtual void Export(const drinstrumentation::trace::Span& span) = 0;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation