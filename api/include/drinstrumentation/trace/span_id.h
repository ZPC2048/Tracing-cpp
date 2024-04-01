#pragma once 

#include "drinstrumentation/defines.h"

namespace drinstrumentation {
namespace trace {

class SpanId final {
 public:
  static constexpr int kSize = 8;

 private:
  uint8 id_[kSize];
};

}  // namespace trace
}  // namespace drinstrumentation