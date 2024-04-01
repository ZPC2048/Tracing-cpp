#pragma once

#include <memory>

#include "drinstrumentation/noop.h"
#include "drinstrumentation/trace/tracer_provider.h"

namespace drinstrumentation {
namespace trace {

class Provider {
 public:
  static std::shared_ptr<TracerProvider> getTracerProvider() {
    return getTracerProvider_();
  }

  static void setTracerProvider(
      std::shared_ptr<TracerProvider> trace_provider) {
    getTracerProvider_() = trace_provider;
  }

 private:
  static std::shared_ptr<TracerProvider>& getTracerProvider_() {
    static std::shared_ptr<TracerProvider> trace_provider(
        new NoopTracerProvider);
    return trace_provider;
  }
};

}  // namespace trace
}  // namespace drinstrumentation
