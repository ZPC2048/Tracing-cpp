#pragma once

#include <map>
#include <memory>

#include "drinstrumentation/trace/tracer_provider.h"
#include "sdk/drinstrumentation/trace/tracer_context.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class TracerProvider : public drinstrumentation::trace::TracerProvider {
 public:
  TracerProvider(std::shared_ptr<TracerContext> context);
  ~TracerProvider() override;
  std::shared_ptr<drinstrumentation::trace::Tracer> getTracer(
      std::string name) override;

 private:
  std::shared_ptr<TracerContext> context_;
  std::map<std::string, std::shared_ptr<drinstrumentation::trace::Tracer>>
      tracers_;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation