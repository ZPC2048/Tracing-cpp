#pragma once

#include <memory>
#include <vector>

#include "drinstrumentation/checker/checker.h"
#include "drinstrumentation/symbol/symbol.h"

namespace drinstrumentation {
namespace instrumentation {

class Instrumentation {
 public:
  virtual void tryToInsertTracerInto(symbol::Symbol) = 0;
};

}  // namespace instrumentation
}  // namespace drinstrumentation