![Ultra Deluxe Chess](https://github.com/mosmar99/ChessProjectClass/blob/main/chess_pic.png "Ultra Deluxe Chess")
___
# ChessProjectClass

## Collaborators
* Mahmut Osmanovic (mosmar99)
* Linus Savinainen (Linkan42)
* Besan Ewir (beew77)
* Isac Paulsson (isacpaulsson)
* Sebastian Tuura (tuura01)

## Project Description
A chess game. Either player vs. player or player vs. engine. The engine runs on an AI algorithm, more specifically, the min-max algorithm. Users may choose whether they desire to play through the CLI or GUI. <br />
[Link to kanban board](https://github.com/users/mosmar99/projects/2)

## Programming languages
Python for UI. <br />
Game logic and AI in C.

## Build System
To be decided. Currently VSC (Visual Studio Code) extension programs are being utilized. More precisely Microsofts CMake Tools extension. Users are in addition expected to have a C-compiler installed. For example, The GNU Compiler Collection (GCC), which includes The C Standard Library, The GNU Project Debugger  (GDB), and the "build tool" GNU MAKE.

## VSCode setup
You need to have .vscode files setup to run it, which are individually configured.<br />
- Windows: https://code.visualstudio.com/docs/cpp/config-mingw<br />
- Mac: https://code.visualstudio.com/docs/cpp/config-clang-mac<br />
- Linux: https://code.visualstudio.com/docs/cpp/config-linux<br />

**Sample Configuration (Ubuntu 20.4 LTS)**<br />
Look at already configured files (.vscode) found within map ".vscode". These are working configurations in Ubuntu, version 20.4 LTS. Since local compiler paths are PC dependent, one might need to update certain fields by hand. The fields in question are: "compilerPath": in c_cpp_properties.json, put gcc path. "command" in tasks, put gcc path. Lastly, within "launch.json" file, locate the field "miDebuggerPath" and put your own debugger path (gdb).

Execute each row below, one by one, in your terminal (Command Prompt (CMD) on Windows, Terminal on Mac and The Shell on Ubuntu), which will install Visual Studio Code Extensions for C:

- code --install-extension ms-vscode.cpptools
- code --install-extension ms-vscode.makefile-tools

## Linter instructions for Github Action
- https://github.com/marketplace/actions/c-c-linter <br />
- [![cpp-linter](https://github.com/cpp-linter/cpp-linter-action/actions/workflows/cpp-linter.yml/badge.svg)](https://github.com/cpp-linter/cpp-linter-action/actions/workflows/cpp-linter.yml) 

## Linter instructions to linter C/C++ code from terminal
- Manual: https://clang.llvm.org/docs/ClangFormat.html
- Download on Ubuntu: sudo apt install clang-format
- Command to format: ```clang-format FILE```

## Instructions for running unit tests
To run the the unit tests for the Queen piece enter the following into the cmd while being in the project folder:

    gcc -fprofile-arcs -ftest-coverage test\testQueen.c src\knight.c src\makeBoard.c src\makeMove.c src\pawn.c src\queen.c src\Rook.c -I include -o test\testQueen.exe

Now run the exe generated:

    test\testQueen.exe

A message displaying "valid" should now be visable.
To see the code coverage enter the following:

    gcov test\testQueen-queen.gcda
    
OR: If one prefers to run the test autonomously, that is also possible through the make file. <br />
Using the terminal whilst within the workspaceFolder enter command:

    make testSelfCapture
There will be two types of output. Firstly the tests will be ran, secondly, its code-coverage will be outputed.

## Declarations
I, Isac Paulsson, declare that I am the sole author of the content I add to this repository. <br />
I, Mahmut Osmanovic, declare that I am the sole author of the content I add to this repository. <br />
I, Linus Savinainen, declare that I am the sole author of the content I add to this repository. <br />
I, Besan Ewir, declare that I am the sole author of the content I add to this repository. <br />
I, Sebastian Tuura, declare that I am the sole author of the content I add to this repository. <br />
