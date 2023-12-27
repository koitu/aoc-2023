#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


typedef long long ll;

class disk {
    int width, height;

    std::vector<std::string> rocks;

    void tilt_north();
    void tilt_east();
    void tilt_south();
    void tilt_west();

public:
    disk(std::vector<std::string> rocks) : rocks(rocks) {
        disk::height = rocks.size();
        disk::width = rocks[0].length();
    };

    void cycle() {
        disk::tilt_north();
        disk::tilt_west();
        disk::tilt_south();
        disk::tilt_east();
    };

    int score();
    std::vector<ll> summary();
};

void disk::tilt_north() {
    std::vector<int> last(disk::width, 0);

    for (int i = 0; i < disk::height; i++) {
        for (int j = 0; j < disk::width; j++) {
            switch (disk::rocks[i][j]) {
                case '#':
                    last[j] = i + 1;
                    break;
                case 'O':
                    disk::rocks[i][j] = '.';
                    disk::rocks[last[j]][j] = 'O';
                    last[j]++;
                    break;
            }
        }
    }
}

void disk::tilt_east() {
    std::vector<int> last(disk::height, disk::width - 1);

    for (int i = disk::width - 1; i >= 0; i--) {
        for (int j = 0; j < disk::height; j++) {
            switch (disk::rocks[j][i]) {
                case '#':
                    last[j] = i - 1;
                    break;
                case 'O':
                    disk::rocks[j][i] = '.';
                    disk::rocks[j][last[j]] = 'O';
                    last[j]--;
                    break;
            }
        }
    }
}

void disk::tilt_south() {
    std::vector<int> last(disk::width, disk::height - 1);

    for (int i = disk::height - 1; i >= 0; i--) {
        for (int j = 0; j < disk::width; j++) {
            switch (disk::rocks[i][j]) {
                case '#':
                    last[j] = i - 1;
                    break;
                case 'O':
                    disk::rocks[i][j] = '.';
                    disk::rocks[last[j]][j] = 'O';
                    last[j]--;
                    break;
            }
        }
    }
}

void disk::tilt_west() {
    std::vector<int> last(disk::height, 0);

    for (int i = 0; i < disk::width; i++) {
        for (int j = 0; j < disk::height; j++) {
            switch (disk::rocks[j][i]) {
                case '#':
                    last[j] = i + 1;
                    break;
                case 'O':
                    disk::rocks[j][i] = '.';
                    disk::rocks[j][last[j]] = 'O';
                    last[j]++;
                    break;
            }
        }
    }
}

int disk::score() {
    int sum = 0;
    int cur = disk::height;

    for (auto &s: disk::rocks) {
        for (auto &c: s) {
            if (c == 'O') sum += cur;
        }
        cur--;
    }
    return sum;
}

std::vector<ll> disk::summary() {
    std::vector<ll> sum_arr;

    for (auto &s: disk::rocks) {
        ll sum = 0;
        int i = 0;

        for (auto &c: s) {
            if (c == 'O') {
                sum += 1 << i;
            }
            i++;
        }
        sum_arr.push_back(sum);
    }
    return sum_arr;
}

std::vector<int> scores;
std::map<std::vector<ll>, int> visited;

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    std::vector<std::string> rocks;
    while (getline(file, line)) {
        rocks.push_back(line);
    }

    disk d(rocks);

    int i = 0;
    std::vector<ll> s;

    while (true) {
        d.cycle();
        s = d.summary();
        scores.push_back(d.score());
        if (visited.find(s) != visited.end()) break;

        visited[s] = i;
        i++;
    }

    int offset = visited[s];
    int cycle = i - visited[s];

    ll end = (1000000000 - offset) % cycle;
    std::cout << scores[offset + end - 1] << std::endl;  // 104619
}