#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

typedef long long ll;

ll parse(std::string s) {
    std::string a;

    for (auto &c: s) {
        if (isdigit(c)) {
            a.push_back(c);
        }
    }
    return stoll(a);
}

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);
    ll time = parse(line);

    getline(file, line);
    ll dist = parse(line);

//    std::cout << time << " " << dist << std::endl;

    ll a = sqrt(time*time/4 - dist);
    a = ceil(time/2 + a) - floor(time/2 - a) + 1;  // switches to closed intervals???

    std::cout << a << std::endl; // 42948149
}
