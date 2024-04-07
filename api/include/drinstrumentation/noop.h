#pragma once

#include "drinstrumentation/instrumentation/instrumentation.h"
#include "drinstrumentation/trace/span.h"
#include "drinstrumentation/trace/tracer.h"
#include "drinstrumentation/trace/tracer_provider.h"

namespace drinstrumentation {

class NoopChecker final : public checker::Checker {
 public:
  bool shouldInstrumentSymbol(symbol::Symbol symbol) override { return true; }
};

class NoopInstrumentation final : public instrumentation::Instrumentation {
 public:
  NoopInstrumentation() {}

  void tryToInsertTracerInto(symbol::Symbol) override {}
};

class NoopSpan final : public trace::Span {
 public:
  const trace::SpanContext getContext() override {
    return trace::SpanContext::getInvalid();
  }
  void setAttribute(std::string key, std::string value) override {}
  void End() override {}
  std::string getSpanJson() const override { return ""; }
};

class NoopTracer final : public trace::Tracer {
 public:
  std::shared_ptr<trace::Span> startSpan(std::string name) override {
    static std::shared_ptr<trace::Span> span_(new NoopSpan);
    return span_;
  }
};

class NoopTracerProvider final : public trace::TracerProvider {
 public:
  NoopTracerProvider() : tracer_(new NoopTracer) {}

  std::shared_ptr<trace::Tracer> getTracer(std::string name) override {
    return tracer_;
  }

 private:
  std::shared_ptr<trace::Tracer> tracer_;
};

}  // namespace drinstrumentation