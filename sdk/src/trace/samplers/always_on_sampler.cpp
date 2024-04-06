#include "sdk/drinstrumentation/trace/samplers/always_on_sampler.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

AlwaysOnSampler::~AlwaysOnSampler() {}

bool AlwaysOnSampler::shouldSample(
    const drinstrumentation::trace::SpanContext& span_context) {
  return true;
}

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation