#ifndef SSSHELL_H
#define SSSHELL_H

#include <Arduino.h>
#include "CommandTokenizer.h"

typedef void (*CommandFunction)(void** args);  // Definir un puntero a función genérico.

class ssShell {
private:
    struct Command {
        String name;
        String paramTypes;   // Tipos de parámetros, como "int int float"
        CommandFunction function;
    };

    Command* commands;
    int commandCount;

    CommandTokenizer tokenizer;

    bool validateAndConvertParams(String paramTypes, CommandTokenizer& tokenizer, void** args);
    
    int findCommand(String commandName);  // DECLARACIÓN DE findCommand()

public:
    ssShell();
    void addCommand(String name, String paramTypes, CommandFunction function);
    bool executeCommand(String input);

    ~ssShell();
};

#endif
