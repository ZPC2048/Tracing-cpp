#pragma once

#include <memory>
#include <string>

#include "drinstrumentation/trace/span.h"

namespace drinstrumentation {
namespace context {

class Context {
 public:
  Context() : head_(nullptr) {}

  Context(std::string key, std::shared_ptr<trace::Span> value)
      : head_(new DataList(key, value)) {}

  Context nextContext(std::string key, std::shared_ptr<trace::Span> value) {
    Context context(key, value);
    context.head_->next_ = this->head_;
    return context;
  }

  std::shared_ptr<trace::Span> getValue(std::string key) {
    std::shared_ptr<DataList> cur = head_;
    while (cur != nullptr) {
      if (cur->key_ == key) {
        return cur->value_;
      }
      cur = cur->next_;
    }
    return nullptr;
  }

  bool operator==(const Context& other) const { return head_ == other.head_; }

 private:
  class DataList {
   public:
    DataList() : next_(nullptr), value_(nullptr) {}
    DataList(std::string key, std::shared_ptr<trace::Span> value)
        : next_(nullptr), key_(key), value_(value) {}

    std::shared_ptr<DataList> next_;
    std::string key_;
    std::shared_ptr<trace::Span> value_;
  };

  std::shared_ptr<DataList> head_;
};

}  // namespace context
}  // namespace drinstrumentation