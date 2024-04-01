#pragma once

#include "drinstrumentation/instrumentation/instrumentation.h"
#include "drinstrumentation/trace/span.h"
#include "drinstrumentation/trace/tracer.h"
#include "drinstrumentation/trace/tracer_provider.h"

namespace drinstrumentation {

class NoopChecker final : public checker::Checker {
 public:
  virtual bool check_instrumentation_point(symbol::Symbol symbol) {
    return true;
  }
};

class NoopInstrumentation final : public instrumentation::Instrumentation {
 public:
  NoopInstrumentation(std::shared_ptr<checker::Checker> checker)
      : instrumentation::Instrumentation(checker) {}

  virtual const std::vector<symbol::Symbol>& get_instrumentation_point() {
    return std::vector<symbol::Symbol>{};
  }

  virtual void insert_instrumentation_point(symbol::Symbol) {}
};

class NoopSpan final : public trace::Span {
 public:
  void setAttribute(std::string key, std::string value) override {}

  void End() override {}
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