#include "ssSHell.h"
#include "internalCommands.h"

ssShell shell;

ssShell::ssShell() : serialCount(0), inputIndex(0) {
    strcpy(prompt, "ssSHell> ");
}

void ssShell::begin(Stream &serial) {
    addSerial(serial);
    library.addCommand("help", cmdHelp);
    library.addCommand("version", cmdVersion);
    library.addCommand("echo", cmdEcho);
    library.addCommand("clear", cmdClear);
    library.addCommand("set", cmdSet);
    library.addCommand("get", cmdGet);
    library.addCommand("info", cmdInfo);
    library.addCommand("pin", cmdPin);
    printPrompt();
}

void ssShell::loop() {
    for (uint8_t i = 0; i < serialCount; i++) {
        while (serials[i]->available()) {
            char c = serials[i]->read();
            if (c == '\n' || c == '\r') {
                inputBuffer[inputIndex] = '\0';
                processInput();
                inputIndex = 0;
                printPrompt();
            } else if (inputIndex < MAX_INPUT_LENGTH - 1) {
                inputBuffer[inputIndex++] = c;
            }
        }
    }
}

bool ssShell::addCommand(const char *command, void (*function)(char *)) {
    return library.addCommand(command, function);
}

bool ssShell::removeCommand(const char *command) {
    return library.removeCommand(command);
}

void ssShell::listCommands() {
    library.listCommands();
}

void ssShell::setPrompt(const char *newPrompt) {
    strncpy(prompt, newPrompt, MAX_PROMPT_LENGTH - 1);
    prompt[MAX_PROMPT_LENGTH - 1] = '\0';
}

bool ssShell::addSerial(Stream &serial) {
    if (serialCount < MAX_SERIALS) {
        serials[serialCount++] = &serial;
        return true;
    }
    return false;
}

bool ssShell::removeSerial(Stream &serial) {
    for (uint8_t i = 0; i < serialCount; i++) {
        if (serials[i] == &serial) {
            for (uint8_t j = i; j < serialCount - 1; j++) {
                serials[j] = serials[j + 1];
            }
            serialCount--;
            return true;
        }
    }
    return false;
}

void ssShell::processInput() {
    char command[MAX_INPUT_LENGTH];
    char params[MAX_INPUT_LENGTH];
    
    if (parser.parse(inputBuffer, command, params)) {
        if (!library.executeCommand(command, params)) {
            printToAll("Command not found. Type 'help' for available commands.");
        }
    }
}

void ssShell::printPrompt() {
    printToAll(prompt);
}

void ssShell::printToAll(const char* message) {
    for (uint8_t i = 0; i < serialCount; i++) {
        serials[i]->print(message);
    }
}

void ssShell::executeCommand(const char *command, const char *params) {
    library.executeCommand(command, (char*)params);  
}
