#pragma once

#include "drinstrumentation/instrumentation/instrumentation.h"

namespace drinstrumentation {
namespace sdk {
namespace instrumentation {

class Instrumentation final
    : public drinstrumentation::instrumentation::Instrumentation {
 public:
  Instrumentation(std::shared_ptr<checker::Checker> checker);

  virtual const std::vector<symbol::Symbol>& get_instrumentation_point();

  virtual void insert_instrumentation_point(symbol::Symbol point);

 protected:
  std::vector<symbol::Symbol> instrumentation_point_;
};



}  // namespace instrumentation
}  // namespace sdk
}  // namespace drinstrumentation