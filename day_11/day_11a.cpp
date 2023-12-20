#include <string>
#include <vector>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    std::vector<std::string> space;
    while(getline(file, line)) {
        space.push_back(line);
    }

    std::vector<int> v_amount(space.size(), 0);
    std::vector<int> h_amount(line.size(), 0);

    int star_count = 0;
    std::vector<std::pair<int, int>> stars;
    for (int i = 0; i < space.size(); i++) {
        for (int j = 0; j < line.size(); j++) {
            if (space[i][j] == '#') {
                v_amount[i]++;
                h_amount[j]++;
                star_count++;
                stars.push_back(std::pair<int, int>(i, j));
            }
        }
    }

    int res = 0;
    int cum;

    cum = 0;
    for (auto &a: v_amount) {
        if (a == 0) {
            // there are no stars in this vertical column
            // increasing distance between left and right stars by 1
            //  is equivalent to multiplying left star count by right star count
            res += cum * (star_count - cum);
        }
        cum += a;
    }

    cum = 0;
    for (auto &a: h_amount) {
        if (a == 0) {
            res += cum * (star_count - cum);
        }
        cum += a;
    }

    // get the manhattan distance from every star to every other star (once)
    std::pair<int, int> cur;
    while (!stars.empty()) {
        cur = std::pair<int, int>(stars.back());
        stars.pop_back();

        for (auto &p: stars) {
            res += abs(p.first - cur.first) + abs(p.second - cur.second);
        }
    }

    std::cout << res << std::endl;  // 9742154
}
