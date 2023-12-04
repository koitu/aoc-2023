#include <string>
#include <fstream>
#include <iostream>

const int MAX_RED = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE = 14;

const std::string delimit1 = ": ";
const std::string delimit2 = "; ";
const std::string delimit3 = ", ";

// TODO: add python string split

std::string read_until(std::string &s, std::string delimiter) {
    size_t pos = s.find(delimiter);
    std::string read;

    read = s.substr(0, pos);
    if (pos != std::string::npos) {
        s.erase(0, pos + delimiter.length());
    } else {
        s.erase(0, pos);
    }
    return read;
}

bool check_game(std::string s) {
    size_t pos = 0;
    std::string color;
    while ((pos = s.find(delimit3)) != std::string::npos) {
        color = line.substr(0, pos);
        s.erase(0,
                pos + delimit3.length());

    }
}


int main(int argc, char* argv[]) {
    std::string input_file = "./input.txt";

    std::fstream file(input_file);
    std::string line;
    int res = 0;
    while(std::getline(file, line)) {
        line.erase(0,
                   line.find(delimit1) + delimit1.length());
        const int len = line.length();

        size_t pos = 0;
        std::string game;
        while ((pos = line.find(delimit2)) != std::string::npos) {
            game = line.substr(0, pos);
            line.erase(0,
                       pos + delimit2.length());

            if (!check_game(game)) {
                res++;
                break;
            }
        }
    }
}
