#include "commandLibrary.h"
#include "ssSHell.h"

CommandLibrary::CommandLibrary() : commandCount(0) {}

bool CommandLibrary::addCommand(const char *command, void (*function)(char *)) {
    if (commandCount < MAX_COMMANDS) {
        strncpy(commands[commandCount].name, command, MAX_COMMAND_LENGTH - 1);
        commands[commandCount].name[MAX_COMMAND_LENGTH - 1] = '\0';
        commands[commandCount].function = function;
        commandCount++;
        sortCommands();
        return true;
    }
    return false;
}

bool CommandLibrary::removeCommand(const char *command) {
    int index = findCommand(command);
    if (index != -1) {
        for (int i = index; i < commandCount - 1; i++) {
            commands[i] = commands[i + 1];
        }
        commandCount--;
        return true;
    }
    return false;
}

void CommandLibrary::listCommands() {
    for (int i = 0; i < commandCount; i++) {
        shell.printToAll(commands[i].name);
        shell.printToAll("\n");
    }
}

bool CommandLibrary::executeCommand(const char *command, char *params) {
    int index = findCommand(command);
    if (index != -1) {
        commands[index].function(params);
        return true;
    }
    return false;
}

int CommandLibrary::findCommand(const char *command) {
    for (int i = 0; i < commandCount; i++) {
        if (strcmp(commands[i].name, command) == 0) {
            return i;
        }
    }
    return -1;
}

void CommandLibrary::sortCommands() {
    for (int i = 1; i < commandCount; i++) {
        Command key = commands[i];
        int j = i - 1;
        while (j >= 0 && strcmp(commands[j].name, key.name) > 0) {
            commands[j + 1] = commands[j];
            j--;
        }
        commands[j + 1] = key;
    }
}