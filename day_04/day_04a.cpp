#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>


int points(std::vector<int> num, std::vector<int> win) {
    std::sort(num.begin(), num.end());
    std::sort(win.begin(), win.end());

    int i = 0;
    int j = 0;
    int r = 0;
    while (i < num.size() && j < win.size()) {
        int n_i = num[i];
        int w_j = win[j];

        if (n_i == w_j) {
            r = (r == 0 ? 1 : r * 2);
        }
        if (n_i <= w_j) {
            i++;
        }
        if (n_i >= w_j) {
            j++;
        }
    }
    return r;
}

std::vector<int> split_nums(std::string s) {
    std::vector<int> nums;
    while(s.length() > 2) {
        nums.push_back(stoi(s.substr(0, 2)));
        s.erase(0, 3);
    }
    nums.push_back(stoi(s.substr(0, 2)));

    return nums;
}

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    int res = 0;
    while(getline(file, line)) {
        size_t pos = line.find(": ");
        line.erase(0, pos + 2);
        pos = line.find(" | ");

        res += points(
                split_nums(line.substr(0, pos)),
                split_nums(line.substr(pos + 3)));
    }
    std::cout << res << std::endl;  // 28750

    return 0;
}