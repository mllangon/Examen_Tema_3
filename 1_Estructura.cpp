#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <variant>

class Environment {
public:
    Environment() = default;

    Environment(const Environment&) = delete;
    Environment& operator=(const Environment&) = delete;

    void setVariable(const std::string& name, const std::variant<int, double, std::string>& value) {
        symbols[name] = value;
    }

