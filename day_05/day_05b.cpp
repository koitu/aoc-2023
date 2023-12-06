#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

typedef long long ll;

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

std::vector<ll> num_list(std::string s, std::string delimiter) {
    std::vector<std::string> a = split(s, delimiter);
    std::vector<ll> b;

    for (auto &it: a) {
        b.push_back(stoll(it));
    }
    return b;
}

class Interval {
public:
    ll start;   // start of interval (inclusive)
    ll end;     // end of interval (inclusive)

    Interval(ll s, ll e) : start(s), end(e) {}
    Interval(const Interval& i) : start(i.start), end(i.end) {}
    bool operator<(const Interval& i) const {
        return start < i.start;
    }
};

std::vector<Interval> cur;
std::vector<Interval> next;

void sort_and_merge() {
    std::sort(cur.begin(), cur.end());

    int i = 0;
    while (i < cur.size() - 1) {
        if (cur[i].end + 1 >= cur[i+1].start) {
            cur[i].end = cur[i+1].end;
            cur.erase(cur.begin() + i + 1);
        } else {
            i++;
        }
    }
}

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);
    line = split(line, ": ")[1];

    std::vector<ll> nums = num_list(line, " ");
    for (int i = 0; i < nums.size(); i += 2) {
        next.push_back(Interval(nums[i], nums[i] + nums[i+1] - 1));
    }

    while(getline(file, line)) {
        if (line == "") {
            for (auto &it: cur) {
                next.push_back(it);
            }
            cur = next;
            next.clear();
            sort_and_merge();
            getline(file, line);
            continue;
        }

        nums = num_list(line, " ");
        ll start = nums[1];
        ll end = start + nums[2] - 1;
        ll translate = nums[0] - start;

        int pos = 0;
        size_t done = cur.size();
        while (pos < done) {
            Interval inter = cur[pos];
            if (end < inter.start || inter.end < start) {
                // no overlap between interval and map
                pos++;
                continue;
            }

            if (start <= inter.start && inter.end <= end) {
                //  [ interval ]
                // [ map        ]
                next.push_back(Interval(inter.start + translate,
                                        inter.end + translate));

            } else if (inter.start < start && end < inter.end) {
                //  [ interval ]
                //   [ map    ]
                cur.push_back(Interval(inter.start,
                                       start - 1));
                next.push_back(Interval(start + translate,
                                        end + translate));
                cur.push_back(Interval(end + 1,
                                       inter.end));

            } else if (start <= inter.start && end < inter.end) {
                //  [ interval ]
                // [ map    ]###
                next.push_back(Interval(inter.start + translate,
                                        end + translate));
                cur.push_back(Interval(end + 1,
                                       inter.end));

            } else if (inter.start < start && inter.end <= end) {
                // [ interval ]
                // ###[ map    ]
                cur.push_back(Interval(inter.start,
                                       start - 1));
                next.push_back(Interval(start + translate,
                                        inter.end + translate));

            } else {
                std::cout << "error!" << std::endl;
            }
            cur.erase(cur.begin() + pos);
            done--;
        }
    }
    for (auto &it: cur) {
        next.push_back(it);
    }
    cur = next;
    sort_and_merge();

    ll low = cur[0].start;
    for (auto &it: cur) {
        low = it.start < low ? it.start : low;
    }
    std::cout << low << std::endl;  // 52210644
}