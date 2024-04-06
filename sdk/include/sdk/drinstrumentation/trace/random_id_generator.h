#pragma once

#include "sdk/drinstrumentation/trace/id_generator.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class RandomIdGenerator : public IdGenerator {
 public:
  ~RandomIdGenerator() override;
  drinstrumentation::trace::TraceId generateTraceId() override;
  drinstrumentation::trace::SpanId generateSpanId() override;

 private:
  static void generateBuffer(uint8* buffer, uint8 size);
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation