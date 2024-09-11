#include "ssSHell.h"
#include "internalCommands.h"

SsShell shell;

SsShell::SsShell() : serialCount(0), inputIndex(0) {
    strcpy(prompt, "ssSHell> ");
}

void SsShell::begin(Stream &serial) {
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

void SsShell::loop() {
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

bool SsShell::addCommand(const char *command, void (*function)(char *)) {
    return library.addCommand(command, function);
}

bool SsShell::removeCommand(const char *command) {
    return library.removeCommand(command);
}

void SsShell::listCommands() {
    library.listCommands();
}

void SsShell::setPrompt(const char *newPrompt) {
    strncpy(prompt, newPrompt, MAX_PROMPT_LENGTH - 1);
    prompt[MAX_PROMPT_LENGTH - 1] = '\0';
}

bool SsShell::addSerial(Stream &serial) {
    if (serialCount < MAX_SERIALS) {
        serials[serialCount++] = &serial;
        return true;
    }
    return false;
}

bool SsShell::removeSerial(Stream &serial) {
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

void SsShell::processInput() {
    char command[MAX_INPUT_LENGTH];
    char params[MAX_INPUT_LENGTH];
    
    if (parser.parse(inputBuffer, command, params)) {
        if (!library.executeCommand(command, params)) {
            printToAll("Command not found. Type 'help' for available commands.");
        }
    }
}

void SsShell::printPrompt() {
    printToAll(prompt);
}

void SsShell::printToAll(const char* message) {
    for (uint8_t i = 0; i < serialCount; i++) {
        serials[i]->print(message);
    }
}

void SsShell::executeCommand(const char *command, const char *params) {
    library.executeCommand(command, (char*)params);  
}