#pragma once

#include <memory>

#include "sdk/drinstrumentation/trace/id_generator.h"
#include "sdk/drinstrumentation/trace/sampler.h"
#include "sdk/drinstrumentation/trace/span_processor.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class TracerContext {
 public:
  explicit TracerContext(std::unique_ptr<Sampler> sampler,
                         std::unique_ptr<IdGenerator> id_generator,
                         std::unique_ptr<SpanProcessor> processor);

  Sampler& getSampler() const;
  IdGenerator& getIdGenerator() const;
  SpanProcessor& getProcessor() const;

 private:
  std::unique_ptr<Sampler> sampler_;
  std::unique_ptr<IdGenerator> id_generator_;
  std::unique_ptr<SpanProcessor> processor_;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation