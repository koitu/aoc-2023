#include <iostream>
#include <fstream>
#include <ctype.h>
#include <vector>

std::vector<std::string> num{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const int MIN_LEN = 3;
const int MAX_LEN = 5;

// TODO: produce a trie from these num

int find_num(const std::string s) {
    int len = s.length();
    for (int i = MIN_LEN; i <= MAX_LEN && i <= len; i++) {
        std::string sub = s.substr(0, i);

        for (int j = 0; j < 9; j++) {
            if (sub.compare(num[j]) == 0) {
                return j + 1;
            }
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    std::string input_file = "./input.txt";

    std::fstream file(input_file);
    std::string line;
    int sum = 0;
    while(std::getline(file, line)) {
        const int len = line.length();

        for (int i = 0; i < len; i++) {
            if (isdigit(line[i])) {
                sum += 10 * (int)(line[i] - '0');
                break;
            }

            int res = find_num(line.substr(i));
            if (res != -1) {
                sum += 10 * res;
                break;
            }
        }

        for (int i = len - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                sum += (int)(line[i] - '0');
                break;
            }

            int res = find_num(line.substr(i));
            if (res != -1) {
                sum += res;
                break;
            }
        }
    }
    std::cout << sum << std::endl;  // 55260
}
