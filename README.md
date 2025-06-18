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
- `WASD`, `Q`, `H`, `O`, `SPACE`, etc., control player interaction.
- A custom `Key` enum maps inputs to actions.
## 4. Undo/Redo Stack
- `Pos Undo[DEPTH]` and `Redo[DEPTH]` arrays for undo/redo functionality.
  
<p align="right">(<a href="#readme-top">back to top</a>)</p>

---
## Demo
Short video showing actual gameplay:

https://github.com/user-attachments/assets/661318fa-0bd8-47aa-8a43-141a1142064d

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
After launching the game, you control the cursor and interact with the board using your keyboard. 
Below are the keyboard controls for the game:

## 1. Controls

| Key | Action |
|-------------|-------------|
| `W` `A` `S` `D` | Move cursor (Up, Left, Down, Right) |
| `SPACE` | Shoot a ray from the edge |
| `O` | Mark a cell as a suspected atom |
| `U` | Undo last mark |
| `R` | Redo previously undone mark |
| `H` | Show a brief hint (reveal atoms) |
| `Q` | Return to main menu |
| `K` | End the current game |

All keys must be followed by `Enter` to take effect.

## 2. Game Objective

Use logic and observation to find all hidden atoms on the board by shooting rays into the grid:
- `H` - Hit: Ray directly hit an atom
- `R` - Reflected: Atom nearby deflected the ray
- `a`, `b`, `c` - Ray passed through from entry to exit
  
Mark the suspected atom locations with `o`, and finish the game with `K` when you're confident.

## 3. After Game Symbols Legend

| Symbol | Meaning |
|-------------|-------------|
| `*` |	Actual atom (only visible in reveal/help) |
| `O` |	Correctly marked atom |
| `X` |	Incorrectly marked cell |
