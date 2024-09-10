# ssShell

Esta biblioteca está diseñada para ser utilizada con Arduino y permite la creacion de interfaces de comando personalizadas.

## Comandos

Los comandos son las instrucciones que se pueden ejecutar en la shell. Cada comando tiene un nombre único y puede tener uno o más parámetros.

### Parámetros

Los parámetros son los valores que se pasan a cada comando cuando se ejecuta. Los parámetros pueden ser de diferentes tipos, como números enteros o flotantes.

## Comando Tokenizer

El CommandTokenizer es una herramienta que ayuda a dividir las entradas del usuario en comandos y parámetros individuales.

## Ejemplo básico

```cpp
#include "ssShell.h"

void miComando(void**) {
    Serial.println("Se ejecutó el comando 'miComando'");
}

int main() {
    Shell shell;
    shell.addCommand("miComando", "", miComando);
    while (true) {
        String input = Serial.readStringUntil('\n');
        if (shell.executeCommand(input)) {
            Serial.println("Se ejecutó el comando con éxito");
        } else {
            Serial.println("Error al ejecutar el comando");
        }
    }

    return 0;
}
```
