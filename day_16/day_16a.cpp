#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

const int UP = 1;
const int RIGHT = 1 << 1;
const int DOWN = 1 << 2;
const int LEFT = 1 << 3;
const int PAD = UP + RIGHT + DOWN + LEFT;

class position {
public:
    int i, j;
    int d;
    position() : i(-1), j(-1) {};
    position(int i, int j) : i(i), j(j) {};
    position(int i, int j, int d) : i(i), j(j), d(d) {};

    void rotate90();
    void rotate270();
    void next_pos();
};

void position::rotate90() {
    int s = (d << 1) % (1 << 4);
    if (s == 0) s = UP;
    d = s;
}

void position::rotate270() {
    int s = (d >> 1);
    if (s == 0) s = LEFT;
    d = s;
}

void position::next_pos() {
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


int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    std::vector<std::string> maze;

    getline(file, line);
    std::string pad(line.length() + 2, '.');
    maze.push_back(pad);
    do {
        maze.push_back('.' + line + '.');
    } while(getline(file, line));
    maze.push_back(pad);

    int h = maze.size();
    int w = pad.length();
    std::vector<std::vector<int>> visited(h, std::vector<int>(w, 0));
    for (int i = 0; i < h; i++) {
        visited[i][0] = PAD;
        visited[i][w - 1] = PAD;
    }
    for (int i = 0; i < w; i++) {
        visited[0][i] = PAD;
        visited[h - 1][i] = PAD;
    }

    std::queue<position> qp;
    qp.push(position(1, 1, RIGHT));

    position cur;
    while (!qp.empty()) {
        cur = qp.front();
        qp.pop();

        if (visited[cur.i][cur.j] & cur.d) continue;
        visited[cur.i][cur.j] += cur.d;

        switch (maze[cur.i][cur.j]) {
            case '.':
                cur.next_pos();
                qp.push(cur);
                break;

            case '/':
                if (cur.d & (RIGHT + LEFT)) {
                    cur.rotate270();
                } else {
                    cur.rotate90();
                }
                cur.next_pos();
                qp.push(cur);
                break;

            case '\\':
                if (cur.d & (RIGHT + LEFT)) {
                    cur.rotate90();
                } else {
                    cur.rotate270();
                }
                cur.next_pos();
                qp.push(cur);
                break;

            case '|':
                if (cur.d & (UP + DOWN)) {
                    cur.next_pos();
                    qp.push(cur);
                } else {
                    qp.push(position(cur.i, cur.j, UP));
                    qp.push(position(cur.i, cur.j, DOWN));
                }
                break;

            case '-':
                if (cur.d & (RIGHT + LEFT)) {
                    cur.next_pos();
                    qp.push(cur);
                } else {
                    qp.push(position(cur.i, cur.j, RIGHT));
                    qp.push(position(cur.i, cur.j, LEFT));
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

    std::cout << res << std::endl; // 8323
}
