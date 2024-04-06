#include "sdk/drinstrumentation/trace/random_id_generator.h"

#include <random>

namespace drinstrumentation {
namespace sdk {
namespace trace {

RandomIdGenerator::~RandomIdGenerator() {}

drinstrumentation::trace::TraceId RandomIdGenerator::generateTraceId() {
  static uint8 buffer[drinstrumentation::trace::TraceId::SIZE];
  generateBuffer(buffer, drinstrumentation::trace::TraceId::SIZE);
  return drinstrumentation::trace::TraceId{buffer};
}

drinstrumentation::trace::SpanId RandomIdGenerator::generateSpanId() {
  static uint8 buffer[drinstrumentation::trace::SpanId::SIZE];
  generateBuffer(buffer, drinstrumentation::trace::SpanId::SIZE);
  return drinstrumentation::trace::SpanId{buffer};
}

void RandomIdGenerator::generateBuffer(uint8* buffer, uint8 size) {
  static std::mt19937 ran{std::random_device{}()};
  static std::uniform_int_distribution<uint8> dis(0, 15);
  for (uint8 i = 0; i < size; ++i) {
    buffer[i] = dis(ran);
  }
}

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation