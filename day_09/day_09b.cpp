#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

std::vector<double> num_split(const std::string s) {
    std::string ss = s;
    std::vector<double> l;
    size_t pos;

    while ((pos = ss.find(" ")) != std::string::npos) {
        l.push_back(stod(ss.substr(0, pos)));
        ss.erase(0, pos + 1);
    }
    l.push_back((stod(ss)));

    return l;
}

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);
    std::vector<double> lst = num_split(line);
    const int n = lst.size();

    std::vector<double> l;
    for (double i = 1; i <= n; i++) {
        double t = 1;

        for (double j = 1; j <= n; j++) {
            if (i != j) {
                t *= -j / (i - j);
            }
        }
        l.push_back(t);
    }

    long long res = 0;
    do {
        lst = num_split(line);
        for (int i = 0; i < n; i++) {
            res += llround(lst[i] * l[i]);
        }
    } while (getline(file, line));

    std::cout << res << std::endl;  // 1097
}
