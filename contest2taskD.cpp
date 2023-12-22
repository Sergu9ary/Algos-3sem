#include <iostream>
#include <stack>
#include <vector>

void DFSGraph(size_t vertex, const std::vector<std::vector<size_t>>& graph, std::vector<bool>& used, std::stack<size_t>& order) {
    used[vertex] = true;
    for (auto& neighbour : graph[vertex]) {
        if (!used[neighbour]) {
            DFSGraph(neighbour, graph, used, order);
        }
    }
    order.push(vertex);
}

void DFSExploreComponent(size_t vertex, const std::vector<std::vector<size_t>>& graph_t, std::vector<bool>& used, std::vector<size_t>& components, size_t current_component) {
    components[vertex] = current_component;
    used[vertex] = true;
    for (auto& i : graph_t[vertex]) {
        if (!used[i]) {
            DFSExploreComponent(i, graph_t, used, components, current_component);
        }
    }
}

std::vector<size_t> Kosaraju(const std::vector<std::vector<size_t>>& graph, const std::vector<std::vector<size_t>>& graph_t, size_t& size) {
    std::vector<bool> used(graph.size(), false);
    std::stack<size_t> order;
    for (size_t i = 0; i < graph.size(); ++i) {
        if (!used[i]) {
            DFSGraph(i, graph, used, order);
        }
    }
    used.assign(graph.size(), false);
    std::vector<size_t> components(graph.size());
    size_t component = 1;
    while (!order.empty()) {
        size_t vertex = order.top();
        order.pop();
        if (!used[vertex]) {
            DFSExploreComponent(vertex, graph_t, used, components, component);
            component++;
        }
    }
    size = component - 1;
    return components;
}

void getInput(std::istream& in, size_t& n, size_t& m, std::vector<std::vector<size_t>>& graph, std::vector<std::vector<size_t>>& graph_t) {
    in >> n >> m;
    graph.resize(n);
    graph_t.resize(n);
    size_t a, b;
    for (size_t i = 0; i < m; ++i) {
        in >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph_t[b - 1].push_back(a - 1);
    }
}

void displayResult(std::ostream& out, const std::vector<size_t>& result, size_t size) {
    out << size << std::endl;
    for (auto& i : result) {
        out << i << ' ';
    }
    out << std::endl;
}

int main() {
    size_t n, m, size;
    std::vector<std::vector<size_t>> graph;
    std::vector<std::vector<size_t>> graph_t;
    getInput(std::cin, n, m, graph, graph_t);

    std::vector<size_t> result = Kosaraju(graph, graph_t, size);
    displayResult(std::cout, result, size);

    return 0;
}
