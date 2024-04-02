#pragma once

#include "drinstrumentation/instrumentation/instrumentation.h"

namespace drinstrumentation {
namespace sdk {
namespace instrumentation {

class Instrumentation final
    : public drinstrumentation::instrumentation::Instrumentation {
 public:
  Instrumentation(std::shared_ptr<checker::Checker> checker);

  void tryToInsertTracerInto(symbol::Symbol) override;

  static void prehookFunc(void *wrapcxt, void **user_data);

  static void posthookFunc(void *wrapcxt, void *user_data);

 private:
  std::shared_ptr<checker::Checker> checker_;
};

}  // namespace instrumentation
}  // namespace sdk
}  // namespace drinstrumentation