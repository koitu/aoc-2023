#include <vector>
#include <string>
#include <fstream>
#include <iostream>

typedef long long ll;

int count_bits(ll a) {
    // damn there are some crazy ways to do this...
    // https://stackoverflow.com/questions/109023/count-the-number-of-set-bits-in-a-32-bit-integer

    int res = 0;

    while (a > 0) {
        if (a & 1) {
            res++;
        }

        a >>= 1;
    }

    return res;
}

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    int res = 0;
    while (true) {
        if (!getline(file, line)) {
            break;
        }

        ll cur_c = 1;
        std::vector<ll> rows;
        std::vector<ll> cols(line.size(), 0);

        do {
            if (line == "") {
                break;
            }

            ll row = 0;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '#') {
                    row += (1 << i);
                    cols[i] += cur_c;
                }
            }

            rows.push_back(row);
            cur_c <<= 1;
        } while (getline(file, line));


        for (int i = 0; i < cols.size(); i++) {
            int bit_diff = 0;

            int j = 0;
            while (i - j >= 0 && i + 1 + j < cols.size()) {
                bit_diff += count_bits(cols[i - j] ^ cols[i + 1 + j]);
                if (bit_diff > 1) break;
                j++;
            }

            if (bit_diff == 1) {
                res += (i + 1);
            }
        }

        for (int i = 0; i < rows.size(); i++) {
            int bit_diff = 0;

            int j = 0;
            while (i - j >= 0 && i + 1 + j < rows.size()) {
                bit_diff += count_bits(rows[i - j] ^ rows[i + 1 + j]);
                if (bit_diff > 1) break;
                j++;
            }

            if (bit_diff == 1) {
                res += (i + 1) * 100;
            }
        }
    }

    // we are basically just computing the hamming distance
    // and only accepting when the distance is 1 (i.e. one flip)
    std::cout << res << std::endl; // 36474
}
