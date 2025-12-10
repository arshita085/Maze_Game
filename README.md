# 🎮 Treasure Hunter Pathfinder (C++ Game)

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

## 🤝 Contributing

Pull requests are welcome.

------------------------------------------------------------------------

## 📜 License

You may add your preferred license (MIT recommended).
