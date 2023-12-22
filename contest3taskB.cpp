#include <climits>
#include <iostream>
#include <queue>
#include <vector>

void setEdge(std::vector<std::vector<std::pair<size_t, size_t>>>& edges, size_t v_from, size_t v_to, size_t v_cost) {
    edges[v_from].emplace_back(v_to, v_cost);
    edges[v_to].emplace_back(v_from, v_cost);
}

const std::vector<size_t>& calculatePath(std::vector<std::vector<std::pair<size_t, size_t>>>& edges,
                                         std::vector<size_t>& distances,
                                         size_t start_vertex, size_t finish_vertex) {
    distances[start_vertex] = 0;
    std::vector<bool> used(edges.size(), false);
    std::priority_queue<std::pair<size_t, size_t>> heap;
    heap.emplace(0, start_vertex);

    while (!heap.empty()) {
        size_t current = heap.top().second;
        heap.pop();
        if (distances[current] > distances[finish_vertex]) {
            return distances;
        }
        if (used[current]) {
            continue;
        }
        used[current] = true;
        for (const auto& edge : edges[current]) {
            if (!used[edge.first]) {
                distances[edge.first] = std::min(distances[edge.first], distances[current] + edge.second);
                heap.emplace(-distances[edge.first], edge.first);
            }
        }
    }
    return distances;
}

void getInput(std::istream& in, size_t& vertex_count, size_t& edge_count, size_t& infection_count,
              std::vector<size_t>& infection_points,
              std::vector<std::vector<std::pair<size_t, size_t>>>& edges) {
    in >> vertex_count >> edge_count >> infection_count;

    edges.resize(vertex_count);

    size_t v_from, v_to, v_cost;
    for (size_t i = 0; i < infection_count; ++i) {
        in >> v_from;
        infection_points.push_back(v_from - 1);
    }

    for (size_t i = 0; i < edge_count; ++i) {
        in >> v_from >> v_to >> v_cost;
        setEdge(edges, v_from - 1, v_to - 1, v_cost);
    }
}

void getStartFinishVertices(std::istream& in, size_t& start_vertex, size_t& finish_vertex) {
    in >> start_vertex >> finish_vertex;
}

void displayResult(std::ostream& out, size_t answer) {
    out << answer << std::endl;
}

int main() {
    size_t vertex_count, edge_count, infection_count;
    std::vector<size_t> infection_points;
    std::vector<std::vector<std::pair<size_t, size_t>>> edges;
    getInput(std::cin, vertex_count, edge_count, infection_count, infection_points, edges);

    size_t start_vertex, finish_vertex;
    getStartFinishVertices(std::cin, start_vertex, finish_vertex);

    std::vector<size_t> distances(vertex_count, LLONG_MAX);
    auto distances_result = calculatePath(edges, distances, finish_vertex - 1, start_vertex - 1);
    size_t answer = distances_result[start_vertex - 1];

    for (const auto& infection_point : infection_points) {
        if (distances_result[infection_point] <= answer) {
            displayResult(std::cout, -1);
            return 0;
        }
    }

    displayResult(std::cout, answer);
    return 0;
}
