#include <vector>
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);
    const int n = line.size();

    std::vector<int> cur_h(n, 0);
    int level = 1;
    int rocks = 0;
    int res = 0;

    do {
        for (int i = 0; i < n; i++) {
            if (line[i] == '#') {
                cur_h[i] = level;
            } else if (line[i] == 'O') {
                cur_h[i]++;
                rocks++;
                res += cur_h[i];
            }
        }

        level++;
    } while(getline(file, line));

    std::cout << (level * rocks) - res << std::endl;  // 112046
}
