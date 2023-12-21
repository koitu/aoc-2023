#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<int> split_nums(std::string s) {
    size_t pos;
    std::vector<int> res;
    while ((pos = s.find(',')) != std::string::npos) {
        res.push_back(stoi(s.substr(0, pos)));
        s.erase(0, pos + 1);
    }
    res.push_back(stoi(s));

    return res;
}

int count_perms(const std::string s, const std::vector<int> nums) {
    if (s.empty()) {
        return nums.empty() ? 1 : 0;
    }

    std::string c(s);
    std::string cc;
    std::vector<int> num(nums);

    switch (c[0]) {
        case '.':
            // if start with . then erase until no .
            while(!c.empty() && c[0] == '.') c.erase(0, 1);
            return count_perms(c, num);

        case '#':
            // if start with # then use first num
            if (nums.empty() || c.length() < num[0]) return 0;
            for (int i = 0; i < num[0]; i++) {
                if (c[i] == '.') {
                    return 0;
                }
            }
            c.erase(0, num[0]);
            num.erase(num.begin());

            if (!num.empty()) {
                if (c.empty() || c[0] == '#') {
                    return 0;
                }
                c.erase(0, 1);
            }
            return count_perms(c, num);

        case '?':
            // if start with ? then replace with either . or #
            c[0] = '.';
            cc = s;
            cc[0] = '#';

            return count_perms(c, nums) + count_perms(cc, nums);

        default:
            std::cout << "error!" << std::endl;
            return 0;
    }
}

int count_perms(std::string s) {
    size_t pos = s.find(' ');
    std::string arrange = s.substr(0, pos);
    s.erase(0, pos + 1);

    std::vector<int> nums = split_nums(s);
    return count_perms(arrange, nums);
}

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    int res = 0;
    while (getline(file, line)) {
//        int ret = count_perms(line);
//        std::cout << ret << std::endl;
        res += count_perms(line);
    }

    std::cout << res << std::endl;  // 8180
}