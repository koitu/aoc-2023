#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Node {
public:
    std::string name;
    std::string left;
    std::string right;
    Node* L;
    Node* R;

    Node(std::string name) : name(name) {}
};

std::map<std::string, Node*> n_map;

int main(int argc, char *argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;

    getline(file, line);
    const std::string path = line;

    getline(file, line);
    std::vector<Node*> nodes;
    while(getline(file, line)) {
        std::string name = line.substr(0, 3);
        Node* n = new Node(name);
        n->left = line.substr(7, 3);
        n->right = line.substr(12, 3);
        nodes.push_back(n);
        n_map[name] = n;
    }

    // TODO: do you really need this?
    for (auto &n: nodes) {
        n->L = n_map[n->left];
        n->R = n_map[n->right];
    }

    int res = 0;
    Node* cur = n_map["AAA"];
    while(true) {
        for (auto &c: path) {
            if (cur->name != "ZZZ") {
                res++;
                switch(c) {
                    case 'L':
                        cur = cur->L;
                        break;
                    case 'R':
                        cur = cur->R;
                        break;
                    default:
                        std::cout << "error!" << std::endl;
                }
            } else {
                for (auto n: nodes) {
                    delete n;
                }
                std::cout << res << std::endl;  // 21409
                return 0;
            }
        }
    }
}
