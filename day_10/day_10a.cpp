#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

enum direction {
    NORTH = 1 << 4,
    EAST = 1 << 3,
    SOUTH = 1 << 2,
    WEST = 1,
};

map<char, direction> d_map = {
    {'|', NORTH | SOUTH},
    {'-', EAST | WEST},
    {'L', NORTH | EAST},
    {'J', NORTH | WEST},
    {'7', SOUTH | WEST},
    {'F', SOUTH | EAST},
};

int main(int argc, char* argv[]) {
    std::string input = "./sample.txt";

    std::fstream file(input);
    std::string line;

    // from S there is ONE loop that will bring it back to S
    //      every pipe in the main loop connects to two neighbours
    // S can be any of |, -, L, J, 7, F
    //      S will have exactly two pipes connecting to it

    // then just consider the number of steps to get back to original start
    // and return half of it
}

