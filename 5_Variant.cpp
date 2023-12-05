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

private:
    std::map<std::string, Variant::Value> symbolTable;
};

int main() {
    Environment myEnvironment;

    myEnvironment.addSymbol("x", 10);
    myEnvironment.addSymbol("y", 3.14);
    myEnvironment.addSymbol("nombre", "Mario");

    Variant::Value valueX = myEnvironment.getSymbolValue("x");
    Variant::Value valueY = myEnvironment.getSymbolValue("y");
    Variant::Value valueName = myEnvironment.getSymbolValue("nombre");

    Variant variantX(valueX);
    Variant variantY(valueY);
    Variant variantName(valueName);

    std::cout << "Valor de x: ";
    variantX.printValue();

    std::cout << "Valor de y: ";
    variantY.printValue();

    std::cout << "Valor de nombre: ";
    variantName.printValue();

    return 0;
}