#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "drinstrumentation/checker/checker.h"

namespace drinstrumentation {
namespace sdk {
namespace checker {

class Checker final : public drinstrumentation::checker::Checker {
 public:
  virtual bool shouldInstrumentSymbol(symbol::Symbol symbol) override;

 private:
  static const std::unordered_set<std::string> module_blacklist;
  static const std::unordered_set<std::string> file_blacklist;
};

}  // namespace checker
}  // namespace sdk
}  // namespace drinstrumentation