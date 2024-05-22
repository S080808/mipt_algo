#include <iostream>
#include <vector>

class Graph {
 private:
  int mmm_, nnn_;
  std::vector<std::vector<int>> adj_;
  std::vector<int> match_left_;
  std::vector<int> match_right_;

  void Read() {
    adj_.resize(mmm_ + 1);
    for (int i = 0; i < mmm_; ++i) {
      int kkk;
      std::cin >> kkk;
      adj_[i + 1].resize(kkk);
      for (int j = 0; j < kkk; ++j) {
        std::cin >> adj_[i + 1][j];
      }
    }
    match_left_.resize(mmm_ + 1);
    for (int i = 1; i <= mmm_; ++i) {
      std::cin >> match_left_[i];
      if (match_left_[i] > 0) {
        if ((int)match_right_.size() <= match_left_[i]) {
          match_right_.resize(match_left_[i] + 1);
        }
        match_right_[match_left_[i]] = i;
      }
    }
  }

  void MinimumVertexCover(std::vector<int>& cover_left,
                          std::vector<int>& cover_right) {
    std::vector<bool> visited_left(mmm_ + 1, false);
    std::vector<bool> visited_right(nnn_ + 1, false);

    for (int i = 0; i < mmm_; ++i) {
      if (match_left_[i + 1] == 0) {
        Dfs(i + 1, visited_left, visited_right);
      }
    }

    for (int i = 0; i < mmm_; ++i) {
      if (!visited_left[i + 1]) {
        cover_left.push_back(i + 1);
      }
    }
    for (int j = 0; j < nnn_; ++j) {
      if (visited_right[j + 1]) {
        cover_right.push_back(j + 1);
      }
    }
  }

  void Dfs(int to, std::vector<bool>& visited_left,
           std::vector<bool>& visited_right) {
    visited_left[to] = true;
    for (int v : adj_[to]) {
      if (!visited_right[v] &&
          ((int)match_right_.size() <= v || match_right_[v] != to)) {
        visited_right[v] = true;
        if ((match_right_[v] != 0) && !visited_left[match_right_[v]]) {
          Dfs(match_right_[v], visited_left, visited_right);
        }
      }
    }
  }

 public:
  void Solve() {
    std::cin >> mmm_ >> nnn_;
    Read();

    std::vector<int> cover_left;
    std::vector<int> cover_right;
    MinimumVertexCover(cover_left, cover_right);

    std::cout << cover_left.size() + cover_right.size() << '\n';
    std::cout << cover_left.size();
    for (int v : cover_left) {
      std::cout << " " << v;
    }
    std::cout << '\n';
    std::cout << cover_right.size();
    for (int v : cover_right) {
      std::cout << " " << v;
    }
  }
};

int main() {
  Graph graph;
  graph.Solve();
}