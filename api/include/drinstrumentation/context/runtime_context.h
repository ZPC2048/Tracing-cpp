#pragma once

#include <memory>
#include <vector>

#include "drinstrumentation/context/context.h"

namespace drinstrumentation {
namespace context {

class RuntimeContext;

/**
 * The Token object is returned when attaching context to the
 * RuntimeContext object and is associated with the attached context, and can be
 * provided to the RuntimeContext detach method to remove the associated context
 * from the RuntimeContext.
 */
class Token {
 public:
  Token(const Context& context) : context_(context) {}

  ~Token();

  bool operator==(const Context& other) const {
    return other == this->context_;
  }

 private:
  const Context context_;
};

/**
 * RuntimeContextStorage is used by RuntimeContext to store Context.
 */
class RuntimeContextStorage {
 public:
  virtual Context getCurrent() = 0;
  virtual std::unique_ptr<Token> attach(const Context&) = 0;
  virtual bool detach(Token& token) = 0;
  virtual ~RuntimeContextStorage() = default;
};

class DefaultRuntimeContextStorage : public RuntimeContextStorage {
 public:
  Context getCurrent() override {
    if (stack_.empty()) {
      return Context();
    }
    return stack_.back();
  }

  std::unique_ptr<Token> attach(const Context& context) override {
    stack_.push_back(context);
    return std::unique_ptr<Token>(new Token(context));
  }

  bool detach(Token& token) override {
    if (!stack_.empty() && token == stack_.back()) {
      stack_.pop_back();
      return true;
    }

    if (!hasContext(token)) {
      return false;
    }

    while (!stack_.empty()) {
      if (token == stack_.back()) {
        stack_.pop_back();
        return true;
      }
      stack_.pop_back();
    }
    return false;
  }

 private:
  bool hasContext(Token& token) {
    for (auto iter = stack_.rbegin(); iter != stack_.rend(); ++iter) {
      if (token == *iter) {
        return true;
      }
    }
    return false;
  }

  std::vector<Context> stack_;
};

/**
 * Provides a wrapper for propagating the context object globally.
 */
class RuntimeContext {
 public:
  static void setRuntimeContextStorage(
      std::shared_ptr<RuntimeContextStorage> context_storage) {
    getRuntimeContextStorage() = context_storage;
  }

  static Context getCurrent() {
    return getRuntimeContextStorage()->getCurrent();
  }

  static std::unique_ptr<Token> attach(const Context& context) {
    return getRuntimeContextStorage()->attach(context);
  }

  static bool detach(Token& token) {
    return getRuntimeContextStorage()->detach(token);
  }

 private:
  static std::shared_ptr<RuntimeContextStorage>& getRuntimeContextStorage() {
    static std::shared_ptr<RuntimeContextStorage> context_storage_(
        new DefaultRuntimeContextStorage);
    return context_storage_;
  }
};

Token::~Token() { RuntimeContext::detach(*this); }

}  // namespace context
}  // namespace drinstrumentation