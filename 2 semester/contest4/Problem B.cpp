#include <iostream>
#include <queue>
#include <vector>

const int cKMax = 1e+9;
typedef std::pair<int, int> Pair;

class Graph {
 private:
  int size_;
  std::vector<std::vector<Pair>> adj_;

 public:
  Graph(int size) : size_(size), adj_(size) {}

  void AddEdge(int from, int to, int weight) {
    adj_[from].emplace_back(weight, to);
    adj_[to].emplace_back(weight, from);
  }

  void PrimMST() {
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
    int start = 0;

    std::vector<int> dp(size_, cKMax);
    std::vector<bool> mst(size_, false);

    pq.emplace(0, start);
    dp[start] = 0;

    int ans = 0;

    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();

      if (!mst[u]) {
        mst[u] = true;
        ans += dp[u];

        for (Pair& pair : adj_[u]) {
          int v = pair.second;
          int weight = pair.first;

          if (!mst[v] && dp[v] > weight) {
            dp[v] = weight;
            pq.emplace(dp[v], v);
          }
        }
      }
    }

    std::cout << ans;
  }
};

int main() {
  int number_of_vertices;
  int number_of_edges;
  std::cin >> number_of_vertices >> number_of_edges;
  Graph g(number_of_vertices);
  for (int i = 0; i < number_of_edges; i++) {
    int from;
    int to;
    int weight;
    std::cin >> from >> to >> weight;
    g.AddEdge(from - 1, to - 1, weight);
  }
  g.PrimMST();
}