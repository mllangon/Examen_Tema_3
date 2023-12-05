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

private:
    std::map<std::string, Value> symbols;
};

void printVariable(const std::optional<Environment::Value>& value, const std::string& name) {
    if (value) {
        std::visit([&name](const auto& v) { std::cout << "Valor de '" << name << "': " << v << std::endl; }, *value);
    } else {
        std::cout << "La variable '" << name << "' no existe." << std::endl;
    }
}

int main() {
    Environment env;
    env.setVariable("testInt", 42);
    env.setVariable("testString", std::string("Hello"));

    printVariable(env.lookup("testInt"), "testInt");

    printVariable(env.lookup("nonExistent"), "nonExistent");

    return 0;
}