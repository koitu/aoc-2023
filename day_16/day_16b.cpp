#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

const int UP = 1;
const int RIGHT = 1 << 1;
const int DOWN = 1 << 2;
const int LEFT = 1 << 3;
const int PAD = UP + RIGHT + DOWN + LEFT;

struct position {
    int i, j, d;
    position(int i, int j, int d) : i(i), j(j), d(d) {};

    void rotate_cw();
    void rotate_ccw();
    void update_pos();
};

void position::rotate_cw() {
    d <<= 1;
    if (d == (1 << 4)) d = UP;
}

void position::rotate_ccw() {
    d >>= 1;
    if (d == 0) d = LEFT;
}

void position::update_pos() {
    switch (d) {
        case UP:
            i--;
            break;
        case RIGHT:
            j++;
            break;
        case DOWN:
            i++;
            break;
        case LEFT:
            j--;
            break;
        default:
            std::cout << "error!" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    std::vector<std::string> maze;

    getline(file, line);
    std::string pad(line.length() + 2, '.');
    maze.push_back(pad);
    do {
        maze.push_back('.' + line + '.');
    } while (getline(file, line));
    maze.push_back(pad);

    const int h = maze.size();
    const int w = pad.length();

    auto eval = [&maze, &h, &w] (position p) -> int {
        std::vector<std::vector<int>> visited(h, std::vector<int>(w, 0));
        for (int i = 0; i < h; i++) {
            visited[i][0] = PAD;
            visited[i][w - 1] = PAD;
        }
        for (int i = 0; i < w; i++) {
            visited[0][i] = PAD;
            visited[h - 1][i] = PAD;
        }

        std::queue<position> pq;
        pq.push(p);

        while (!pq.empty()) {
            position cur = pq.front();
            pq.pop();

            if (visited[cur.i][cur.j] & cur.d) continue;
            visited[cur.i][cur.j] += cur.d;

            switch (maze[cur.i][cur.j]) {
                case '.':
                    cur.update_pos();
                    pq.push(cur);
                    break;

                case '/':
                    if (cur.d & (RIGHT + LEFT)) {
                        cur.rotate_ccw();
                    } else {
                        cur.rotate_cw();
                    }
                    cur.update_pos();
                    pq.push(cur);
                    break;

                case '\\':
                    if (cur.d & (RIGHT + LEFT)) {
                        cur.rotate_cw();
                    } else {
                        cur.rotate_ccw();
                    }
                    cur.update_pos();
                    pq.push(cur);
                    break;

                case '-':
                    if (cur.d & (RIGHT + LEFT)) {
                        cur.update_pos();
                        pq.push(cur);
                    } else {
                        pq.push(position(cur.i, cur.j, RIGHT));
                        pq.push(position(cur.i, cur.j, LEFT));
                    }
                    break;

                case '|':
                    if (cur.d & (UP + DOWN)) {
                        cur.update_pos();
                        pq.push(cur);
                    } else {
                        pq.push(position(cur.i, cur.j, UP));
                        pq.push(position(cur.i, cur.j, DOWN));
                    }
                    break;

                default:
                    std::cout << "error!" << std::endl;
            }
        }

        int res = 0;
        for (int i = 1; i < h - 1; i++) {
            for (int j = 1; j < w - 1; j++) {
                if (visited[i][j]) {
                    res++;
                }
            }
        }

        return res;
    };

    auto max = [] (int a, int b) -> int {
        return a > b ? a : b;
    };

    int res = 0;
    for (int i = 1; i < h - 1; i++) {
        res = max(res, eval(position(i, 1, RIGHT)));
        res = max(res, eval(position(i, w - 2, LEFT)));
    }
    for (int i = 1; i < w - 1; i++) {
        res = max(res, eval(position(1, i, DOWN)));
        res = max(res, eval(position(h - 2, i, UP)));
    }

    std::cout << res << std::endl;  // 8491
}
