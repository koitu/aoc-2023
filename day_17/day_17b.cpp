#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

const int INT_MAX = (unsigned)(-1) >> 1;

const int UP = 1;
const int RIGHT = 1 << 1;
const int DOWN = 1 << 2;
const int LEFT = 1 << 3;

struct dst {
    std::vector<int> up = std::vector<int>(7, INT_MAX);
    std::vector<int> right = std::vector<int>(7, INT_MAX);
    std::vector<int> down = std::vector<int>(7, INT_MAX);
    std::vector<int> left = std::vector<int>(7, INT_MAX);

    dst() {};
    int get(int steps, int direction) {
        switch (direction) {
            case UP:
                return up[steps];
            case RIGHT:
                return right[steps];
            case DOWN:
                return down[steps];
            case LEFT:
                return left[steps];
            default:
                std::cout << "error!" << std::endl;
                return -1;
        }
    }

    void update(int steps, int direction, int value) {
        switch (direction) {
            case UP:
                up[steps] = value;
                break;
            case RIGHT:
                right[steps] = value;
                break;
            case DOWN:
                down[steps] = value;
                break;
            case LEFT:
                left[steps] = value;
                break;
            default:
                std::cout << "error!" << std::endl;
                break;
        }
    }
};

struct pos {
    int distance, i, j, steps, direction;
    pos(int distance, int i, int j, int steps, int direction) :
        distance(distance),
        i(i), j(j),
        steps(steps),
        direction(direction) {};
};

struct comp {
    bool operator()(const pos& lhs, const pos& rhs) {
        return lhs.distance > rhs.distance;
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

    std::priority_queue<pos, std::vector<pos>, comp> q;
    q.push(pos(maze[0][1] + maze[0][2] + maze[0][3] + maze[0][4],0, 4, 6, RIGHT));
    q.push(pos(maze[1][0] + maze[2][0] + maze[3][0] + maze[4][0],4, 0, 6, DOWN));

    std::vector<std::vector<dst>> dist(h, std::vector<dst>(w, dst()));

    auto valid = [&h, &w] (const pos& p) -> bool {
        return (p.i >= 0 && p.i < h) && (p.j >= 0 && p.j < w) && p.steps >= 0;
    };

    while (!q.empty()) {
        pos cur = q.top();
        q.pop();

        pos next[] = {
                pos(-1, cur.i - 4, cur.j, 6, UP),
                pos(-1, cur.i, cur.j + 4, 6, RIGHT),
                pos(-1, cur.i + 4, cur.j, 6, DOWN),
                pos(-1, cur.i, cur.j - 4, 6, LEFT),
        };

        for (auto &n: next) {
            if (cur.direction + n.direction == 0b1010 ||
                cur.direction + n.direction == 0b0101) {
                continue;
            }

            if (n.direction == cur.direction) {
                n.steps = cur.steps - 1;

                switch (n.direction) {
                    case UP:
                        n.i = cur.i - 1;
                        break;
                    case RIGHT:
                        n.j = cur.j + 1;
                        break;
                    case DOWN:
                        n.i = cur.i + 1;
                        break;
                    case LEFT:
                        n.j = cur.j - 1;
                        break;
                    default:
                        std::cout << "error!" << std::endl;
                }
            }
            
            if (!valid(n)) {
                continue;
            }
            
            n.distance = cur.distance;
            switch (n.direction) {
                case UP:
                    for (int i = cur.i - 1; i >= n.i; i--)
                        n.distance += maze[i][n.j];
                    break;

                case RIGHT:
                    for (int j = cur.j + 1; j <= n.j; j++)
                        n.distance += maze[n.i][j];
                    break;

                case DOWN:
                    for (int i = cur.i + 1; i <= n.i; i++)
                        n.distance += maze[i][n.j];
                    break;

                case LEFT:
                    for (int j = cur.j - 1; j >= n.j; j--)
                        n.distance += maze[n.i][j];
                    break;

                default:
                    std::cout << "error!" << std::endl;
            }

            if (n.distance < dist[n.i][n.j].get(n.steps, n.direction)) {
                dist[n.i][n.j].update(n.steps, n.direction, n.distance);
                q.push(n);
            }
        }
    }

    auto min = [] (int a, int b) -> int{
        return a < b ? a : b;
    };

    int res = INT_MAX;
    dst last = dist[h - 1][w - 1];
    for (int i = 0; i < 7; i++) {
        res = min(res, last.up[i]);
        res = min(res, last.right[i]);
        res = min(res, last.down[i]);
        res = min(res, last.left[i]);
    }

    std::cout << res << std::endl; // 1367
}