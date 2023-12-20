#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

enum direction {
    NONE = 0,
    NORTH = 1,
    EAST = 1 << 1,
    SOUTH = 1 << 2,
    WEST = 1 << 3,
};

enum block {
    NOTHING = 0,
    OUTER = 1,
    WALL = 2,
};

std::map<char, int> d_map{
    {'S', NORTH | EAST | SOUTH | WEST},
    {'|', NORTH | SOUTH},
    {'-', EAST | WEST},
    {'L', NORTH | EAST},
    {'J', NORTH | WEST},
    {'7', SOUTH | WEST},
    {'F', SOUTH | EAST},
    {'.', NONE},
};

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
            std::cout << "error!" << std::endl;
            return NONE;
    }
}


int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);

    std::vector<std::string> maze;
    const std::string pad(line.size() + 2, '.');
    maze.push_back(pad);

    do {
        maze.push_back('.' + line + '.');
    } while (getline(file, line));
    maze.push_back(pad);

    // scale the pipes maze three times so that outer can flow between pipes
    std::vector<std::vector<block>> pipes;
    for (int i = 0; i < maze.size()*3; i++) {
        pipes.push_back(std::vector<block>(pad.size()*3, NOTHING));
    }

    int i, j;
    for (i = 0; i < maze.size(); i++) {
        if ((j = maze[i].find('S')) != -1) {
            break;
        }
    }

    direction prev_direction;
    if (d_map[maze[i-1][j]] & invert(NORTH)) {
        prev_direction = NORTH;
        i--;

    } else if (d_map[maze[i][j+1]] & invert(EAST)) {
        prev_direction = EAST;
        j++;

    } else if (d_map[maze[i+1][j]] & invert(SOUTH)) {
        prev_direction = SOUTH;
        i++;

    } else if (d_map[maze[i][j-1]] & invert(WEST)) {
        prev_direction = WEST;
        j--;

    } else {
        std::cout << "error!" << std::endl;
    }

    while(true) {
        int cur_direction = d_map[maze[i][j]];

        pipes[i*3 + 1][j*3 + 1] = WALL;
        if (cur_direction & NORTH) pipes[i*3][j*3 + 1] = WALL;
        if (cur_direction & EAST) pipes[i*3 + 1][j*3 + 2] = WALL;
        if (cur_direction & SOUTH) pipes[i*3 + 2][j*3 + 1] = WALL;
        if (cur_direction & WEST) pipes[i*3 + 1][j*3] = WALL;

        if (maze[i][j] == 'S') {
            break;
        }

        direction cur = (direction)(cur_direction - (int)invert(prev_direction));
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

    std::queue<std::pair<int, int>> next;
    for (int x = 0; x < pad.size()*3; x++) {
        pipes[0][x] = OUTER;
        pipes[maze.size()*3 - 1][x] = OUTER;
    }
    for (int x = 0; x < maze.size()*3; x++) {
        pipes[x][0] = OUTER;
        pipes[x][pad.size()*3 - 1] = OUTER;
    }
    for (int x = 1; x < pad.size()*3 - 1; x++) {
        next.push(std::pair(1, x));
        next.push(std::pair(maze.size()*3 - 2, x));
    }
    for (int x = 1; x < maze.size()*3 - 1; x++) {
        next.push(std::pair(x, 1));
        next.push(std::pair(x, pad.size()*3 - 2));
    }

    std::pair<int, int> cur;
    while(!next.empty()) {
        cur = next.front();
        next.pop();

        int y = cur.first;
        int x = cur.second;

        if (pipes[y][x] == NOTHING) {
            pipes[y][x] = OUTER;
            next.push(std::pair<int, int>(y-1, x));
            next.push(std::pair<int, int>(y+1, x));
            next.push(std::pair<int, int>(y, x-1));
            next.push(std::pair<int, int>(y, x+1));
        }
    }

//    for (auto &p: pipes) {
//        for (auto &b: p) {
//            std::cout << b;
//        }
//        std::cout << std::endl;
//    }

    int count = 0;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < pad.size(); j++) {
            if (pipes[i*3 + 1][j*3 + 1] == NOTHING) {
                count++;
            }
        }
    }
    std::cout << count << std::endl;  // 353
}
