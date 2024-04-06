#pragma once

#include <memory>
#include <string>

#include "drinstrumentation/trace/tracer.h"

namespace drinstrumentation {
namespace trace {

class TracerProvider {
 public:
  virtual ~TracerProvider() = default;
  virtual std::shared_ptr<Tracer> getTracer(std::string name) = 0;
};

}  // namespace trace
}  // namespace drinstrumentation
