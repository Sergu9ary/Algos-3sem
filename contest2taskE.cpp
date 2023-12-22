#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Graph {
private:
    const std::string WHITE = "white";
    const std::string GRAY = "gray";
    const std::string BLACK = "black";

    int size;
    std::vector<int> back, t_in;
    std::vector<std::vector<std::pair<int, int>>> edges;
    std::vector<std::pair<int, int>> bridges;
    std::vector<std::pair<int, int>> stronglyConnectedComponents;
    std::vector<std::string> col;

    int Search(int a, int b) {
        int num = 0;
        int i = 0;
        while (i < static_cast<int>(edges[a].size())) {
            if (edges[a][i].first == b) {
                num++;
            }
            i++;
        }
        if (num <= 1) {
            return 1;
        }
        return 0;
    }

public:
    Graph(int arg1, int m) : size(1) {
        t_in.resize(arg1 + 1);
        edges.resize(arg1 + 1);
        col.resize(arg1 + 1);
        back.resize(arg1 + 1);

        edges[0].push_back({-1, -1});
        for (int i = 0; i <= arg1; i++) {
            col[i] = WHITE;
        }
        for (int64_t i = 1; i <= m; i++) {
            int first, second;
            std::cin >> first >> second;

            if (first == second) {
                continue;
            }
            bridges.push_back({first, second});
            ++size;
            edges[first].push_back({second, size - 1});
            edges[second].push_back({first, size - 1});
        }
    }

    void DFS(int& current_vertex, int& target_vertex, int time) {
        col[current_vertex] = GRAY;
        t_in[current_vertex] = time;
        back[current_vertex] = time;
        ++time;
        size_t i = 0;
        while (i < edges[current_vertex].size()) {
            auto elem = edges[current_vertex][i].first;
            if (elem == target_vertex) {
                i++;
                continue;
            }

            if (col[elem] == WHITE) {
                DFS(elem, current_vertex, time);
                back[current_vertex] = std::min(back[current_vertex], back[elem]);
            } else {
                back[current_vertex] = std::min(back[current_vertex], t_in[elem]);
            }

            i++;
        }
        if (back[current_vertex] == t_in[current_vertex] && target_vertex != -1 && Search(target_vertex, current_vertex) == 1) {
            stronglyConnectedComponents.push_back({target_vertex, current_vertex});
        }
        col[current_vertex] = BLACK;
    }

    void InsertFunc(std::set<int>& result) {
        for (size_t j = 0; j < stronglyConnectedComponents.size(); j++) {
            for (size_t i = 0; i < edges[stronglyConnectedComponents[j].first].size(); i++) {
                auto fir = edges[stronglyConnectedComponents[j].first][i].first;
                auto sec = stronglyConnectedComponents[j].second;
                if (fir == sec) {
                    result.insert(edges[stronglyConnectedComponents[j].first][i].second);
                    break;
                }
            }
        }
    }

    void Solve() {
        int t = 0;
        std::set<int> result;
        int k_const = -1;

        for (int i = 0; i < edges.size(); i++) {
            if (col[i] == WHITE) {
                DFS(i, k_const, t);
            }
        }
        InsertFunc(result);

        std::cout << stronglyConnectedComponents.size() << std::endl;

        for (auto& it : result) {
            std::cout << it << " ";
        }
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n, m);
    graph.Solve();

    return 0;
}
