#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

enum color {
    RED = 1,
    GREEN = 2,
    BLUE = 3
};

std::map<std::string, color> stoc;

void register_colors() {
    stoc["red"] = RED;
    stoc["green"] = GREEN;
    stoc["blue"] = BLUE;
}

std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    std::vector<std::string> ss;
    std::string str = s;
    size_t pos;

    while((pos = str.find(delimiter)) != std::string::npos) {
        ss.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    ss.push_back(str);

    return ss;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min_game(const std::string &game) {
    int red = 0;
    int green = 0;
    int blue = 0;

    std::vector<std::string> sets = split(game, "; ");
    for (auto &set: sets) {
        std::vector<std::string> pairs = split(set, ", ");

        for (auto &pair: pairs) {
            std::vector<std::string> p = split(pair, " ");
            int val = stoi(p[0]);
            color c = stoc[p[1]];

            switch (c) {
                case RED:
                    red = max(red, val);
                    break;
                case GREEN:
                    green = max(green, val);
                    break;
                case BLUE:
                    blue = max(blue, val);
                    break;
            }
        }
    }

    return red * green * blue;
}


int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    register_colors();
    int res = 0;
    while(std::getline(file, line)) {
        res += min_game(split(line, ": ")[1]);
    }
    std::cout << res << std::endl;
}
