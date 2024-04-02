#pragma once

#include <string>

#include "drinstrumentation/defines.h"

namespace drinstrumentation {
namespace symbol {

struct Symbol {
 public:
  /** file name, can be empty. */
  std::string file_name;

  /** module name, can be empty. */
  std::string module_name;

  /** line number */
  uint64 line;

  /** offset from address that starts at line */
  size_t line_offs;

  /** module base pointer */
  pointer module_start;

  /** offset from module base of start of symbol. */
  size_t start_offs;

  /** offset from module base of end of symbol.*/
  size_t end_offs;

  /** mangled symbol name, can be empty. */
  std::string mangled_name;

  /**
   * Omitting templates and parameter types. For all symbol types,
   * templates are collapsed to <> while function parameters are
   * omitted entirely (without any parentheses). Can be empty.
   **/
  std::string demangled_name;

  /** Demangle template arguments and parameter types. Can be empty. */
  std::string full_demangled_name;
};

}  // namespace symbol
}  // namespace drinstrumentation