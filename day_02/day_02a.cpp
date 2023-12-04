#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

const int MAX_RED = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE = 14;


std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    std::vector<std::string> ss;
    std::string str = s;
    size_t pos;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        ss.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    ss.push_back(str);

    return ss;
}

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


bool check_game(const std::string &set) {
    std::vector<std::string> cubes = split(set, ", ");
    int red = 0;
    int green = 0;
    int blue = 0;

    for (auto &cube: cubes) {
        std::vector<std::string> p = split(cube, " ");
        int val = stoi(p[0]);
        color c = stoc[p[1]];
        switch(c) {
            case RED:
                red += val;
                break;
            case GREEN:
                green += val;
                break;
            case BLUE:
                blue += val;
                break;
        }
    }

    return (red <= MAX_RED) && (green <= MAX_GREEN) && (blue <= MAX_BLUE);
}


int main(int argc, char* argv[]) {
    std::string input_file = "./input.txt";

    register_colors();
    std::fstream file(input_file);
    std::string line;
    int res = 0;
    while(std::getline(file, line)) {
        std::vector<std::string> p = split(line, ": ");
        int id = stoi(split(p[0], " ")[1]);

        std::vector<std::string> sets = split(p[1], "; ");
        for (auto &set: sets) {
            if (!check_game(set)) {
                id = 0;
                break;
            }
        }
        res += id;
    }
    std::cout << res << std::endl;  // 2505
    return 0;
}
