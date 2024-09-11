#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <Arduino.h>

class CommandParser {
public:
    CommandParser();
    bool parse(const char *input, char *command, char *params);

private:
    void trimWhitespace(char *str);
};

#endif