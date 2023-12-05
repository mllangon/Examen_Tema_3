#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <optional>

class Environment {
public:
    using Value = std::variant<int, double, std::string>;

    Environment() = default;

    Environment(const Environment&) = delete;
    Environment& operator=(const Environment&) = delete;

    void setVariable(const std::string& name, const Value& value) {
        symbols[name] = value;
    }

    std::optional<Value> lookup(const std::string& name) const {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return it->second;
        } else {
            return std::nullopt;
        }
    }

