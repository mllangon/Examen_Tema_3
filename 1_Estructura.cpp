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


    gameEnvironment.setVariable("vidaJugador", 100);
    gameEnvironment.setVariable("puntuacion", 0);
    gameEnvironment.setVariable("nombreNivel", std::string("Bosque Encantado"));

    try {
        std::cout << "Vida del Jugador: " << gameEnvironment.getVariable<int>("vidaJugador") << std::endl;
        std::cout << "Puntuacion: " << gameEnvironment.getVariable<int>("puntuacion") << std::endl;
        std::cout << "Nombre del Nivel: " << gameEnvironment.getVariable<std::string>("nombreNivel") << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}