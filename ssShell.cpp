#include "ssShell.h"

ssShell::ssShell() : commandCount(0), commands(nullptr) {}

void ssShell::addCommand(String name, String paramTypes, CommandFunction function) {
    // Aumentar la lista de comandos dinámicamente
    Command* newCommands = new Command[commandCount + 1];
    for (int i = 0; i < commandCount; i++) {
        newCommands[i] = commands[i];
    }

    // Agregar el nuevo comando
    newCommands[commandCount].name = name;
    newCommands[commandCount].paramTypes = paramTypes;
    newCommands[commandCount].function = function;

    delete[] commands;
    commands = newCommands;
    commandCount++;

    // Ordenar los comandos por nombre para optimizar la búsqueda binaria
    for (int i = 0; i < commandCount - 1; i++) {
        for (int j = i + 1; j < commandCount; j++) {
            if (commands[i].name > commands[j].name) {
                Command temp = commands[i];
                commands[i] = commands[j];
                commands[j] = temp;
            }
        }
    }
}

bool ssShell::validateAndConvertParams(String paramTypes, CommandTokenizer& tokenizer, void** args) {
    int paramCount = tokenizer.getParamCount();
    if (paramTypes.length() != paramCount * 4 - 1) {
        return false;
    }

    for (int i = 0; i < paramCount; i++) {
        String type = paramTypes.substring(i * 4, i * 4 + 3);
        bool success = false;

        if (type == "int") {
            int* param = new int;
            *param = tokenizer.getParamAsInt(i, success);
            if (!success) return false;
            args[i] = param;
        } else if (type == "flo") {
            float* param = new float;
            *param = tokenizer.getParamAsFloat(i, success);
            if (!success) return false;
            args[i] = param;
        } else if (type == "boo") {
            bool* param = new bool;
            *param = tokenizer.getParamAsBool(i, success);
            if (!success) return false;
            args[i] = param;
        } else if (type == "str") {
            String* param = new String;
            *param = tokenizer.getParamAsString(i);
            args[i] = param;
        } else {
            return false;
        }
    }
    return true;
}

// Búsqueda binaria para encontrar el comando
int ssShell::findCommand(String commandName) {
    int low = 0;
    int high = commandCount - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (commands[mid].name == commandName) {
            return mid;  // Comando encontrado
        } else if (commands[mid].name < commandName) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;  // Comando no encontrado
}

bool ssShell::executeCommand(String input) {
    tokenizer.parse(input);
    String commandName = tokenizer.getCommand();

    int commandIndex = findCommand(commandName);
    if (commandIndex == -1) {
        return false;  // Comando no encontrado
    }

    Command& cmd = commands[commandIndex];
    int paramCount = tokenizer.getParamCount();
    void** args = new void*[paramCount];

    if (!validateAndConvertParams(cmd.paramTypes, tokenizer, args)) {
        delete[] args;
        return false;
    }

    cmd.function(args);

    for (int i = 0; i < paramCount; i++) {
        delete args[i];
    }
    delete[] args;

    return true;
}

ssShell::~ssShell() {
    delete[] commands;
}
