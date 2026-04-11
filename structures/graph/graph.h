#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

namespace {

enum class Color { kGray, kWhite, kBlack };
using IntGraph = std::vector<std::vector<int>>;
using WeightedGraph = std::vector<std::vector<std::pair<int, int>>>;

inline void PaintWhite(Color* arr, size_t n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = Color::kWhite;
    }
}

void FillGraph(int m, IntGraph& graph) {
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }
}

void PrintGraph(const IntGraph& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        std::cout << i + 1 << ": ";
        for (const int& neighbor : graph[i]) {
            std::cout << neighbor << ' ';
        }
        std::cout << std::endl;
    }
}

int BFS(const IntGraph& graph) { // for components count
    int n = graph.size();
    Color colors[n]; 
    PaintWhite(colors, n);

    int components = 0;
    std::queue<int> que;

    for (int i = 0; i < n; ++i) {
        if (colors[i] != Color::kWhite) { continue; }   
        components++;
        que.push(i);
        colors[i] = Color::kGray;   

        while (!que.empty()) {
            int current = que.front();
            que.pop();
            for (const int& neighbor : graph[current]) {
                if (colors[neighbor] == Color::kWhite) {
                    colors[neighbor] = Color::kGray;
                    que.push(neighbor);
                }
            }
            colors[current] = Color::kBlack;
        }
    }
    return components;
}

std::vector<int> BFS(const IntGraph& graph, int first_v) { // for k-length path
    int n = graph.size();
    std::vector<int> dist(n, INT32_MAX);
    
    std::queue<int> que;
    dist[first_v] = 0;
    que.push(first_v);

    while (!que.empty()) {
        int current = que.front();
        que.pop();

        for (const int& neighbor: graph[current]) {
            if (dist[neighbor] > dist[neighbor] + 1) {
                dist[neighbor] = dist[neighbor] + 1;
                que.push(neighbor);
            }
        }
    }
    return dist;
}

void DFS(const IntGraph& graph, int v, std::vector<Color>& color) {
    color[v] = Color::kGray;
    for (int u : graph[v]) {
        if (color[u] == Color::kWhite) {
            DFS(graph, u, color);
        }
    }
    color[v] = Color::kBlack;
}

void TopSortDFS(const IntGraph& graph, int v,
                std::vector<Color>& color,
                std::vector<int>& order,
                bool& has_cycle) {
    color[v] = Color::kGray;

    for (int u : graph[v]) {
        if (color[u] == Color::kGray) {
            has_cycle = true;
            return;
        }
        if (color[u] == Color::kWhite) {
            TopSortDFS(graph, u, color, order, has_cycle);
            if (has_cycle) return;
        }
    }

    color[v] = Color::kBlack;
    order.push_back(v);
}

std::vector<int> TopologicalSort(const IntGraph& graph) {
    int n = graph.size();
    std::vector<Color> color(n, Color::kWhite);
    std::vector<int> order;
    bool has_cycle = false;

    for (int v = 0; v < n; ++v) {
        if (color[v] == Color::kWhite) {
            TopSortDFS(graph, v, color, order, has_cycle);
        }
    }

    if (has_cycle) {
        return {};
    }

    std::reverse(order.begin(), order.end());
    return order;
}

std::pair<std::vector<int>, std::vector<int>> Dijkstra(const WeightedGraph& graph, int start) {
    int n = graph.size();
    std::vector<int> dist(n, INT32_MAX);
    std::vector<int> parent(n, -1);

    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d > dist[v]) {
            continue;
        }
        for (auto [u, w] : graph[v]) {
            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                parent[u] = v;
                pq.push({dist[u], u});
            }
        }
    }
    return {dist, parent};
}

}