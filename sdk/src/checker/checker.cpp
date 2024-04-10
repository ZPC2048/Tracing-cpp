#include "sdk/drinstrumentation/checker/checker.h"

namespace drinstrumentation {
namespace sdk {
namespace checker {

const std::unordered_set<std::string> Checker::module_blacklist{
    "libdynamorio.so", "ld-linux-x86-64.so.2", "linux-vdso.so.1", "libc.so.6",
    "libm.so.6",       "libgcc_s.so.1",        "libstdc++.so.6"};

const std::unordered_set<std::string> Checker::file_blacklist{
    "libdynamorio.so",
    "ld-linux-x86-64.so.2",
    "[vdso]",
    "libc.so.6",
    "libm.so.6",
    "libgcc_s.so.1",
    "libstdc++.so.6.0.30"};

bool Checker::shouldInstrumentSymbol(symbol::Symbol symbol) {
  if (module_blacklist.find(symbol.module_name) != module_blacklist.end()) {
    return false;
  }
  if (file_blacklist.find(symbol.file_name) != file_blacklist.end()) {
    return false;
  }

  // DEBUG
  if (symbol.demangled_name != "Post" &&
      symbol.demangled_name != "receive" &&
      symbol.demangled_name != "response") {
    return false;
  }
  return true;
}

}  // namespace checker
}  // namespace sdk
}  // namespace drinstrumentation