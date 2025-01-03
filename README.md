#ENG
This code implements a simple text-based game in C++ called "Black Box," where the player interacts with a grid-based board. 
The program utilizes console graphics and cursor manipulation to create a visual representation of the game state. 
Below is a high-level summary and breakdown:

Key Features
Game State Management:
The game operates in different states: menu, play, and ended.
State transitions are handled within a game loop.

Player Interaction:
The player moves a cursor (Pos structure) on the grid using WASD keys.
Actions include moving, shooting, placing markers, undoing, and accessing help.

Board Representation:
The Board structure holds a 2D grid to represent game elements.
Cells can contain atoms (1), player markers (2 or 3), or be empty.

Visuals and Cursor Control:
Uses Windows-specific console functions (SetConsoleCursorPosition) to manipulate the cursor and draw game elements.
Draws a grid with borders and corner characters for a polished look.

Gameplay Mechanics:
Atom Placement: Randomly distributed on the grid.
Shoot Functionality: Simulates shooting a laser beam along the edges to detect atoms indirectly.
Undo/Redo: Supports limited history for undoing moves.

Menu System:
Provides options to start new games with varying grid sizes and atom counts.

---------------------------------------------------------------------------------------------------------------------------
#PL
Interakcja gracza:
Gracz porusza kursorem (struktura Pos) na siatce przy użyciu klawiszy WASD 

Dostępne akcje:
-Ruch kursora
-Strzał (laserem) wzdłuż krawędzi planszy.
-Umieszczanie znaczników (markerów).
-Cofanie akcji (undo).
-Wyświetlanie pomocy.
-Reprezentacja planszy
-Struktura Board przechowuje planszę jako 2D siatkę.
-Każda komórka planszy może zawierać:
-Atom (1).
-Znacznik gracza (2 lub 3).
-Pole puste.

Wizualizacje i sterowanie kursorem:
Gra wykorzystuje funkcje konsolowe systemu Windows, takie jak SetConsoleCursorPosition, do kontrolowania kursora.
Tworzy wizualną reprezentację planszy z obramowaniem i charakterystycznymi rogami dla lepszego wyglądu.

Mechanika gry:
Rozmieszczenie atomów: Atomów na planszy jest losowa liczba, ustalana przy rozpoczęciu gry.
Funkcja strzału: Symuluje strzał laserem z krawędzi planszy, aby pośrednio wykryć atomy.
Cofanie/ruch wstecz: Obsługuje historię ruchów gracza, umożliwiając cofanie akcji.

System menu:
W menu dostępne są opcje, takie jak rozpoczęcie nowej gry z różnymi:
Rozmiarami planszy, Liczbą atomów.
