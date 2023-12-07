#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

std::map<char, char> s_map{
    {'2', 'a'},
    {'3', 'b'},
    {'4', 'c'},
    {'5', 'd'},
    {'6', 'e'},
    {'7', 'f'},
    {'8', 'g'},
    {'9', 'h'},
    {'T', 'i'},
    {'J', 'j'},
    {'Q', 'k'},
    {'K', 'l'},
    {'A', 'm'}};

enum card_t {
    HIGH = 0,
    ONE_PAIR = 1,
    TWO_PAIR = ONE_PAIR + ONE_PAIR,
    THREE_KIND = 3,
    FULL_HOUSE = ONE_PAIR + THREE_KIND,
    FOUR_KIND = 5,
    FIVE_KIND = 6,
};

class Card {
public:
    std::string card;
    int type;
    int value;
    Card(std::string card, int value) {
        this->value = value;

        std::string s;
        for (auto &it: card) {
            s.push_back(s_map[it]);
        }

        this->card = s;
        std::sort(s.begin(), s.end());

        std::vector<int> matches;
        int cur = -1;
        char prev = '0';
        for (auto &it: s) {
            if (it != prev) {
                matches.push_back(0);
                cur++;
                prev = it;
            }
            matches[cur]++;
        }

        int c_type = HIGH;
        for (auto &it: matches) {
            switch (it) {
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
                    std::cout << "error!" << std::endl;
            }
        }

        this->type = c_type;
    }

    bool operator<(const Card &c) {
        if (type != c.type) {
            return type < c.type;
        }
        return card < c.card;
    }
};


int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    std::vector<Card> cards;
    while(getline(file, line)) {
        size_t pos = line.find(" ");
        cards.push_back(Card(line.substr(0, pos),
                             stoi(line.substr(pos + 1))));
    }

    std::sort(cards.begin(), cards.end());
    int res;
    for (int i = 0; i < cards.size(); i++) {
        res += cards[i].value * (i + 1);
    }
    std::cout << res << std::endl;  // 251287184
}
