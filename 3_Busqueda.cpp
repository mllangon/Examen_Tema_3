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

