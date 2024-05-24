#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

class OrientedGraph {
 private:
  std::vector<std::vector<int>> adjacency_list_;
  std::vector<std::vector<int>> transposed_adjacency_list_;
  std::vector<int> scc_;
  std::stack<int> finish_order_;
  std::vector<bool> used_;
  int scc_count_;

  void DFSFirstPass(int vertex) {
    used_[vertex] = true;
    for (int next_vertex : adjacency_list_[vertex]) {
      if (!used_[next_vertex]) {
        DFSFirstPass(next_vertex);
      }
    }
    finish_order_.push(vertex);
  }

  void DFSSecondPass(int vertex, int current_scc) {
    used_[vertex] = true;
    scc_[vertex] = current_scc;
    for (int next_vertex : transposed_adjacency_list_[vertex]) {
      if (!used_[next_vertex]) {
        DFSSecondPass(next_vertex, current_scc);
      }
    }
  }

 public:
  explicit OrientedGraph(int size)
      : adjacency_list_(size + 1),
        transposed_adjacency_list_(size + 1),
        scc_(size + 1, -1),
        used_(size + 1, false),
        scc_count_(0) {}

  void AddEdge(int from_vertex, int to_vertex) {
    adjacency_list_[from_vertex].push_back(to_vertex);
    transposed_adjacency_list_[to_vertex].push_back(from_vertex);
  }

  void FindSCCs() {
    for (int vertex = 1; vertex < static_cast<int>(adjacency_list_.size());
         ++vertex) {
      if (!used_[vertex]) {
        DFSFirstPass(vertex);
      }
    }

    std::fill(used_.begin(), used_.end(), false);

    while (!finish_order_.empty()) {
      int vertex = finish_order_.top();
      finish_order_.pop();
      if (!used_[vertex]) {
        DFSSecondPass(vertex, scc_count_++);
      }
    }
  }

  void PrintSCCs() {
    std::cout << scc_count_ << '\n';
    for (size_t i = 1; i < scc_.size(); ++i) {
      std::cout << scc_[i] + 1 << " ";
    }
  }
};

int main() {
  int number_of_vertices;
  int number_of_edges;
  std::cin >> number_of_vertices >> number_of_edges;
  OrientedGraph graph(number_of_vertices);

  for (int i = 0; i < number_of_edges; ++i) {
    int from_vertex;
    int to_vertex;
    std::cin >> from_vertex >> to_vertex;
    graph.AddEdge(from_vertex, to_vertex);
  }

  graph.FindSCCs();
  graph.PrintSCCs();
}