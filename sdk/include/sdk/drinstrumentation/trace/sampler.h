#pragma once

#include "drinstrumentation/trace/span_context.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class Sampler {
 public:
  virtual ~Sampler() = default;
  virtual bool shouldSample(const drinstrumentation::trace::SpanContext&) = 0;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation