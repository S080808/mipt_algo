#include <algorithm>
#include <iostream>
#include <vector>

const int cKinf = 100000;

struct Edge {
  int from_vertex;
  int to_vertex;
  int weight;
  Edge(int from, int to, int weight)
      : from_vertex(from), to_vertex(to), weight(weight) {}
};

bool FindNegativeCycle(int start_vertex, const std::vector<Edge>& edges,
                       int number_of_vertices, std::vector<int>& cycle) {
  std::vector<int> dist(number_of_vertices, cKinf);
  std::vector<int> parent(number_of_vertices, -1);
  dist[start_vertex] = 0;
  int last_updated;

  for (int i = 0; i < number_of_vertices; ++i) {
    last_updated = -1;
    for (const Edge& edge : edges) {
      if (dist[edge.from_vertex] < cKinf &&
          dist[edge.to_vertex] > dist[edge.from_vertex] + edge.weight) {
        dist[edge.to_vertex] = dist[edge.from_vertex] + edge.weight;
        parent[edge.to_vertex] = edge.from_vertex;
        last_updated = edge.to_vertex;
      }
    }
  }

  if (last_updated != -1) {
    int cycle_start = last_updated;
    for (int i = 0; i < number_of_vertices; ++i) {
      cycle_start = parent[cycle_start];
    }

    for (int cur = cycle_start;; cur = parent[cur]) {
      cycle.push_back(cur);
      if (cur == cycle_start && cycle.size() > 1) {
        break;
      }
    }
    std::reverse(cycle.begin(), cycle.end());
    return true;
  }
  return false;
}

int main() {
  int number_of_vertices;
  std::cin >> number_of_vertices;

  std::vector<Edge> edges;

  for (int from_vertex = 0; from_vertex < number_of_vertices; ++from_vertex) {
    for (int to_vertex = 0; to_vertex < number_of_vertices; ++to_vertex) {
      int weight;
      std::cin >> weight;
      if (weight != cKinf) {
        edges.emplace_back(from_vertex, to_vertex, weight);
      }
    }
  }

  bool cycle_found = false;
  std::vector<int> cycle;

  for (int start = 0; start < number_of_vertices; ++start) {
    if (FindNegativeCycle(start, edges, number_of_vertices, cycle)) {
      cycle_found = true;
      break;
    }
  }

  if (!cycle_found) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    std::cout << cycle.size() << '\n';
    for (int vertex : cycle) {
      std::cout << vertex + 1 << " ";
    }
    std::cout << '\n';
  }

  return 0;
}