#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

enum direction {
    NONE = 0,
    NORTH = 1,
    EAST = 1 << 1,
    SOUTH = 1 << 2,
    WEST = 1 << 3,
};

std::map<char, int> d_map{
    {'|', NORTH | SOUTH},
    {'-', EAST | WEST},
    {'L', NORTH | EAST},
    {'J', NORTH | WEST},
    {'7', SOUTH | WEST},
    {'F', SOUTH | EAST},
    {'.', NONE}};

direction invert(direction d) {
    switch (d) {
        case NORTH:
            return SOUTH;
        case EAST:
            return WEST;
        case SOUTH:
            return NORTH;
        case WEST:
            return EAST;
        default:
            return NONE;
    }
}

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    std::vector<std::string> maze;

    getline(file, line);
    const std::string pad(line.length() + 2, '.');
    maze.push_back(pad);

    do {
        maze.push_back('.' + line + '.');
    } while (getline(file, line));
    maze.push_back(pad);

    int i, j;
    for (i = 0; i < maze.size(); i++) {
        if ((j = maze[i].find('S')) != std::string::npos) {
            break;
        }
    }

    int steps = 1;
    direction prev_direction;

    if (d_map[maze[i-1][j]] & invert(NORTH)) {
        prev_direction = NORTH;
        i--;

    } else if (d_map[maze[i][j+1]] & invert(EAST)) {
        prev_direction = EAST;
        j++;

    } else if (d_map[maze[i][j-1]] & invert(SOUTH)) {
        prev_direction = SOUTH;
        i++;

    } else if (d_map[maze[i+1][j]] & invert(WEST)) {
        prev_direction = WEST;
        j--;

    } else {
        std::cout << "error!" << std::endl;
        return 1;
    }

    while(true) {
        if (maze[i][j] == 'S') {
            std::cout << steps / 2 << std::endl;  // 6682
            return 0;
        }
        steps++;

        direction cur = (direction)(d_map[maze[i][j]] - (int)invert(prev_direction));
        switch(cur) {
            case NORTH:
                i--;
                break;
            case EAST:
                j++;
                break;
            case SOUTH:
                i++;
                break;
            case WEST:
                j--;
                break;
            default:
                std::cout << "error!" << std::endl;
                return 1;
        }
        prev_direction = cur;
    }
}
