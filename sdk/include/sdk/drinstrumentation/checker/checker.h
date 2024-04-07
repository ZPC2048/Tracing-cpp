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

}  // namespace checker
}  // namespace sdk
}  // namespace drinstrumentation