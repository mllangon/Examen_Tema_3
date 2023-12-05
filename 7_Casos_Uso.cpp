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
            iter->second.first = value;
        }
    }

    template<typename T>
    T getVariableAs(const std::string& name) const {
        auto it = symbols.find(name);
        if (it == symbols.end()) {
            throw std::runtime_error("La variable del juego '" + name + "' no existe");
        }
        try {
            return std::get<T>(it->second.first);
        } catch (const std::bad_variant_access&) {
            throw std::runtime_error("Tipo incorrecto para la variable '" + name + "'");
        }
    }

private:
    std::map<std::string, std::pair<Value, bool>> symbols;
};

int main() {
    Environment gameEnv;

    gameEnv.setVariable("Dificultad", std::string("Normal"));

    gameEnv.setVariable("Salud", 100);

    gameEnv.setVariable("Puntos", 5000);

    std::cout << "Dificultad del Juego: " << gameEnv.getVariableAs<std::string>("Dificultad") << std::endl;
    std::cout << "Salud del Jugador: " << gameEnv.getVariableAs<int>("Salud") << std::endl;
    std::cout << "Puntaje Objetivo: " << gameEnv.getVariableAs<int>("Puntos") << std::endl;

    return 0;
}