#include "CommandTokenizer.h"

CommandTokenizer::CommandTokenizer() : command(""), params(nullptr), paramCount(0) {}

void CommandTokenizer::parse(String input) {
    // Tokenización inicial: comando y parámetros
    int firstSpace = input.indexOf(' ');
    command = input.substring(0, firstSpace);
    String paramString = input.substring(firstSpace + 1);
    
    // Separar los parámetros por espacios o comas
    paramCount = 0;
    for (int i = 0; i < paramString.length(); i++) {
        if (paramString.charAt(i) == ' ' || paramString.charAt(i) == ',') {
            paramCount++;
        }
    }
    paramCount++;  // Añadir el último parámetro

    params = new String[paramCount];
    int currentIndex = 0;
    while (paramString.length() > 0) {
        int spaceIndex = paramString.indexOf(' ');
        if (spaceIndex == -1) {
            params[currentIndex++] = paramString;
            paramString = "";
        } else {
            params[currentIndex++] = paramString.substring(0, spaceIndex);
            paramString = paramString.substring(spaceIndex + 1);
        }
    }
}

String CommandTokenizer::getCommand() {
    return command;
}

int CommandTokenizer::getParamCount() {
    return paramCount;
}

String CommandTokenizer::getParam(int index) {
    if (index < 0 || index >= paramCount) {
        return "";  // Error de índice fuera de rango
    }
    return params[index];
}

int CommandTokenizer::getParamAsInt(int index, bool& success) {
    String param = getParam(index);
    success = param.toInt() != 0 || param == "0";
    return param.toInt();
}

float CommandTokenizer::getParamAsFloat(int index, bool& success) {
    String param = getParam(index);
    success = param.toFloat() != 0.0 || param == "0.0";
    return param.toFloat();
}

double CommandTokenizer::getParamAsDouble(int index, bool& success) {
    String param = getParam(index);
    success = param.toDouble() != 0.0 || param == "0.0";
    return param.toDouble();
}

char CommandTokenizer::getParamAsChar(int index, bool& success) {
    String param = getParam(index);
    success = param.length() == 1;
    return param.charAt(0);
}

bool CommandTokenizer::getParamAsBool(int index, bool& success) {
    String param = getParam(index);
    if (param == "true" || param == "1") {
        success = true;
        return true;
    } else if (param == "false" || param == "0") {
        success = true;
        return false;
    }
    success = false;
    return false;
}

String CommandTokenizer::getParamAsString(int index) {
    return getParam(index);
}

CommandTokenizer::~CommandTokenizer() {
    delete[] params;
}
