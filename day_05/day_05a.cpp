#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>


std::vector<std::string> split(std::string s, std::string delimiter) {
    std::vector<std::string> a;
    size_t pos;

    while((pos = s.find(delimiter)) != std::string::npos) {
        a.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    a.push_back(s);
    return a;
}

std::vector<long> nums;
std::vector<long> next;

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);

    size_t pos = line.find(": ");
    line.erase(0, pos + 2);

    std::vector<std::string> a = split(line, " ");
    for (auto &it: a) {
        next.push_back(stol(it));
    }

    nums = std::vector<long>(next.size(), 0);
    while(getline(file, line)) {
        if (line == "") {
            for (int i = 0; i < nums.size(); i++) {
                nums[i] = next[i];
            }
            getline(file, line);
            continue;
        }

        a = split(line, " ");
        long target = stol(a[0]);
        long source = stol(a[1]);
        long range = stol(a[2]);

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] >= source && nums[i] < source + range) {
                next[i] = (nums[i] - source) + target;
            }
        }
    }
    nums = next;

    long l = nums[0];
    for(auto &it: nums) {
        l = it < l ? it : l;
    }
    std::cout << l << std::endl;  // 340994526
}