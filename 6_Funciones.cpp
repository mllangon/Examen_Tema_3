#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <stdexcept>
#include<vector>

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

    void removeVariable(const std::string& name) {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            symbols.erase(it);
        }
    }

    bool hasVariable(const std::string& name) const {
        return symbols.find(name) != symbols.end();
    }

    std::string isVariableReadOnly(const std::string& name) const {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return (it->second.second) ? "Sí" : "No";
        } else {
            throw std::runtime_error("Variable del juego '" + name + "' no encontrada");
        }
    }

    void clearEnvironment() {
        symbols.clear();
    }

    std::vector<std::string> getAllVariables() const {
        std::vector<std::string> variableList;
        for (const auto& pair : symbols) {
            variableList.push_back(pair.first);
        }
        return variableList;
    }

private:
    std::map<std::string, std::pair<Value, bool>> symbols;
};

int main() {
    Environment gameEnv;

    gameEnv.setVariable("playerHealth", 100);
    gameEnv.setVariable("playerName", std::string("Mario"));
    gameEnv.setVariable("maxHealth", 200, true);

    std::cout << "Salud del Jugador: " << gameEnv.getVariableAs<int>("playerHealth") << std::endl;
    std::cout << "Nombre del Jugador: " << gameEnv.getVariableAs<std::string>("playerName") << std::endl;

    std::string varName = "maxHealth";
    std::cout << "Es '" << varName << "' de solo lectura? " << gameEnv.isVariableReadOnly(varName) << std::endl;

    try {
        gameEnv.setVariable("maxHealth", 250);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    gameEnv.removeVariable("playerName");

    std::string deletedVarName = "playerName";
    std::cout << "Existe '" << deletedVarName << "' en el entorno? " << (gameEnv.hasVariable(deletedVarName) ? "Sí" : "No") << std::endl;

    std::cout << "Variables en el entorno:" << std::endl;
    std::vector<std::string> variableList = gameEnv.getAllVariables();
    if (variableList.empty()) {
        std::cout << "No hay variables en el entorno." << std::endl;
    } else {
        for (const auto& var : variableList) {
            std::cout << "- " << var << std::endl;
        }
    }

    gameEnv.clearEnvironment();

    std::cout << "El entorno esta vacio? " << (gameEnv.getAllVariables().empty() ? "Si" : "No") << std::endl;

    return 0;
}