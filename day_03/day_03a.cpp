#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::vector<bool>> mask;
std::vector<std::string> engine;
int w, h;

void set_mask(int y, int x) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (isdigit(engine[y + i][x + j])) {
                mask[y + i][x + j] = true;
            }
        }
    }
}

void expand_mask() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (mask[i][j]) {
                int x = -1;
                while(isdigit(engine[i][j + x])) {
                    mask[i][j + x] = true;
                    x--;
                }

                // TODO: can be reworked to not need this loop
                while(isdigit(engine[i][j + 1])) {
                    mask[i][j + 1] = true;
                    j++;
                }
            }
        }
    }
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
    engine.push_back("." + line + ".");

    while(getline(file, line)) {
        engine.push_back("." + line + ".");
    }
    engine.push_back(pad);

    w = pad.length();
    h = engine.size();
    for (int i = 0; i < h; i++) {
        mask.push_back(std::vector<bool>(w, false));
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char cur = engine[i][j];

            if (cur != '.' && !isdigit(cur)) {
                set_mask(i, j);
            }
        }
    }
    expand_mask();

//    for (int i = 0; i < h; i++) {
//        for (int j = 0; j < w; j++) {
//            std::cout << (mask[i][j] ? '0' : '.');
//        }
//        std::cout << std::endl;
//    }

    int res = 0;
    std::string cur;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (mask[i][j]) {
                cur = cur + engine[i][j];
                continue;
            }

            if (cur != "") {
                res += stoi(cur);
                cur.clear();
            }
        }
    }
    std::cout << res << std::endl; // 527364

    return 0;
}
