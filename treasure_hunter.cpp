// treasure_hunter_persistent.cpp
// Treasure Hunter Pathfinder - Persistent Score Edition 💾
// Compile: g++ treasure_hunter_persistent.cpp -o treasure_hunter -std=c++17
// Run: ./treasure_hunter   (Windows: treasure_hunter.exe)

#include <bits/stdc++.h>
#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
#else
  #include <termios.h>
  #include <unistd.h>
  int _getch(){ struct termios oldt, newt; int ch; tcgetattr(STDIN_FILENO,&oldt); newt = oldt; newt.c_lflag &= ~(ICANON|ECHO); tcsetattr(STDIN_FILENO,TCSANOW,&newt); ch = getchar(); tcsetattr(STDIN_FILENO,TCSANOW,&oldt); return ch; }
  void Sleep(int ms){ usleep(ms*1000); }
#endif

using namespace std;
using namespace chrono;

// ---------------------------------------------
// Data Structures
// ---------------------------------------------
struct Node { int x, y; };
struct AStarNode {
    int x, y, g, f;
    bool operator<(AStarNode const& o) const { return f > o.f; }
};

// ---------------------------------------------
// Globals
// ---------------------------------------------
int N = 10, M = 20;
double obstacle_density = 0.20;
int level = 1;
int totalScore = 0;
int highScore = 0;
int maxLevel = 1;
string scoreFile = "scores.txt";

vector<string> grid;
Node player, treasure;
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

random_device rd;
mt19937 gen(rd());

// ---------------------------------------------
// Utility Messages
// ---------------------------------------------
vector<string> success_msgs = {
    "🎉 Excellent! You found the treasure!",
    "🏆 You conquered this maze!",
    "🌟 Great job, hero!",
    "🔥 You cleared this level like a pro!",
    "💎 Treasure collected successfully!",
    "🗺️ Another maze mastered!"
};
vector<string> levelup_msgs = {
    "🚀 Level Up! Get ready for a tougher maze!",
    "⚔️ Advancing to next challenge!",
    "🧠 Let’s see if you can handle the next one!",
    "🌋 Maze expanding... brace yourself!",
    "🎯 Onward to Level "
};

string randomMsg(const vector<string>& v) {
    uniform_int_distribution<int> d(0, (int)v.size()-1);
    return v[d(gen)];
}

// ---------------------------------------------
// File Handling
// ---------------------------------------------
void loadScores() {
    ifstream in(scoreFile);
    if (in) {
        in >> highScore >> maxLevel;
        in.close();
    }
    else {
        highScore = 0;
        maxLevel = 1;
    }
}

void saveScores() {
    ofstream out(scoreFile);
    out << highScore << " " << maxLevel;
    out.close();
}

// ---------------------------------------------
// Utility Functions
// ---------------------------------------------
bool validCell(int x, int y, const vector<string>& g) {
    return x >= 0 && x < N && y >= 0 && y < M && g[x][y] != '#';
}

void printGrid(const vector<string>& g) {
    system("cls");
    for (const auto& row : g) cout << row << "\n";
    cout << "\nLevel: " << level << " | Size: " << N << "x" << M
         << " | Density: " << obstacle_density
         << "\n💰 Score: " << totalScore
         << " | 🏆 High Score: " << highScore
         << " | Max Level: " << maxLevel << "\n";
    cout << "Commands: WASD=move | r=BFS | x=A* | g=regen | q=quit\n";
}

// ---------------------------------------------
// BFS + A*
// ---------------------------------------------
vector<Node> bfs_path(const vector<string>& g, Node start, Node goal) {
    vector<vector<bool>> vis(N, vector<bool>(M,false));
    vector<vector<Node>> parent(N, vector<Node>(M, {-1,-1}));
    queue<Node> q;
    q.push(start); vis[start.x][start.y] = true;

    while(!q.empty()){
        Node cur = q.front(); q.pop();
        if (cur.x == goal.x && cur.y == goal.y) {
            vector<Node> path;
            Node p = cur;
            while (!(p.x == -1 && p.y == -1)) {
                path.push_back(p);
                p = parent[p.x][p.y];
            }
            reverse(path.begin(), path.end());
            return path;
        }
        for(int i=0;i<4;i++){
            int nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (validCell(nx,ny,g) && !vis[nx][ny]) {
                vis[nx][ny] = true;
                parent[nx][ny] = cur;
                q.push({nx,ny});
            }
        }
    }
    return {};
}

int manhattan(Node a, Node b){ return abs(a.x-b.x) + abs(a.y-b.y); }

