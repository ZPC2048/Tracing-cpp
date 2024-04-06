#pragma once

#include "sdk/drinstrumentation/trace/sampler.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class AlwaysOnSampler : public Sampler {
 public:
  ~AlwaysOnSampler() override;
  bool shouldSample(
      const drinstrumentation::trace::SpanContext& span_context) override;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation