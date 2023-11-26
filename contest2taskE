#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Graph {
public:
    static const std::string WHITE;
    static const std::string GRAY;
    static const std::string BLACK;

    int amount;
    std::vector<int> back, t_in;
    std::vector<std::vector<std::pair<int, int>>> pairgr;

    Graph(int arg1, int m) : amount(1) {
        t_in.resize(arg1 + 1);
        pairgr.resize(arg1 + 1);
        col.resize(arg1 + 1);
        back.resize(arg1 + 1);

        pairgr[0].push_back({-1, -1});
        for (int i = 0; i <= arg1; i++) {
            col[i] = WHITE;
        }
        for (int64_t i = 1; i <= m; i++) {
            int first, second;
            std::cin >> first >> second;

            if (first == second) {
                continue;
            }
            fir.push_back({first, second});
            ++amount;
            pairgr[first].push_back({second, amount - 1});
            pairgr[second].push_back({first, amount - 1});
        }
    }

    void DFS(int& arg1_param, int& arg2, int t) {
        col[arg1_param] = GRAY;
        t_in[arg1_param] = t;
        back[arg1_param] = t;
        ++t;
        size_t i = 0;
        while (i < pairgr[arg1_param].size()) {
            auto elem = pairgr[arg1_param][i].first;
            if (elem == arg2) {
                i++;
                continue;
            }

            if (col[elem] == WHITE) {
                DFS(elem, arg1_param, t);
                back[arg1_param] = std::min(back[arg1_param], back[elem]);
            } else {
                back[arg1_param] = std::min(back[arg1_param], t_in[elem]);
            }

            i++;
        }
        if (back[arg1_param] == t_in[arg1_param] && arg2 != -1 && Search(arg2, arg1_param) == 1) {
            most.push_back({arg2, arg1_param});
        }
        col[arg1_param] = BLACK;
    }

    void InsFunc(std::set<int>& result) {
        size_t j;
        for (j = 0; j < most.size(); j++) {
            size_t i;
            for (i = 0; i < pairgr[most[j].first].size(); i++) {
                auto fir = pairgr[most[j].first][i].first;
                auto sec = most[j].second;
                if (fir == sec) {
                    result.insert(pairgr[most[j].first][i].second);
                    break;
                }
            }
        }
    }

    void Solve() {
        int t = 0;
        std::set<int> result;
        int k_const = -1;

        for (int i = 0; i < pairgr.size(); i++) {
            if (col[i] == WHITE) {
                DFS(i, k_const, t);
            }
        }
        InsFunc(result);

        std::cout << most.size() << std::endl;

        for (auto& it : result) {
            std::cout << it << " ";
        }
    }

private:
    int Search(int xval, int yval) {
        int num = 0;
        int i = 0;
        while (i < static_cast<int>(pairgr[xval].size())) {
            if (pairgr[xval][i].first == yval) {
                num++;
            }
            i++;
        }
        if (num <= 1) {
            return 1;
        }
        return 0;
    }

    std::vector<std::pair<int, int>> most, fir;
    std::vector<std::string> col;
};

const std::string Graph::WHITE = "white";
const std::string Graph::GRAY = "gray";
const std::string Graph::BLACK = "black";

int main() {
    int arg1, m;
    std::cin >> arg1 >> m;

    Graph graph(arg1, m);
    graph.Solve();

    return 0;
}
