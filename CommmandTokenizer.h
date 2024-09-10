#ifndef COMMAND_TOKENIZER_H
#define COMMAND_TOKENIZER_H

#include <Arduino.h>

class CommandTokenizer {
private:
    String command;
    String* params;
    int paramCount;

public:
    CommandTokenizer();
    void parse(String input);
    String getCommand();
    int getParamCount();
    String getParam(int index);

    // Métodos para obtener parámetros en diferentes tipos
    int getParamAsInt(int index, bool& success);
    float getParamAsFloat(int index, bool& success);
    double getParamAsDouble(int index, bool& success);
    char getParamAsChar(int index, bool& success);
    bool getParamAsBool(int index, bool& success);
    String getParamAsString(int index);

    // Destructor para liberar memoria
    ~CommandTokenizer();
};

#endif
