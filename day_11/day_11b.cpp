#include <vector>
#include <string>
#include <fstream>
#include <iostream>

typedef long long ll;

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);

    std::vector<int> row_count;
    std::vector<int> col_count(line.size(), 0);
    std::vector<std::pair<int, int>> stars;

    int i = 0;
    do {
        row_count.push_back(0);
        for (int j = 0; j < line.size(); j++) {
            if (line[j] == '#') {
                row_count[i]++;
                col_count[j]++;
                stars.push_back(std::pair<int, int>(i, j));
            }
        }

        i++;
    } while(getline(file, line));

    ll res = 0;
    ll star_count = stars.size();

    ll cum = 0;
    for (auto &a: col_count) {
        if (a == 0) {
            res += (cum * (star_count - cum) * 999999); // 1 space is replaced by 1,000,000
        }
        cum += a;
    }

    cum = 0;
    for (auto &a: row_count) {
        if (a == 0) {
            res += (cum * (star_count - cum) * 999999);
        }
        cum += a;
    }

    std::pair<int, int> cur;
    while(!stars.empty()) {
        cur = std::pair<int, int>(stars.back());
        stars.pop_back();

        for (auto &p: stars) {
            res += ll(abs(p.first - cur.first) + abs(p.second - cur.second));
        }
    }

    std::cout << res << std::endl;  // 411142919886
}
