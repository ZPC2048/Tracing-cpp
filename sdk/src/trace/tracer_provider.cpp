#include "sdk/drinstrumentation/trace/tracer_provider.h"

#include "sdk/drinstrumentation/trace/tracer.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

TracerProvider::TracerProvider(std::shared_ptr<TracerContext> context)
    : context_(context) {}

TracerProvider::~TracerProvider() {}

std::shared_ptr<drinstrumentation::trace::Tracer> TracerProvider::getTracer(
    std::string name) {
  auto tracer_iter = tracers_.find(name);
  if (tracer_iter != tracers_.end()) {
    return tracer_iter->second;
  }
  tracers_[name] =
      std::shared_ptr<drinstrumentation::trace::Tracer>(new Tracer(context_));
  return tracers_[name];
}

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation