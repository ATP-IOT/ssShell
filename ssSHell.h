#ifndef SSSHELL_H
#define SSSHELL_H

#include <Arduino.h>
#include "commandParser.h"
#include "commandLibrary.h"

#define MAX_INPUT_LENGTH 128
#define MAX_PROMPT_LENGTH 32
#define MAX_SERIALS 5

class SsShell {
public:
    SsShell();
    void begin(Stream &serial);
    void loop();
    bool addCommand(const char *command, void (*function)(char *));
    bool removeCommand(const char *command);
    void listCommands();
    void setPrompt(const char *prompt);
    bool addSerial(Stream &serial);
    bool removeSerial(Stream &serial);
    void printToAll(const char* message);
    void executeCommand(const char *command, const char *params);

private:
    CommandParser parser;
    CommandLibrary library;
    Stream* serials[MAX_SERIALS];
    uint8_t serialCount;
    char prompt[MAX_PROMPT_LENGTH];
    char inputBuffer[MAX_INPUT_LENGTH];
    uint8_t inputIndex;

    void processInput();
    void printPrompt();
};

extern SsShell shell;

#endif