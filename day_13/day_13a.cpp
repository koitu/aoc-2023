#include <string>
#include <vector>
#include <fstream>
#include <iostream>


typedef long long ll;

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    int res = 0;
    while (true) {
        if (!getline(file, line)) break;

        ll cur_c = 1;
        std::vector<ll> rows;
        std::vector<ll> cols(line.size(), 0);

        do {
            if (line == "") break;

            ll cur_r = 0;
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == '#') {
                    cur_r += 1 << i;
                    cols[i] += cur_c;
                }
            }
            rows.push_back(cur_r);
            cur_c = cur_c << 1;

        } while (getline(file, line));

        for (int i = 0; i < cols.size() - 1; i++) {
            bool ref = true;

            int j = 0;
            // split vertically between i and i + 1
            while (i - j >= 0 && (i + 1) + j < cols.size()) {
                if (cols[i - j] != cols[(i + 1) + j]) {
                    ref = false;
                    break;
                }
                j++;
            }

            if (ref) {
                res += (i + 1);
            }
        }

        for (int i = 0; i < rows.size() - 1; i++) {
            bool ref = true;

            int j = 0;
            // split horizontally between i and i + 1
            while (i - j >= 0 && (i + 1) + j < rows.size()) {
                if (rows[i - j] != rows[(i + 1) + j]) {
                    ref = false;
                    break;
                }
                j++;
            }

            if (ref) {
                res += (i + 1) * 100;
            }
        }

//        std::cout << "   ";
//        for (auto &c: cols) {
//            std::cout << c << "  ";
//        }
//        std::cout << std::endl;
//
//        for (auto &r: rows) {
//            std::cout << r << std::endl;
//        }
//        std::cout << std::endl;
    }

    std::cout << res << std::endl; // 30158
}