<a id="readme-top"></a>


<br />
<div align="center">
  <h1 align="center">BlackBox Board Game</h1>
  <p align="center">
    A C++ program that enables you to play the classic Black Box game in the terminal, with real-time keyboard interaction and ASCII-based board rendering.
    <br />  
  </p>
</div>

---

## Table of Contents
- [About The Project](#about-the-project)
- [Demo](#Demo)
- [Built With](#built-with)
- [Prerequisites](#Prerequisites)
- [Installation](#Installation)
- [Usage](#Usage)


---

## About The Project

This project is a console-based implementation of the classic Black Box game, written in C++. The player interacts with a hidden grid containing atoms, using strategic probes fired from the edges to deduce the atoms' positions through the behavior of the rays.

The core gameplay mechanics are inspired by the original Black Box board game, where players analyze how rays are absorbed, reflected, or deflected to logically infer the hidden layout.

🔗 Learn more about the original game concept: https://en.wikipedia.org/wiki/Black_Box_(game)

## Features:

## 1. Core Game Logic
- Initializes a board with random "atoms".
- Allows the player to move a cursor with `WASD`.
- Supports shooting laser beams into the board, detecting:
  - Hit (when a beam hits an atom directly).
  - Reflection (beam is reflected due to adjacent atoms).
  - Pass-through (beam exits from another edge).
## 2. Board Visualization
- Dynamically draws a board with ASCII characters.
- Visibility levels (`visability` flag) determine what the player sees.
## 3. Input Handling
- `WASD`, `Q`, `H`, `O`, `spacebar`, etc., control player interaction.
- A custom `Key` enum maps inputs to actions.
## 4. Undo/Redo Stack
- `Pos Undo[DEPTH]` and `Redo[DEPTH]` arrays for undo/redo functionality.
  
<p align="right">(<a href="#readme-top">back to top</a>)</p>

---
## Demo

## Built With

| Language | Description |
|----------|-------------|
| 🟦 **C++** | Core language used for all game logic, board control, and system functions. |

| Library | Description |
|----------|-------------|
| `<Windows.h>` | Provides access to Windows-specific API functions (e.g., console manipulation, sleep, system calls). |
| `<stdlib.h>` | Standard utility functions like memory allocation, random number generation (`rand()`), and program control. |
| `<time.h>` | Used for seeding random number generators (`srand(time(NULL))`) and managing time-related functions. |
| `<conio.h>` | Enables keyboard input handling with functions like `getch()` and `kbhit()` for real-time interaction. |


<p align="right">(<a href="#readme-top">back to top</a>)</p>

---


### Prerequisites

| Requirement | Description |
|-------------|-------------|
| **C++ compiler** | Working C++ compiler (e.g. `g++`) |
| **Terminal** | Command line to compile and run the program |
| **Programming environment** | Visual Studio Code, CLion, or any other IDE for editing and testing the code |

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Installation

Clone the repository and change directory:

```bash
git clone https://github.com/DexusY/BlackBox-Board-Game---Gra-Planszowa-BlackBox.git
cd BlackBox-Board-Game---Gra-Planszowa-BlackBox
```


Compile the project (example for Wnidows using MinGW):

```bash
g++ main.cpp -o 
```

Or open `main.cpp` in your preferred programming environment (e.g., Visual Studio Code) and build/run the program from there

### Usage
