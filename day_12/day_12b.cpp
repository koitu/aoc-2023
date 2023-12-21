#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

typedef long long ll;

std::vector<int> split(std::string s) {
    std::vector<int> res;
    size_t pos;
    while ((pos = s.find(',')) != std::string::npos) {
        res.push_back(stoi(s.substr(0, pos)));
        s.erase(0, pos + 1);
    }
    res.push_back(stoi(s));

    return res;
}


ll get_perms(const std::string s, const std::vector<int> n) {
    std::vector<std::vector<int>> mem(s.length(),
                                      std::vector<int>(n.size(), -1));
    // mem[i][j]
    //  i -> index of s to continue from
    //  j -> index of n to continue from

    for (int i = 0; i < s.length() - 1; i++) {
        // no more numbers but vary amount of string left
        std::string ss = s.substr(i);
        mem[i][n.size() - 1] =
                (ss.find('#') == std::string::npos) ? 1 : 0;
    }
    for (int i = 0; i < n.size() - 1; i++) {
        // no more string but vary number of numbers left
        mem[s.length() - 1][i] = 0;
    }
    mem[s.length() - 1][n.size() - 1] = 1;

    auto f = [&] (int i, int j) -> ll {
        if (mem[i][j] != -1) {
            return mem[i][j];
        }

        switch (s[i]) {
            case '.':
                // increase i until s[i] no longer .

            case '#':
                // increase i up to num[j] times
                //  - if hit a . then return 0
                //  - else
                //      - if can take an extra . or ? increment j
                //      - else return 0

            case '?':
                // increase i until s[i] no longer .

                // increase i up to num[j] times
                //  - if hit a . then return 0
                //  - else
                //      - if can take an extra . or ? increment j
                //      - else return 0

            default:
                std::cout << "error!" << std::endl;
        }

        return mem[i][j];
    };

    return f(0, 0);
}


ll get_perms(std::string s) {
    size_t pos = s.find(' ');
    std::string arr = s.substr(0, pos);
    s.erase(0, pos + 1);

    std::vector<int> nums = split(s);

    std::string a(arr);
    std::vector<int> n(nums);
    for (int i = 0; i < 4; i ++) {
        a = a + '?' + arr;
        for (auto &nu: nums) {
            n.push_back(nu);
        }
    }

    return get_perms(a, n);
}


int main(int argc, char* argv[]) {
    std::string input = "./sample.txt";

    std::fstream file(input);
    std::string line;

    ll res = 0;
    while (getline(file, line)) {
        ll ret = get_perms(line);
        std::cout << ret << std::endl;
        res += ret;
    }

    std::cout << res << std::endl;
}

