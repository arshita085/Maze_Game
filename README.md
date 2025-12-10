# 🎮 Treasure Hunter Pathfinder (C++ Game)

✦ This is a small C++ project I built to practice pathfinding algorithms, random maze generation, and file handling. It’s a fun console-based mini-game where you try to reach the treasure in a randomly generated maze.
You can explore manually or let the computer find the shortest path using BFS or A*.

🌟 Why I Built This Project

● I made this project to improve my:

● C++ logic building

● Understanding of BFS & A* pathfinding

● Working with persistent storage (scores.txt)

● Handling keyboard input and console animation

● Game-based problem solving

~ It was a great learning experience and really fun to create!

A console-based maze adventure game built in **C++**, featuring:

✨ Randomly generated mazes\
✨ BFS & A\* pathfinding\
✨ Increasing level difficulty\
✨ Persistent scoring saved to `scores.txt`\
✨ Smooth animations\
✨ Cross-platform support (Windows/Linux)

------------------------------------------------------------------------

## 🚀 Features

### 🔹 Maze Generation

-   Each level generates a **new random maze**
-   Increasing maze **size** and **obstacle density** as difficulty
    rises
-   Guaranteed solvable maze using BFS validation

### 🔹 Algorithms Included

  Algorithm                        Purpose
  -------------------------------- -------------------------------------
  **BFS (Breadth-First Search)**   Shortest path in equal-weight grid
  **A\***                          Optimal heuristic-based pathfinding

### 🔹 Dynamic Level System

Tracks: - Level\
- Max level reached\
- High score

### 🔹 Persistent Scoring

Stored in `scores.txt`:

    <highScore> <maxLevel>

### 🔹 Keyboard Controls

  Key           Action
  ------------- -------------------------
  **W A S D**   Move player
  **R**         Show BFS path animation
  **X**         Show A\* path animation
  **G**         Generate new maze
  **Q**         Quit game

------------------------------------------------------------------------

## 🛠️ Installation & Setup

### 1️⃣ Compile

    g++ treasure_hunter.cpp -o treasure_hunter -std=c++17

### 2️⃣ Run

Windows:

    treasure_hunter.exe

Linux:

    ./treasure_hunter

------------------------------------------------------------------------

## 🗂️ Project Structure

    📁 Project Folder
    │
    ├── treasure_hunter.cpp
    ├── treasure_hunter.exe
    ├── scores.txt
    └── .vscode/
        ├── c_cpp_properties.json
        ├── launch.json
        └── settings.json

------------------------------------------------------------------------

## 📸 Game Preview

    ######################
    #....#....#.......#..#
    #..P.#.##.#.###.#.#..#
    #....#....#.....#....T
    ######################

    Level: 1 | Size: 10x20
    Score: 0 | High Score: 1500
    Commands: WASD | r=BFS | x=A* | g=regen | q=quit

------------------------------------------------------------------------

## 📈 Scoring Logic

    levelScore = max(50, 500 / (seconds + 1)) + (level * 20)

------------------------------------------------------------------------

👤 Author

Arshita Bhikhadiya
Built for learning, fun, and improving my C++ skills ✨
