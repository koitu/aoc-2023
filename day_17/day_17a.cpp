#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


const int INT_MAX = (unsigned int)(~0) >> 1;
const int UP = 1;
const int RIGHT = 1 << 1;
const int DOWN = 1 << 2;
const int LEFT = 1 << 3;

class dst {
    std::vector<int> up = std::vector<int>(3, INT_MAX);
    std::vector<int> right = std::vector<int>(3, INT_MAX);
    std::vector<int> down = std::vector<int>(3, INT_MAX);
    std::vector<int> left = std::vector<int>(3, INT_MAX);
public:
    dst() {};
    int get(int d, int step);
    void update(int d, int step, int val);
};

int dst::get(int d, int step) {
    switch (d) {
        case UP:
            return up[step];

        case RIGHT:
            return right[step];

        case DOWN:
            return down[step];

        case LEFT:
            return left[step];

        default:
            std::cout << "error!" << std::endl;
            return -1;
    }
}

void dst::update(int d, int step, int val) {
    switch (d) {
        case UP:
//            for (int i = step; i >= 0; i--)
//                if (up[i] > val) up[i] = val;
            up[step] = val;
            break;

        case RIGHT:
//            for (int i = step; i >= 0; i--)
//                if (right[i] > val) right[i] = val;
            right[step] = val;
            break;

        case DOWN:
//            for (int i = step; i >= 0; i--)
//                if (down[i] > val) down[i] = val;
            down[step] = val;
            break;

        case LEFT:
//            for (int i = step; i >= 0; i--)
//                if (left[i] > val) left[i] = val;
            left[step] = val;
            break;

        default:
            std::cout << "error!" << std::endl;
    }
}

struct pos {
    int dist, i, j, steps, direction; // distance, i, j, steps, direction (steps left in direction)
    pos(int dist, int i, int j, int steps, int direction) :
        dist(dist),
        i(i),
        j(j),
        steps(steps),
        direction(direction) {};
};

struct comp {
    bool operator()(const pos& lhs, const pos& rhs) {
        return lhs.dist > rhs.dist;
    }
};

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    std::vector<std::vector<int>> maze;
    while (getline(file, line)) {
        std::vector<int> h;
        for (auto &c: line) {
            h.push_back((int)(c - '0'));
        }
        maze.push_back(h);
    }
    const int h = maze.size();
    const int w = line.size();

    std::vector<std::vector<dst>> dist(h, std::vector<dst>(w, dst()));
    dist[0][0].update(UP, 2, 0);
    dist[0][0].update(RIGHT, 2, 0);
    dist[0][0].update(DOWN, 2, 0);
    dist[0][0].update(LEFT, 2, 0);

    std::priority_queue<pos, std::vector<pos>, comp> q;
    q.push(pos(maze[1][0], 1, 0, 2, DOWN));
    q.push(pos(maze[0][1], 0, 1, 2, RIGHT));

    auto valid = [&h, &w] (pos p) -> bool {
        return (p.i >= 0 && p.i < h) && (p.j >= 0 && p.j < w) && p.steps >= 0;
    };

    while (!q.empty()) {
        pos cur = q.top();
        q.pop();

        pos next[] = {
                pos(-1, cur.i - 1, cur.j, 2, UP),
                pos(-1, cur.i, cur.j + 1, 2, RIGHT),
                pos(-1, cur.i + 1, cur.j, 2, DOWN),
                pos(-1, cur.i, cur.j - 1, 2, LEFT)};

        for (auto &n: next) {
            if (cur.direction + n.direction == 0b1010 ||
                cur.direction + n.direction == 0b0101) {
                continue;
            }

            if (n.direction == cur.direction) {
                n.steps = cur.steps - 1;
            }

            if (!valid(n)) {
                continue;
            }
            n.dist = cur.dist + maze[n.i][n.j];

            if (n.dist < dist[n.i][n.j].get(n.direction, n.steps)) {
                dist[n.i][n.j].update(n.direction, n.steps, n.dist);
                q.push(n);
            }
        }
    }

    auto min = [] (int a, int b) -> int {
        return a < b ? a : b;
    };
    int res = INT_MAX;
    for (int i = 0; i < 3; i++) {
        res = min(res, dist[h - 1][w - 1].get(UP, i));
        res = min(res, dist[h - 1][w - 1].get(RIGHT, i));
        res = min(res, dist[h - 1][w - 1].get(DOWN, i));
        res = min(res, dist[h - 1][w - 1].get(LEFT, i));
    }
    std::cout << res << std::endl; // 1244
}
