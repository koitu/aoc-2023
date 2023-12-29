#include <string>
#include <vector>
#include <fstream>
#include <iostream>


typedef long long ll;

std::vector<std::string> split(std::string s) {
    std::vector<std::string> ss;
    size_t pos;

    while ((pos = s.find(',')) != std::string::npos) {
        ss.push_back(s.substr(0, pos));
        s.erase(0, pos + 1);
    }
    ss.push_back(s);

    return ss;
}

int hash(const std::string s) {
    int res = 0;
    for (auto &c: s) {
        res += (int)(c);
        res = (res * 17) % 256;
    }
    return res;
}

class box {
    std::vector<std::pair<std::string, int>> contents;
    int find(const std::string s);

public:
    box() {};
    void remove(const std::string s);
    void insert(const std::string s, int focal);
    int sum();
};

int box::find(const std::string s) {
    int i = 0;
    for (auto &p: contents) {
        if (p.first == s) return i;
        i++;
    }
    return -1;
}

void box::remove(const std::string s) {
    int i = box::find(s);

    if (i != -1) {
        contents.erase(contents.begin() + i);
    }
}

void box::insert(const std::string s, int focal) {
    int i = box::find(s);

    if (i != -1) {
        contents[i].second = focal;
    } else {
        contents.push_back(
                std::pair<std::string, int>(s, focal));
    }
}

int box::sum() {
    int res = 0;
    int i = 1;

    for (auto &p: contents) {
        res += (i * p.second);
        i++;
    }

    return res;
}

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);
    std::vector<std::string> ss = split(line);

    std::vector<box> boxes(256, box());
    for (auto &s: ss) {
        size_t eq_pos = s.find('=');
        size_t sub_pos = s.find('-');

        std::string ha;
        if (eq_pos != std::string::npos) {
            ha = s.substr(0, eq_pos);
            int h = hash(ha);
            int fl = stoi(s.substr(eq_pos + 1));

            boxes[h].insert(ha, fl);

        } else if (sub_pos != std::string::npos) {
            ha = s.substr(0, sub_pos);
            int h = hash(ha);

            boxes[h].remove(ha);

        } else {
            std::cout << "error!" << std::endl;
        }
    }

    int res = 0;
    int i = 1;
    for (auto &b: boxes) {
        res += (i * b.sum());
        i++;
    }

    std::cout << res << std::endl;  // 290779
}
