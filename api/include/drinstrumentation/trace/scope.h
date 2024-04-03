#pragma once

#include <memory>

#include "drinstrumentation/context/context.h"
#include "drinstrumentation/context/runtime_context.h"
#include "drinstrumentation/trace/span.h"
#include "drinstrumentation/trace/span_metadata.h"

namespace drinstrumentation {
namespace trace {

class Scope final {
 public:
  Scope(const std::shared_ptr<Span>& span)
      : token_(context::RuntimeContext::attach(
            context::RuntimeContext::getCurrent().nextContext(SPAN_KEY,
                                                              span))) {}

 private:
  std::unique_ptr<context::Token> token_;
};
}  // namespace trace
}  // namespace drinstrumentation