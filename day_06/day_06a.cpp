#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<int> parse(std::string s) {
    s.erase(0, s.find(": ") + 2);
    std::vector<int> a;

    std::stringstream stream(s);

    int n;
    while(stream >> n) {
        a.push_back(n);
    }
    return a;
}

float max(float a, float b) {
    return a > b ? a : b;
}

float min(float a, float b) {
    return a < b ? a : b;
}

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);
    std::vector<int> times = parse(line);

    getline(file, line);
    std::vector<int> dists = parse(line);

    int n = times.size();
    int res = 1;
    for (int i = 0; i < n; i++) {
        float time = static_cast<float>(times[i]);  // total time for race
        float dist = static_cast<float>(dists[i]);  // dist to beat

        // x -> now long to hold
        // t -> time for race
        // d -> distance to "beat" (is that >= or >)
        // find integer value of x such that: d < (t - x)x = -x^2 + at   ->   0 < -x^2 + xt - d
        // (-t \pm sqrt(t^2 - 4d))/-2   ->    t/2 \pm sqrt(t^2/4 - d)
        float a = sqrt(time*time/4 - dist);
        float begin = max(time/2 - a, 0);
        float end = min(time/2 + a, time);

        // get the number of integers on open interval (begin, end)
        res *= ceil(end) - floor(begin) - 1;
    }

    std::cout << res << std::endl;  // 227850
}
