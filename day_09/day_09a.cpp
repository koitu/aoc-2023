#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<double> num_split(std::string s) {
    std::vector<double> f;
    size_t pos;

    while((pos = s.find(" ")) != std::string::npos) {
        f.push_back(stod(s.substr(0, pos)));
        s.erase(0, pos + 1);
    }
    f.push_back(stod(s));

    return f;
}

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);  // assume we always have at least one line
    std::string temp = line;

    std::vector<double> lst = num_split(temp);
    const int n = lst.size();  // assume we always have at least one number

    std::vector<double> l;
    // Unisolvence thm: given n data pairs (x_i, y_i) with distinct x_i there is a unique polynomial of degree <= n-1
    //  that interpolates the data

    // https://en.wikipedia.org/wiki/Lagrange_polynomial
    for (double i = 0; i < n; i++) {
        double h = 1;

        for (double j = 0; j < n; j++) {
            if (i != j) {
                h *= (n - j) / (i - j);
            }
        }

        l.push_back(h);
    }

    long long res = 0;
    do {
        lst = num_split(line);
        for (int i = 0; i < n; i++) {
            res += std::llround(l[i] * lst[i]);
        }
    } while(getline(file, line));

    std::cout << res << std::endl;  // 2008960228

    return 0;
}
