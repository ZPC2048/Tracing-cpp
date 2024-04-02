#include "sdk/drinstrumentation/instrumentation/instrumentation.h"

#include "dr_api.h"
#include "drwrap.h"

namespace drinstrumentation {
namespace sdk {
namespace instrumentation {

Instrumentation::Instrumentation(std::shared_ptr<checker::Checker> checker)
    : checker_(checker) {}

void Instrumentation::tryToInsertTracerInto(symbol::Symbol insertPoint) {
  if (checker_->shouldInstrumentSymbol(insertPoint)) {
    drwrap_wrap_ex(insertPoint.module_start + insertPoint.start_offs,
                   prehookFunc, posthookFunc, nullptr, 0);
  }
}

void Instrumentation::prehookFunc(void *wrapcxt, void **user_data) {

}

void Instrumentation::posthookFunc(void *wrapcxt, void *user_data) {
  
}

}  // namespace instrumentation
}  // namespace sdk
}  // namespace drinstrumentation