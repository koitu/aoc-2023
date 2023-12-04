#include <iostream>
#include <fstream>
#include <ctype.h>

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
        }

        for (int i = len - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                sum += (int)(line[i] - '0');
                break;
            }
        }
    }
    std::cout << sum << std::endl;  // 55123
}