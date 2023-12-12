#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b != 0) {
//        a, b = b, a % b;
        ll c = a % b;
        a = b;
        b = c;
    }
    return a;
}

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

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

    std::vector<Node*> find;
    for (auto &n: nodes) {
        if (n->name[2] == 'A') {
            find.push_back(n);
        }
    }

    std::vector<int> found;
    for (auto &f: find) {
        Node* cur = f;
        int res = 0;
        bool done = false;

        while(!done) {
            for (auto &c: path) {
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

                if (cur->name[2] == 'Z') {
                    std::cout << res << std::endl;
                    found.push_back(res);
                    done = true;
                    break;
                }
            }
        }
    }

    ll res = 1;
    for (int &f: found) {
        res = lcm(res, static_cast<ll>(f));
    }

    // really dislike this, not explained in the question but
    //  - for each starting node they will only visit one ending node
    //  - after visiting that ending node they will go back to the starting node on the next step
    std::cout << res << std::endl;  // 21165830176709

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
