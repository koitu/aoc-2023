#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

int max(int a, int b) {
    return a < b ? b : a;
}

std::map<char, char> c_map{
        {'J', 'a'},
        {'2', 'b'},
        {'3', 'c'},
        {'4', 'd'},
        {'5', 'e'},
        {'6', 'f'},
        {'7', 'g'},
        {'8', 'h'},
        {'9', 'i'},
        {'T', 'j'},
        {'Q', 'k'},
        {'K', 'l'},
        {'A', 'm'}};

enum hand_t {
    HIGH = 0,
    ONE_PAIR = 1,
    TWO_PAIR = ONE_PAIR + ONE_PAIR, // 2
    THREE_KIND = 3,
    FULL_HOUSE = ONE_PAIR + THREE_KIND, // 4
    FOUR_KIND = 5,
    FIVE_KIND = 6,
};

class Card {
    int get_type(std::string s) {
        std::sort(s.begin(), s.end());

        std::vector<int> matches;
        int cur = -1;
        char prev = ' ';
        for (auto &c: s) {
            if (c != prev) {
                matches.push_back(0);
                cur++;
                prev = c;
            }
            matches[cur]++;
        }

        int c_type = HIGH;
        for (auto &m: matches) {
            switch (m) {
                case 1:
                    c_type += HIGH;
                    break;
                case 2:
                    c_type += ONE_PAIR;
                    break;
                case 3:
                    c_type += THREE_KIND;
                    break;
                case 4:
                    c_type += FOUR_KIND;
                    break;
                case 5:
                    c_type += FIVE_KIND;
                    break;
                default:
                    std::cout << "error: " << s << std::endl;
            }
        }
        return c_type;
    }

public:
    int type;
    int value;
    std::string card;

    Card(std::string s) {
        size_t pos = s.find(" ");
        value = stoi(s.substr(pos + 1));
        s.erase(pos);

        for (auto &it: s) {
            card.push_back(c_map[it]);
        }
        s = card;

        std::sort(s.begin(), s.end());
        char prev = ' ';
        int a_count = 0;
        std::vector<char> other_chars;
        for (auto &c: s) {
            if (prev != c) {
                other_chars.push_back(c);
                prev = c;
            }
            if (c == 'a') {
                a_count++;
            }
        }

        type = get_type(s);
        if (a_count == 0) {
            return;
        }

        std::string j;
        for (auto &c: other_chars) {
            for (auto &a: s) {
                if (a == 'a') {
                    j.push_back(c);
                } else {
                    j.push_back(a);
                }
            }

            type = max(type, get_type(j));
            j.clear();
        }
    }
    bool operator<(const Card &c) {
        if (type == c.type) {
            return card < c.card;
        }
        return type < c.type;
    }
};

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    std::vector<Card> cards;
    while(getline(file, line)) {
        cards.push_back(Card(line));
    }

    std::sort(cards.begin(), cards.end());
    int res = 0;
    for (int i = 0; i < cards.size(); i++) {
        res += cards[i].value * (i + 1);
    }
    std::cout << res << std::endl;  // 250757288
}
