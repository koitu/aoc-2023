#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>


std::vector<int> parse_nums(std::string s) {
    std::vector<int> a;
    while(s.length() > 2) {
        a.push_back(stoi(s.substr(0, 2)));
        s.erase(0, 3);
    }
    a.push_back(stoi(s.substr(0, 2)));

    return a;
}


int count_points(std::vector<int> num, std::vector<int> win) {
    std::sort(num.begin(), num.end());
    std::sort(win.begin(), win.end());

    int i = 0, j = 0, r = 0;
    while(i < num.size() && j < win.size()) {
        int ii = num[i];
        int jj = win[j];
        if (ii == jj) {
            r++;
        }
        if (ii <= jj) {
            i++;
        }
        if (ii >= jj) {
            j++;
        }
    }
    return r;
}

std::vector<int> points;
std::vector<int> copies;

void copy_cards(int pos, int n) {
    for (int i = 1; i <= n; i++) {
        copies[pos + i] += copies[pos];
    }
}

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    while(getline(file, line)) {
        size_t pos = line.find(": ");
        line.erase(0, pos + 2);

        pos = line.find(" | ");
        points.push_back(
                count_points(
                        parse_nums(line.substr(0, pos)),
                        parse_nums(line.substr(pos + 3))));
    }

    int res = 0;
    copies = std::vector<int>(points.size(), 1);
    for (int i = 0; i < points.size(); i++) {
        copy_cards(i, points[i]);
        res += copies[i];
    }

    std::cout << res << std::endl;  // 10212704
    return 0;
}