#pragma once

#include <map>
#include <memory>
#include <string>

namespace drinstrumentation {
namespace trace {

class TraceState {
 public:
  void set(const std::string& key, const std::string& value) {
    kv_container_[key] = value;
  }

  bool get(const std::string& key, std::string& value) {
    auto value_iter = kv_container_.find(key);
    if (value_iter != kv_container_.end()) {
      value = value_iter->second;
      return true;
    }
    return false;
  }

  void remove(const std::string& key) { kv_container_.erase(key); }

  bool empty() { return kv_container_.empty(); }

  static std::shared_ptr<TraceState> getDefault() {
    static std::shared_ptr<TraceState> trace_state{new TraceState()};
    return trace_state;
  }

 private:
  std::map<std::string, std::string> kv_container_;
};

}  // namespace trace
}  // namespace drinstrumentation
