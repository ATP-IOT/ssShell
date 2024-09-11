#include "internalCommands.h"
#include "ssSHell.h"

#define MAX_VARS 10
#define VAR_NAME_LENGTH 20
#define VAR_VALUE_LENGTH 50

struct EnvVar {
    char name[VAR_NAME_LENGTH];
    char value[VAR_VALUE_LENGTH];
};

EnvVar variables[MAX_VARS];
int varCount = 0;

void cmdHelp(char *params) {
    shell.printToAll("\nAvailable commands:\n");
    shell.listCommands();
}

void cmdVersion(char *params) {
    shell.printToAll("\nssSHell version 1.0\n");
}

void cmdEcho(char *params) {
    shell.printToAll(params);
    shell.printToAll("\n");
}

void cmdClear(char *params) {
    shell.printToAll("\033[2J\033[H");  // ANSI escape codes to clear screen and move cursor to home
}

void cmdSet(char *params) {
    char *name = strtok(params, "=");
    char *value = strtok(NULL, "");
    
    if (name && value) {
        for (int i = 0; i < varCount; i++) {
            if (strcmp(variables[i].name, name) == 0) {
                strncpy(variables[i].value, value, VAR_VALUE_LENGTH);
                shell.printToAll("Variable updated\n");
                return;
            }
        }
        
        if (varCount < MAX_VARS) {
            strncpy(variables[varCount].name, name, VAR_NAME_LENGTH);
            strncpy(variables[varCount].value, value, VAR_VALUE_LENGTH);
            varCount++;
            shell.printToAll("Variable set\n");
        } else {
            shell.printToAll("Error: Maximum number of variables reached\n");
        }
    } else {
        shell.printToAll("Usage: set NAME=VALUE\n");
    }
}

void cmdGet(char *params) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(variables[i].name, params) == 0) {
            shell.printToAll(variables[i].name);
            shell.printToAll("=");
            shell.printToAll(variables[i].value);
            shell.printToAll("\n");
            return;
        }
    }
    shell.printToAll("Variable not found\n");
}

void cmdInfo(char *params) {
    char buffer[64];
    
    shell.printToAll("Arduino Board: ");
    shell.printToAll(ARDUINO_BOARD);
    shell.printToAll("\nFree Memory: ");
    sprintf(buffer, "%d bytes\n", ESP.getFreeHeap());
    shell.printToAll(buffer);
}

void cmdPin(char *params) {
    char *operation = strtok(params, " ");
    char *pinStr = strtok(NULL, " ");
    char *valueStr = strtok(NULL, " ");
    
    if (!operation || !pinStr) {
        shell.printToAll("Usage: pin [read|write] PIN [VALUE]\n");
        return;
    }
    
    int pin = atoi(pinStr);
    
    if (strcmp(operation, "read") == 0) {
        pinMode(pin, INPUT);
        int value = digitalRead(pin);
        char buffer[32];
        sprintf(buffer, "Pin %d value: %d\n", pin, value);
        shell.printToAll(buffer);
    } else if (strcmp(operation, "write") == 0) {
        if (!valueStr) {
            shell.printToAll("Usage: pin write PIN VALUE\n");
            return;
        }
        int value = atoi(valueStr);
        pinMode(pin, OUTPUT);
        digitalWrite(pin, value);
        char buffer[32];
        sprintf(buffer, "Pin %d set to %d\n", pin, value);
        shell.printToAll(buffer);
    } else {
        shell.printToAll("Invalid operation. Use 'read' or 'write'.\n");
    }
}

// Helper function to get free memory
int freeMemory() {
    char top;
    return &top - reinterpret_cast<char*>(malloc(4));
}