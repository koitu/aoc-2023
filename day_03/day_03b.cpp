#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> engine;
int h, w;

int get_gear(int i, int j) {
    std::vector<int> a;

    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (isdigit(engine[i + y][j + x])) {
                while (isdigit(engine[i + y][j + x - 1])) {
                    x--;
                }

                std::string s;
                while (isdigit(engine[i + y][j + x])) {
                    s = s + engine[i + y][j + x];
                    x++;
                }
                a.push_back(stoi(s));
            }
        }
    }

    if (a.size() != 2) {
        return 0;
    }

    return a[0] * a[1];
}


int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    if (!getline(file, line)) {
        std::cout << 0 << std::endl;
        return 0;
    }
    std::string pad(line.length() + 2, '.');
    engine.push_back(pad);
    engine.push_back('.' + line + '.');

    while(getline(file, line)) {
        engine.push_back('.' + line + '.');
    }
    engine.push_back(pad);
    h = engine.size();
    w = pad.length();

    int res = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (engine[i][j] == '*') {
                res += get_gear(i, j);
            }
        }
    }

    std::cout << res << std::endl;  // 79026871
}