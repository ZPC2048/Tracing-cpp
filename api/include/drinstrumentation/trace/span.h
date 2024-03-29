#pragma once

#include <string>

namespace drinstrumentation {
namespace trace {

class Span {
 public:
  virtual void setAttribute(std::string key, std::string value) = 0;

  virtual void End() = 0;
};

}  // namespace trace
}  // namespace drinstrumentation