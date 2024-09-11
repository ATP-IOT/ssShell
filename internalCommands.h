#ifndef INTERNAL_COMMANDS_H
#define INTERNAL_COMMANDS_H

#include <Arduino.h>

void cmdHelp(char *params);
void cmdVersion(char *params);
void cmdEcho(char *params);
void cmdClear(char *params);
void cmdSet(char *params);
void cmdGet(char *params);
void cmdInfo(char *params);
void cmdPin(char *params);

#endif