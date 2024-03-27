#pragma once

#include <memory>
#include <vector>

#include "drinstrumentation/instrumentation/instrumentation.h"
#include "drinstrumentation/noop.h"

namespace drinstrumentation {
namespace instrumentation {

class InstrumentationProvider {
 public:
  /**
   * Returns the singleton Instrumentation.
   *
   * By default, a no-op Instrumentation is returned. This will never return a
   * nullptr Instrumentation.
   */
  static std::shared_ptr<Instrumentation> GetInstrumentationProvider() {
    return std::shared_ptr<Instrumentation>(GetInstrumentation());
  }

  /**
   * Changes the singleton Instrumentation.
   */
  static void SetInstrumentationProvider(
      std::shared_ptr<Instrumentation> instrumentation) {
    GetInstrumentation() = instrumentation;
  }

 private:
  static std::shared_ptr<Instrumentation>& GetInstrumentation() {
    static std::shared_ptr<Instrumentation> instrumentation(
        new NoopInstrumentation(
            std::make_shared<checker::Checker>(new NoopChecker)));
    return instrumentation;
  }
};

}  // namespace instrumentation
}  // namespace drinstrumentation