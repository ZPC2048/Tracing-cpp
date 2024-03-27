#include "sdk/drinstrumentation/instrumentation/instrumentation.h"

namespace drinstrumentation {
namespace sdk {
namespace instrumentation {

Instrumentation::Instrumentation(std::shared_ptr<checker::Checker> checker) :
  drinstrumentation::instrumentation::Instrumentation(checker) {

  }

const std::vector<symbol::Symbol>& Instrumentation::get_instrumentation_point() {
  return instrumentation_point_;
}

void Instrumentation::insert_instrumentation_point(symbol::Symbol point) {
  if (checker_->check_instrumentation_point(point)) {
    instrumentation_point_.push_back(point);
  }
}

}  // namespace instrumentation
}  // namespace sdk
}  // namespace drinstrumentation