#pragma once

#include <memory>

#include "drinstrumentation/trace/tracer.h"
#include "sdk/drinstrumentation/trace/tracer_context.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class Tracer : public drinstrumentation::trace::Tracer,
               public std::enable_shared_from_this<Tracer> {
 public:
  Tracer(std::shared_ptr<TracerContext> context);

  std::shared_ptr<drinstrumentation::trace::Span> startSpan(
      std::string name) override;

  SpanProcessor& getProcessor();

  IdGenerator& getIdGenerator() const;

 private:
  std::shared_ptr<TracerContext> context_;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation