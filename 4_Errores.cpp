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

    Value getVariable(const std::string& name) const {
        auto it = symbols.find(name);
        if (it == symbols.end()) {
            throw std::runtime_error("La variable del juego '" + name + "' no existe");
        }
        return it->second.first;
    }

private:
    std::map<std::string, std::pair<Value, bool>> symbols; // El booleano indica si es de solo lectura
};

int main() {
    Environment gameEnv;

    try {

        gameEnv.setVariable("maxHealth", 100, true); // Constante del juego
        gameEnv.setVariable("playerHealth", 100);   // Variable del juego
        gameEnv.setVariable("playerName", std::string("Hero")); // Nombre del jugador
        gameEnv.setVariable("maxHealth", 150); // Intento fallido de modificar una constante

        std::cout << "Salud Máxima: " << std::get<int>(gameEnv.getVariable("maxHealth")) << std::endl;
        std::cout << "Salud del Jugador: " << std::get<int>(gameEnv.getVariable("playerHealth")) << std::endl;
        std::cout << "Nombre del Jugador: " << std::get<std::string>(gameEnv.getVariable("playerName")) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error en el juego: " << e.what() << std::endl;
    }

    try {
        std::cout << "Puntuacion: " << std::get<int>(gameEnv.getVariable("score")) << std::endl; // Variable no definida
    } catch (const std::runtime_error& e) {
        std::cerr << "Error en el juego: " << e.what() << std::endl;
    }

    return 0;
}
