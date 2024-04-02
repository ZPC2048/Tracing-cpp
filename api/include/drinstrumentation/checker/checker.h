#pragma once

#include "drinstrumentation/symbol/symbol.h"

namespace drinstrumentation {
namespace checker {

class Checker {
 public:
  virtual bool shouldInstrumentSymbol(symbol::Symbol symbol) = 0;
};

}  // namespace checker
}  // namespace drinstrumentation