#include <iostream>
#include <map>
#include <string>
#include <variant>

class Variant {
public:

    using Value = std::variant<int, double, std::string>;

    Variant(const Value& val) : value(val) {}

    Value getValue() const {
        return value;
    }

    void printValue() const {
        std::visit([](const auto& v) { std::cout << v; }, value);
        std::cout << std::endl;
    }

private:
    Value value;
};

class Environment {
public:

    void addSymbol(const std::string& symbol, const Variant::Value& value) {
        symbolTable[symbol] = value;
    }

    Variant::Value getSymbolValue(const std::string& symbol) const {
        auto it = symbolTable.find(symbol);
        if (it != symbolTable.end()) {
            return it->second;
        } else {
            std::cerr << "Error: El simbolo '" << symbol << "' no esta definido." << std::endl;
            return Variant::Value{};
        }
    }

