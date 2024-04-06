#pragma once

#include "sdk/drinstrumentation/trace/sampler.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class AlwaysOffSampler : public Sampler {
 public:
  ~AlwaysOffSampler() override;
  bool shouldSample(
      const drinstrumentation::trace::SpanContext& span_context) override;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation