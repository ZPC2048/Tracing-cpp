#pragma once

#include <string>

#include "drinstrumentation/trace/span_context.h"

namespace drinstrumentation {
namespace trace {

class Span {
 public:
  virtual ~Span() = default;
  virtual const SpanContext getContext() const = 0;
  virtual void setAttribute(std::string key, std::string value) = 0;
  virtual void End() = 0;
  virtual std::string getSpanJson() const = 0;
};

}  // namespace trace
}  // namespace drinstrumentation