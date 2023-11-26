#include <iostream>
#include <stack>
#include <vector>

void DFS1(size_t vertex, const std::vector<std::vector<size_t>>& graph, std::vector<bool>& used, std::stack<size_t>& order) {
    used[vertex] = true;
    for(auto& i: graph[vertex]) {
        if(!used[i]) {
            DFS1(i, graph, used, order);
        }
    }
    order.push(vertex);
}


void DFS2(size_t vertex, const std::vector<std::vector<size_t>>& graph_t, std::vector<bool>& used, std::vector<size_t>& components, size_t current_component) {
    components[vertex] = current_component;
    used[vertex] = true;
    for(auto& i: graph_t[vertex]) {
        if(!used[i]) {
            DFS2(i, graph_t, used, components, current_component);
        }
    }
}

std::vector<size_t> Kosaraju(const std::vector<std::vector<size_t>>& graph, const std::vector<std::vector<size_t>>& graph_t, size_t& size) {
    std::vector<bool> used(graph.size(), false);
    std::stack<size_t> order;
    for(size_t i = 0; i < graph.size(); ++i) {
        if(!used[i]) {
            DFS1(i, graph, used, order);
        }
    }
    used.assign(graph.size(), false);
    std::vector<size_t> components(graph.size());
    size_t component = 1;
    for(; !order.empty(); order.pop()) {
        size_t vertex = order.top();
        if(!used[vertex]) {
            DFS2(vertex, graph_t, used, components, component);
            component++;
        }
    }
    size = component - 1;
    return components;
}


int main() {
    size_t n, m;
    std:: cin >> n >> m;
    std::vector<std::vector<size_t>> graph(n);
    std::vector<std::vector<size_t>> graph_t(n);
    size_t a, b;
    for(size_t i = 0; i < m; ++i) {
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph_t[b - 1].push_back(a - 1);
    }
    size_t size;
    std::vector<size_t> result = Kosaraju(graph, graph_t, size);
    std:: cout << size;
    std:: cout << std::endl;
    for(auto& i : result) {
        std:: cout << i;
        std:: cout << ' ';
    }
}


