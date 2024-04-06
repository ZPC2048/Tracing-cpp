#pragma once

#include <memory>
#include <string>

#include "drinstrumentation/context/runtime_context.h"
#include "drinstrumentation/trace/scope.h"
#include "drinstrumentation/trace/span.h"
#include "drinstrumentation/trace/span_metadata.h"

namespace drinstrumentation {
namespace trace {

class Tracer {
 public:
  virtual std::shared_ptr<Span> startSpan(std::string name) = 0;

  virtual ~Tracer() = default;

  static Scope WithActiveSpan(std::shared_ptr<Span> span) {
    return Scope(span);
  }

  static std::shared_ptr<Span> getCurrentSpan() {
    return context::RuntimeContext::getCurrent().getValue(SPAN_KEY);
  }
};

}  // namespace trace
}  // namespace drinstrumentation
