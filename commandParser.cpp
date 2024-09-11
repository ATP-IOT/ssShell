#include "commandParser.h"

CommandParser::CommandParser() {}

bool CommandParser::parse(const char *input, char *command, char *params) {
    const char *space = strchr(input, ' ');
    if (space == NULL) {
        strcpy(command, input);
        params[0] = '\0';
    } else {
        size_t commandLength = space - input;
        strncpy(command, input, commandLength);
        command[commandLength] = '\0';
        strcpy(params, space + 1);
    }
    
    trimWhitespace(command);
    trimWhitespace(params);
    
    return strlen(command) > 0;
}

void CommandParser::trimWhitespace(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';
}