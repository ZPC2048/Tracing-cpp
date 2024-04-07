#include "sdk/drinstrumentation/checker/checker.h"

namespace drinstrumentation {
namespace sdk {
namespace checker {

bool Checker::shouldInstrumentSymbol(symbol::Symbol symbol) {
  if (module_blacklist.find(symbol.module_name) != module_blacklist.end()) {
    return false;
  }
  if (file_blacklist.find(symbol.file_name) != file_blacklist.end()) {
    return false;
  }
}

}  // namespace checker
}  // namespace sdk
}  // namespace drinstrumentation