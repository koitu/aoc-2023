#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Node {
public:
    std::string name, left, right;
    Node* L;
    Node* R;
};

std::map<std::string, Node*> n_map;

int main(int argc, char* argv[]) {
    std::string input = "./input.txt";

    std::fstream file(input);
    std::string line;
    getline(file, line);

    const std::string path = line;
    getline(file, line);

    std::vector<Node*> nodes;
    while(getline(file, line)) {
        std::string name = line.substr(0, 3);
        Node* n = new Node();
        n->name = name;
        n->left = line.substr(7, 3);
        n->right = line.substr(12, 3);

        n_map[name] = n;
        nodes.push_back(n);
    }

    for (auto &n: nodes) {
        n->L = n_map[n->left];
        n->R = n_map[n->right];
    }

    // TODO: optimization
    //  - use the fact the path is repeating
    //  - if you are in the same index of path and same location then you have repeated
    //  - 6 A's and 6 Z's (6! = 720 ways)
    //  - brute force convert NFA to DFA

    // after path.length() * nodes.size() + 1 you must have repeated the (path, node) state at least once

//    std::vector<Node*> cur;
//    std::vector<Node*> next;
//    for (auto &n: nodes) {
//        if (n->name[2] == 'A') {
//            next.push_back(n);
//        }
//    }
//
//    int res = 0;
//    while(true) {
//        for (auto &c: path) {
//            cur = next;
//            next.clear();
//
//            bool done = true;
//            for (auto &n: cur) {
//                if (n->name[2] != 'Z') {
//                    done = false;
//                    break;
//                }
//            }
//
//            if (!done) {
//                res++;
//                if ((res & (res - 1)) == 0) {
//                    std::cout << res << std::endl;
//                }
//
//                for (auto &n: cur) {
//                    switch (c) {
//                        case 'L':
//                            next.push_back(n->L);
//                            break;
//
//                        case 'R':
//                            next.push_back(n->R);
//                            break;
//
//                        default:
//                            std::cout << "error!" << std::endl;
//                    }
//                }
//
//            } else {
//                std::cout << res << std::endl;
//                for (auto &n: cur) {
//                    delete n;
//                }
//                return 0;
//            }
//        }
//    }
}
