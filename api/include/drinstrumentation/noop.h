#pragma once

#include "drinstrumentation/instrumentation/instrumentation.h"

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

  virtual void insert_instrumentation_point(symbol::Symbol) { }
};

}  // namespace drinstrumentation