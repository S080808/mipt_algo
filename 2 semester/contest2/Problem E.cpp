#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

class Graph {
 private:
  int vertices_;
  std::vector<std::vector<std::pair<int, int>>> adjacency_list_;
  std::vector<int> bridges_;
  std::map<std::pair<int, int>, int> edge_count_;
  std::vector<bool> visited_;
  std::vector<int> tin_, low_;
  int time_;

  void DFS(int vertex, int parent) {
    visited_[vertex] = true;
    tin_[vertex] = low_[vertex] = time_++;
    for (auto& edge : adjacency_list_[vertex]) {
      int to_vertex = edge.first;
      int edge_idx = edge.second;
      if (to_vertex == parent) {
        continue;
      }
      if (visited_[to_vertex]) {
        low_[vertex] = std::min(low_[vertex], tin_[to_vertex]);
      } else {
        DFS(to_vertex, vertex);
        low_[vertex] = std::min(low_[vertex], low_[to_vertex]);
        if (low_[to_vertex] > tin_[vertex] &&
            edge_count_[{std::min(vertex, to_vertex),
                         std::max(vertex, to_vertex)}] == 1) {
          bridges_.push_back(edge_idx);
        }
      }
    }
  }

 public:
  explicit Graph(int n) : vertices_(n), adjacency_list_(n), time_(0) {}

  void AddEdge(int from_vertex, int to_vertex, int index) {
    adjacency_list_[from_vertex].emplace_back(to_vertex, index);
    adjacency_list_[to_vertex].emplace_back(from_vertex, index);
    edge_count_[{std::min(from_vertex, to_vertex),
                 std::max(from_vertex, to_vertex)}]++;
  }

  void FindBridges() {
    visited_.assign(vertices_, false);
    tin_.assign(vertices_, -1);
    low_.assign(vertices_, -1);
    bridges_.clear();

    for (int i = 0; i < vertices_; ++i) {
      if (!visited_[i]) {
        DFS(i, -1);
      }
    }
  }

  void PrintBridges() {
    std::cout << bridges_.size() << '\n';
    std::sort(bridges_.begin(), bridges_.end());
    for (int idx : bridges_) {
      std::cout << idx + 1 << " ";
    }
  }
};

int main() {
  int number_of_vertices;
  int number_of_edges;
  std::cin >> number_of_vertices >> number_of_edges;
  Graph graph(number_of_vertices);

  for (int i = 0; i < number_of_edges; ++i) {
    int from_vertex;
    int to_vertex;
    std::cin >> from_vertex >> to_vertex;
    graph.AddEdge(from_vertex - 1, to_vertex - 1, i);
  }

  graph.FindBridges();
  graph.PrintBridges();
}