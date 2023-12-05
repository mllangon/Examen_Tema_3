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

    bool insert(const std::string& name, const std::variant<int, double, std::string>& value) {
        auto result = symbols.insert({name, value});
        return result.second;
    }

    void setVariable(const std::string& name, const std::variant<int, double, std::string>& value) {
        symbols[name] = value;
    }

    template<typename T>
    T getVariable(const std::string& name) const {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            try {
                return std::get<T>(it->second);
            } catch (const std::bad_variant_access&) {
                throw std::runtime_error("Tipo de variable incorrecto para " + name);
            }
        } else {
            throw std::runtime_error("Variable no encontrada: " + name);
        }
    }

private:
    std::map<std::string, std::variant<int, double, std::string>> symbols;
};

int main() {
    Environment gameEnvironment;


    bool inserted = gameEnvironment.insert("vidaJugador", 100);
    std::cout << "'vidaJugador' fue insertado? " << (inserted ? "Si" : "No") << std::endl;


    inserted = gameEnvironment.insert("vidaJugador", 150);
    std::cout << "Intento de reinsertar 'vidaJugador'? " << (inserted ? "Si" : "No") << std::endl;


