#LR Parser in C

## Overview

This project implements a simple LR parser C. The parser is driven by external grammar rules, action tables, and goto tables. The main source file is `lrParser.c`, and it is supported by several additional source and header files:

- `grammar.h`
- `string_queue.h`, `string_queue.c`
- `string_stack.h`, `string_stack.c`
- `tree.h`, `tree.c`

These supporting files provide essential data structures used by the parser.

## Setup Instructions

1. Set up a C compiler (e.g. GCC)
2. Clone or download the project files.
3. Open the project folder in your IDE (e.g. Visual Studio Code).
4. Set up your `tasks.json` and `launch.json` for build and debugging.

### tasks.json

```json
{
    "version": "2.0.0",
    "tasks": [
      {
        "label": "build LR Parser program",
        "type": "shell",
        "command": "gcc",
        "args": [
          "-g",
          "lrParser.c",
          "string_stack.c",
          "string_queue.c",
          "tree.c",
          "-o",
          "lrParser"
        ],
        "group": {
          "kind": "build",
          "isDefault": true
        },
        "problemMatcher": [
          "$gcc"
        ],
        "detail": "Build all files into lrParser"
      }
    ]
  }
  
```

> Make sure all relevant source files are included in the build task.
> 

### launch.json

```json
{
    "version": "0.2.0",
    "configurations": [
      {
        "name": "Debug lrParser",
        "type": "cppdbg",
        "request": "launch",
        "program": "${workspaceFolder}/lrParser",  // Path to the compiled binary
        "args": [],  // Add command-line arguments here if needed
        "stopAtEntry": false,
        "cwd": "${workspaceFolder}",
        "environment": [],
        "externalConsole": true,  // Set to true if you want an external console
        "MIMode": "lldb",  // Or "lldb" depending on your system and debugger
        "preLaunchTask": "build LR Parser program"  // This matches your task label
      }
    ]
  }
  
```

> Ensure the `preLaunchTask` field matches the label in `tasks.json`.
> 

## Running the Parser

In `lrParser.c`, update the file paths for your grammar, action, goto, and input files:

```c
char*** actionTable = readFile("PathToActionTable.txt", &aRows, &aCols);
char*** goToTable = readFile("PathToGotoTable.txt", &goRows, &goCols);
Grammar* grammarTable = readGrammar("PathToGrammar.txt");
Queue input = getInput("PathToinput.txt");
   
```

> Replace the `"PathTo..."` strings with actual paths to your `.txt` files.

Sample inputs created by [Beyza Eken](github.com/beken) are provided in the `inputs` folder

## Execution

### 1. From a code editor:

To run the parser:

1. Build the project using the task: **build LR Parser program**.
2. Start debugging using the **Debug lrParser** configuration in your editor.

### 2. From a CLI

To run the parser:

1. Build the project from it’s root folder with the following command

```c
gcc -g lrParser.c string_stack.c string_queue.c tree.c -o lrParser
```

1. Run the executable

> MacOS X `./lrParser`
> 

> Windows `.\lrParser`
> 

## Samples of the code running

### Correct input - input1.txt

```c
id + id * id $
```

Parsing result for correct input (provided input1.txt)

![Screenshot 2025-05-04 at 19.45.19.png](attachment:616b8d3b-5094-4800-84af-4904e55b5add:Screenshot_2025-05-04_at_19.45.19.png)

### Correct input - input2.txt

```c
id * id + id $
```

Parsing result for correct input (provided input2.txt)

![Screenshot 2025-05-04 at 19.47.22.png](attachment:d4e5f941-176d-44e3-95cc-2c1be26e12e5:Screenshot_2025-05-04_at_19.47.22.png)

### Incorrect input - input7.txt

```c
id + * id $
```

Parsing result for incorrect input (provided input7.txt)

![Screenshot 2025-05-04 at 19.49.38.png](attachment:fae1e652-6dc8-4c22-a7fd-b4bab787ff41:Screenshot_2025-05-04_at_19.49.38.png)

### Incorrect input - input9.txt

```c
( id + id ) * ( id - id ) + id * id $
```

Parsing result for incorrect input (provided input9.txt)

![Screenshot 2025-05-04 at 19.51.09.png](attachment:ea607eee-a9bc-4302-ae5f-9ae2fd246671:Screenshot_2025-05-04_at_19.51.09.png)