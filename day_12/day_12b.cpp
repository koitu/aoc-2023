#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>

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
    // same logic as before with some optimizations:
    //     - perform memoization on previously found answers
    //     - use indexes instead of passing around strings

    std::vector<std::vector<ll>> mem(s.length() + 1,
                                      std::vector<ll>(n.size() + 1, -1));
    // mem[i][j]
    //  i -> index of s to continue from
    //  j -> index of n to continue from

    // base cases
    for (int i = 0; i < s.length(); i++) {
        // no more numbers but vary amount of string left
        std::string ss = s.substr(i);
        mem[i][n.size()] = (ss.find('#') == std::string::npos) ? 1 : 0;
    }
    for (int i = 0; i < n.size(); i++) {
        // no more string but vary number of numbers left
        mem[s.length()][i] = 0;
    }
    mem[s.length()][n.size()] = 1;

    // inductive step
    std::function<const ll (int, int)> f = [&] (int i, int j) -> ll {
        if (mem[i][j] != -1) {
            return mem[i][j];
        }

        ll res = 0;

        if (s[i] == '.' || s[i] == '?') {
            // consume one ? or . then any many . as possible
            int ii = i + 1;
            while (ii < s.length() && s[ii] == '.') ii++;

            res += f(ii, j);
        }

        if (s[i] == '#' || s[i] == '?') {
            if (i + n[j] < s.length()) {
                // check:
                //  - [i, i + n[j] - 1] for # and ? (match the number)
                //  - i + n[j] for . or ? (split the number)
                bool cont = true;

                for (int x = 0; x < n[j]; x++) {
                    if (s[i + x] == '.') {
                        cont = false;
                        break;
                    }
                }
                if (s[i + n[j]] == '#') {
                    cont = false;
                }

                if (cont) {
                    res += f(i + n[j] + 1, j + 1);
                }
            }
        }

        mem[i][j] = res;
        return mem[i][j];
    };

    return f(0, 0);
}


ll get_perms(std::string s) {
    size_t pos = s.find(' ');
    std::string arr = s.substr(0, pos);
    s.erase(0, pos + 1);

    std::string a;
    for (int i = 0; i < 4; i ++) {
        a = a + arr + '?';
    }
    a = a + arr + '.'; // add a dot at the end to make cases easier

    std::vector<int> nums = split(s);
    std::vector<int> n;
    for (int i = 0; i < 5; i ++) {
        for (auto &nu: nums) n.push_back(nu);
    }

    return get_perms(a, n);
}


int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    ll res = 0;
    while (getline(file, line)) {
//        ll ret = get_perms(line);
//        std::cout << ret << std::endl;
//        res += ret;
        res += get_perms(line);
    }

    std::cout << res << std::endl; // 620189727003627
}