vector<Node> astar_path(const vector<string>& g, Node start, Node goal) {
    const int INF = 1e9;
    vector<vector<int>> gscore(N, vector<int>(M, INF));
    vector<vector<Node>> parent(N, vector<Node>(M, {-1,-1}));
    priority_queue<AStarNode> pq;
    gscore[start.x][start.y] = 0;
    pq.push({start.x, start.y, 0, manhattan(start,goal)});

    while(!pq.empty()){
        AStarNode cur = pq.top(); pq.pop();
        if (cur.x == goal.x && cur.y == goal.y) {
            vector<Node> path;
            Node p = {cur.x, cur.y};
            while (!(p.x == -1 && p.y == -1)) {
                path.push_back(p);
                p = parent[p.x][p.y];
            }
            reverse(path.begin(), path.end());
            return path;
        }
        if (cur.g != gscore[cur.x][cur.y]) continue;
        for(int i=0;i<4;i++){
            int nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (!validCell(nx,ny,g)) continue;
            int tentative = cur.g + 1;
            if (tentative < gscore[nx][ny]) {
                gscore[nx][ny] = tentative;
                parent[nx][ny] = {cur.x, cur.y};
                int f = tentative + manhattan({nx,ny}, goal);
                pq.push({nx,ny, tentative, f});
            }
        }
    }
    return {};
}

// ---------------------------------------------
// Maze Generator
// ---------------------------------------------
void generateGrid() {
    uniform_real_distribution<> dis(0.0,1.0);
    while (true) {
        grid.assign(N, string(M, '.'));
        for (int i = 0; i < N; ++i) grid[i][0] = grid[i][M-1] = '#';
        for (int j = 0; j < M; ++j) grid[0][j] = grid[N-1][j] = '#';

        for (int i=1;i<N-1;i++)
            for (int j=1;j<M-1;j++)
                if (dis(gen) < obstacle_density) grid[i][j] = '#';

        vector<pair<int,int>> freecells;
        for (int i=1;i<N-1;i++)
            for (int j=1;j<M-1;j++)
                if (grid[i][j]=='.') freecells.push_back({i,j});

        if (freecells.size() < 2) continue;

        shuffle(freecells.begin(), freecells.end(), gen);
        player = {freecells[0].first, freecells[0].second};
        treasure = {freecells[1].first, freecells[1].second};

        grid[player.x][player.y] = 'P';
        grid[treasure.x][treasure.y] = 'T';

        if (!bfs_path(grid, player, treasure).empty()) break;
    }
}

// ---------------------------------------------
// Level Up + Scoring
// ---------------------------------------------
void showScore(double seconds) {
    int levelScore = max(50, (int)(500.0 / (seconds + 1))) + (level * 20);
    totalScore += levelScore;
    cout << "\n🕒 Time: " << fixed << setprecision(2) << seconds << "s";
    cout << "\n💰 Level Score: +" << levelScore;
    cout << "\n🏆 Total Score: " << totalScore << "\n";

    if (totalScore > highScore) {
        highScore = totalScore;
        cout << "🎉 New High Score!\n";
    }

    if (level > maxLevel) maxLevel = level;
    saveScores();

    // 👇 Wait for any key
    cout << "\nPress any key to continue...";
    _getch();  
}

void nextLevel() {
    level++;
    if (level % 2 == 0) { N += 2; M += 3; }
    if (obstacle_density < 0.45) obstacle_density += 0.03;
    cout << "\n" << randomMsg(levelup_msgs) << level << "!\n";
    Sleep(1500);
    generateGrid();
}

// ---------------------------------------------
// MAIN GAME LOOP
// ---------------------------------------------
int main() {
    cout << "🏆 Treasure Hunter Pathfinder (Persistent Score Edition)\n";
    loadScores();
    generateGrid();

    while (true) {
        auto startTime = high_resolution_clock::now();

        while (true) {
            printGrid(grid);
            char ch = tolower(_getch());
            if (ch == 'q') { cout << "👋 Thanks for playing!\n"; saveScores(); return 0; }
            else if (ch == 'g') { generateGrid(); break; }

            else if (ch == 'r' || ch == 'x') {
                vector<Node> path = (ch == 'r') ? bfs_path(grid, player, treasure)
                                                : astar_path(grid, player, treasure);
                if (path.empty()) { cout << "No path found!\n"; _getch(); continue; }

                for (auto p : path) {
                    if (grid[p.x][p.y] == 'T') {
                        printGrid(grid);
                        cout << randomMsg(success_msgs) << "\n";
                        auto endTime = high_resolution_clock::now();
                        double timeTaken = duration<double>(endTime - startTime).count();
                        showScore(timeTaken);
                        nextLevel();
                        break;
                    }
                    if (grid[p.x][p.y] == 'P') continue;
                    grid[p.x][p.y] = '*';
                    printGrid(grid);
                    Sleep(70);
                }
                break;
            }

            int nx = player.x, ny = player.y;
            if (ch == 'w') nx--;
            else if (ch == 's') nx++;
            else if (ch == 'a') ny--;
            else if (ch == 'd') ny++;
            else continue;

            if (!validCell(nx,ny,grid)) continue;
            grid[player.x][player.y] = '.';
            player = {nx,ny};

            if (player.x == treasure.x && player.y == treasure.y) {
                grid[player.x][player.y] = 'P';
                printGrid(grid);
                cout << randomMsg(success_msgs) << "\n";
                auto endTime = high_resolution_clock::now();
                double timeTaken = duration<double>(endTime - startTime).count();
                showScore(timeTaken);
                nextLevel();
                break;
            }
            grid[player.x][player.y] = 'P';
        }
    }
}
