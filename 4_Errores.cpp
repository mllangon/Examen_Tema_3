#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <stdexcept>

class Environment {
public:
    using Value = std::variant<int, double, std::string>;

    Environment() = default;

    Environment(const Environment&) = delete;
    Environment& operator=(const Environment&) = delete;

    void setVariable(const std::string& name, const Value& value, bool readOnly = false) {
        auto [iter, success] = symbols.insert({name, std::make_pair(value, readOnly)});
        if (!success && iter->second.second) {
            throw std::runtime_error("No se puede modificar la constante del juego '" + name + "'");
        } else if (!success) {
            iter->second.first = value; // Actualiza el valor si no es de solo lectura
        }
    }

    Value getVariable(const std::string& name) const {
        auto it = symbols.find(name);
        if (it == symbols.end()) {
            throw std::runtime_error("La variable del juego '" + name + "' no existe");
        }
        return it->second.first;
    }

