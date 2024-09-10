# ssShell: A Shell Library for Arduino

![image](https://github.com/user-attachments/assets/802f6941-a08c-4b4c-a961-6bed1369d0dc)


## Description
The ssShell library is a tool for creating command-line interfaces on Arduino-based devices. It allows you to define custom commands and execute instructions based on user input.

## Key Features

*   Custom command definition with parameters
*   Support for basic data types (int, float)
*   Parameter validation and conversion at runtime
*   Intended use with Arduino

## Usage

To use the ssShell library, follow these steps:

1.  Create a `ssShell` object to initialize the command system.
2.  Define custom commands using the `addCommand` function.
3.  Use the `executeCommand` function to execute instructions based on user input.

## Advanced Example

```cpp
#include <ssShell.h>

ssShell shell;  // Crear una instancia de la clase Shell

// Función para el comando "move"
void moveFunction(void** args) {
    int* x = (int*)args[0];
    int* y = (int*)args[1];
    float* speed = (float*)args[2];
    
    Serial.print("Moving to X: ");
    Serial.print(*x);
    Serial.print(", Y: ");
    Serial.print(*y);
    Serial.print(" at speed: ");
    Serial.println(*speed);
}

// Función para el comando "rotate"
void rotateFunction(void** args) {
    int* angle = (int*)args[0];
    bool* clockwise = (bool*)args[1];

    Serial.print("Rotating to angle: ");
    Serial.print(*angle);
    Serial.print(" degrees, direction: ");
    Serial.println(*clockwise ? "Clockwise" : "Counter-Clockwise");
}

// Función para el comando "setSpeed"
void setSpeedFunction(void** args) {
    float* speed = (float*)args[0];
    
    Serial.print("Setting speed to: ");
    Serial.println(*speed);
}

void setup() {
    Serial.begin(9600);

    // Agregar los comandos con sus parámetros y funciones
    shell.addCommand("move", "int int flo", moveFunction);  // Comando con dos enteros y un float
    shell.addCommand("rotate", "int boo", rotateFunction);  // Comando con un entero y un booleano
    shell.addCommand("setSpeed", "flo", setSpeedFunction);  // Comando con un float
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');

        // Intentar ejecutar el comando ingresado
        if (!shell.executeCommand(input)) {
            Serial.println("Error: Invalid command or parameters.");
        }
    }
}
```

## Documentation

The ssShell library consists of the following functions and variables:

*   `ssShell()`: Constructor to initialize the command system
*   `addCommand(String name, String paramTypes, CommandFunction function)`: Add a custom command to the system
*   `executeCommand(String input)`: Execute instructions based on user input
*   `~ssShell()`: Destructor to release resources

## Contribution

If you'd like to contribute to the ssShell library, please review the source code and open issues on GitHub. You can submit your proposals for change or correction via pull request.

### Note
Please note that this is an initial version of the documentation and may contain errors or omissions. If you find any problems or have suggestions, please don't hesitate to contact the developers.
```
