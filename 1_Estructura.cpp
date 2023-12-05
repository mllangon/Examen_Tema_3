#include <map>
#include <string>
#include <stdexcept>

class Variant{
public:
    Variant(int intValue) : value(intValue) {}
    Variant(double doubleValue) : value(doubleValue) {}
    Variant(const std::string& stringValue) : value(stringValue) {}

    bool isInt() const { return std::holds_alternative<int>(value); }
    bool isDouble() const { return std::holds_alternative<double>(value); }
    bool isString() const { return std::holds_alternative<std::string>(value); }

    int asInt() const {
        if (!isInt()) throw std::runtime_error("No es un int");
        return std::get<int>(value);
    }


};