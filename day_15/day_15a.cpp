#include <string>
#include <vector>
#include <fstream>
#include <iostream>


typedef long long ll;

std::vector<std::string> split(std::string s) {
    std::vector<std::string> s_arr;
    size_t pos;

    while ((pos = s.find(',')) != std::string::npos) {
        s_arr.push_back(s.substr(0, pos));
        s.erase(0, pos + 1);
    }

    s_arr.push_back(s);
    return s_arr;
}

ll hash(std::string s) {
    ll res = 0;
    for (auto &c: s) {
        res += (ll)(c);
        res = (res * 17) % 256;
    }
    return res;
}

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);
    std::vector<std::string> s = split(line);

    ll res = 0;
    for (auto &ss: s) {
        res += hash(ss);
    }

    std::cout << res << std::endl;  // 511416
}