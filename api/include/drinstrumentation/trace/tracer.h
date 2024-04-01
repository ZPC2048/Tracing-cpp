#pragma once

#include <memory>
#include <string>

#include "drinstrumentation/trace/span.h"

namespace drinstrumentation {
namespace trace {

class Tracer {
 public:
  virtual std::shared_ptr<Span> startSpan(std::string name) = 0;
  static void WithActiveSpan(std::shared_ptr<Span>) {}
  static std::shared_ptr<Span> getCurrentSpan() {}
};

}  // namespace trace
}  // namespace drinstrumentation
