🎮 Treasure Hunter Pathfinder – C++ Console Game

This is a small C++ project I built to practice pathfinding algorithms, random maze generation, and file handling. It’s a fun console-based mini-game where you try to reach the treasure in a randomly generated maze.
You can explore manually or let the computer find the shortest path using BFS or A*.

🌟 Why I Built This Project

I made this project to improve my:

C++ logic building

Understanding of BFS & A* pathfinding

Working with persistent storage (scores.txt)

Handling keyboard input and console animation

Game-based problem solving

It was a great learning experience and really fun to create!

🚀 Features

Random maze generation every level

BFS & A* pathfinding visualized step-by-step

Increasing difficulty with bigger mazes

Leveling system with score calculation

Persistent high score saved locally

Smooth console animation

Simple & clean gameplay

🎮 Controls
Key	Action
W A S D	Move player
R	Show BFS path
X	Show A* path
G	Generate new maze
Q	Quit game
🏗️ Tech Used

C++ (C++17)

STL (vectors, queue, priority queue, etc.)

File handling

Random maze generation

Basic console UI

BFS & A* algorithms

🛠️ How to Run
Compile:
g++ treasure_hunter.cpp -o treasure_hunter -std=c++17

Run:

Windows:

treasure_hunter.exe


Linux:

./treasure_hunter

📁 Project Structure
📁 Project Folder
│
├── treasure_hunter.cpp      # Main game source
├── scores.txt               # Stores high score + max level
├── treasure_hunter.exe      # Windows build (optional)
└── .vscode/                 # Config (optional)

📸 Preview (Console Sample)
######################
#....#....#.......#..#
#..P.#.##.#.###.#.#..#
#....#....#.....#....T
######################

🏆 Scoring

Score depends on:

Level number

Time taken

Speed bonus

Formula:

levelScore = max(50, 500 / (seconds + 1)) + (level * 20)

✨ Future Improvements I May Add

Colorful console output

Enemy movement

Power-ups

Maze themes

Save full gameplay history

👤 Author

Arshita Bhikhadiya
Built for learning, fun, and improving my C++ skills ❤️
