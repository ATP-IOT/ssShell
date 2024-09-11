#ifndef COMMAND_LIBRARY_H
#define COMMAND_LIBRARY_H

#include <Arduino.h>

#define MAX_COMMANDS 50
#define MAX_COMMAND_LENGTH 20

class CommandLibrary {
public:
    CommandLibrary();
    bool addCommand(const char *command, void (*function)(char *));
    bool removeCommand(const char *command);
    void listCommands();
    bool executeCommand(const char *command, char *params);

private:
    struct Command {
        char name[MAX_COMMAND_LENGTH];
        void (*function)(char *);
    };

    Command commands[MAX_COMMANDS];
    uint8_t commandCount;

    int findCommand(const char *command);
    void sortCommands();
};

#endif