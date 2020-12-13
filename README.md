# :sparkles: :santa: AdventOfCode2020 :christmas_tree: :candle: 

Solutions for [Advent Of Code 2020](http://adventofcode.com/2020) written in **C**

The descriptions of the daily tasks are in the comments in the `*.c` files (see `src/`).

The `*.txt` files in `input/` contain the original input for the tasks.

`main.exe` does all tasks and prints all solutions. It uses the input files in `input/`.

Use GCC to build `main.c` with the makefile provided.

![C/C++ CI](https://github.com/derpicknicker1/AdventOfCode2020/workflows/C/C++%20CI/badge.svg)
## Building in SublimeText3 (Win)

* Install Mingw
* Add `C:\MinGW\bin` to PATH
* Symlink `mklink C:\MinGW\bin\make.exe C:\MinGW\bin\mingw32-make.exe`
* In SublimeText **Tools > Build System > New Build System...**
  * Add the following code (also found in _Make_AOC.sublime-build_)
    ```yaml
    {
      "shell_cmd": "make",
      "working_dir": "${folder}",
     
      "variants": 
      [
          {
              "name": "Run",
              "shell_cmd": "make && ${folder}/main.exe skip"
          },
          {
              "name": "Clean",
              "shell_cmd": "make clean"
          }
      ]
    }
    ```
  * Save to `C:\Users\[$user]\AppData\Roaming\Sublime Text 3\Packages\User`
* Select this Build System in **Tools > Build System**
* Build with <kbd>Ctrl</kbd> + <kbd>B</kbd>
  * <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>B</kbd> to choose variant (e.g _run_)
