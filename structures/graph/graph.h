#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

enum class Color { kGray, kWhite, kBlack };

using IntGraph = std::vector<std::vector<int>>;

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

int DFS(IntGraph& graph) {
    return 1;
}