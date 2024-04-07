#include "sdk/drinstrumentation/trace/tracer_context.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

TracerContext::TracerContext(std::unique_ptr<Sampler> sampler,
                             std::unique_ptr<IdGenerator> id_generator,
                             std::unique_ptr<SpanProcessor> processor)
    : sampler_(std::move(sampler)),
      id_generator_(std::move(id_generator)),
      processor_(std::move(processor)) {}

Sampler& TracerContext::getSampler() const { return *sampler_; }

IdGenerator& TracerContext::getIdGenerator() const { return *id_generator_; }

SpanProcessor& TracerContext::getProcessor() const { return *processor_; }

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation
