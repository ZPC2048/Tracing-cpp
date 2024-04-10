#pragma once

#include <cstring>
#include <string>

#include "drinstrumentation/defines.h"

namespace drinstrumentation {
namespace trace {

class SpanId final {
 public:
  static constexpr uint8 SIZE = 8;

  SpanId() : id_{0} {}

  SpanId(uint8* id) { memcpy(id_, id, SIZE); }

  static SpanId fromString(std::string s) {
    SpanId result;
    if (SIZE * 2 > s.size()) {
      return result;
    }
    for (int i = 0; i < SIZE; ++i) {
      result.id_[i] = std::stoi(s.substr(2 * i, 2), nullptr, 16);
    }
    return result;
  }

  std::string toLowerBase16() const {
    static char HEX[] = "0123456789abcdef";
    std::string buf(SIZE * 2, '0');
    for (int i = 0; i < SIZE; ++i) {
      buf[i * 2 + 0] = HEX[(id_[i] & 0xF0) >> 4];
      buf[i * 2 + 1] = HEX[(id_[i] & 0x0F) >> 0];
    }
    return buf;
  }

  bool operator==(const SpanId& other) const {
    return memcmp(id_, other.id_, SIZE) == 0;
  }

  bool operator!=(const SpanId& other) const { return !(*this == other); }

  bool isValid() const {
    static const uint8 empty_id_[SIZE] = {0};
    return memcmp(id_, empty_id_, SIZE) != 0;
  }

 private:
  uint8 id_[SIZE];
};

}  // namespace trace
}  // namespace drinstrumentation