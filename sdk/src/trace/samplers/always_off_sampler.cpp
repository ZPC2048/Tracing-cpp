#include "sdk/drinstrumentation/trace/samplers/always_off_sampler.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

AlwaysOffSampler::~AlwaysOffSampler() {}

bool AlwaysOffSampler::shouldSample(
    const drinstrumentation::trace::SpanContext& span_context) {
  return false;
}

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation