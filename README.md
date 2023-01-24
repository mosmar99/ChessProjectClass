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
Look at already configured files (.vscode) found within map ".vscode". These are working configurations in Ubuntu, version 20.4 LTS. Since local compiler paths are PC dependent one would need to updated certain fields manually. The fields in question are: "compilerPath": in c_cpp_properties.json, put gcc path. "command" in tasks, put gcc path. Lastly, within "launch.json" file, locate the field "miDebuggerPath" and put your own debugger path (gdb).

Execute each row below, one by one, in your terminal (Command Prompt (CMD) on Windows, Terminal on Mac and The Shell on Ubuntu), which will install Visual Studio Code Extensions for C:

- code --install-extension ms-vscode.cpptools
- code --install-extension ms-vscode.makefile-tools

## Declarations
I, Isac Paulsson, declare that I am the sole author of the content I add to this repository. <br />
I, Mahmut Osmanovic, declare that I am the sole author of the content I add to this repository. <br />
I, Linus Savinainen, declare that I am the sole author of the content I add to this repository. <br />
I, Besan Ewir, declare that I am the sole author of the content I add to this repository. <br />
I, Sebastian Tuura, declare that I am the sole author of the content I add to this repository. <br />
