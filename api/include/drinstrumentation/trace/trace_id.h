#pragma once

#include "drinstrumentation/defines.h"

namespace drinstrumentation {
namespace trace {

class TraceId final {
 public:
  static constexpr int kSize = 16;

 private:
  uint8 id_[kSize];
};

}  // namespace trace
}  // namespace drinstrumentation