# Simple Linux Shell

**Author:** Daniel Boland  
**Course:** 3460:4/526 Operating Systems Lab 1  
**Date:** 2026-03-09  

---

## Overview

This project implements a simple command-line shell for Linux. The shell allows the user to execute programs, manipulate files, and navigate the system using a limited set of built-in commands. The shell is written in **C++** using standard C++ libraries and POSIX system calls.

---

## Features

The shell supports the following built-in commands:

| Command | Description |
|---------|-------------|
| `C file1 file2` | Copy `file1` to `file2` (without deleting the original). |
| `D file` | Delete the specified file. |
| `E comment` | Echo the comment on the screen. Multiple spaces/tabs are reduced to a single space. |
| `H` | Display this help manual. |
| `L` | List contents of the current directory: first prints the working directory (`pwd`), then lists files in long form (`ls -l`). |
| `M file` | Create or edit the named text file using the `nano` text editor. |
| `P file` | Print the contents of the specified file using `more`. |
| `Q` | Quit the shell. |
| `W` | Clear the terminal screen. |
| `X program [args...]` | Execute the specified program with optional arguments. |

Any other command typed without a built-in prefix will be executed directly using the system’s `execvp()`.

---

## How to Compile and run

1. Open a Linux terminal in the project directory.  
2. Compile the source code using the provided Makefile:

```bash
make
```
3. Run the shell with

```bash
make run
```
