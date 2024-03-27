#pragma once

#include <memory>
#include <vector>

#include "drinstrumentation/checker/checker.h"
#include "drinstrumentation/symbol/symbol.h"

namespace drinstrumentation {
namespace instrumentation {

class Instrumentation {
 public:
  Instrumentation(std::shared_ptr<checker::Checker> checker)
      : checker_(checker) {}

  virtual const std::vector<symbol::Symbol>& get_instrumentation_point() = 0;

  virtual void insert_instrumentation_point(symbol::Symbol point) = 0;

 protected:
  std::shared_ptr<checker::Checker> checker_;
};

}  // namespace instrumentation
}  // namespace drinstrumentation