#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

const int cKMax = std::numeric_limits<int>::max();

class MinCostMaxFlow {
public:
  struct Edge {
    int from;
    int to;
    int capacity;
    int cost;
    int flow;
    Edge(int from, int to, int capacity, int cost, int flow)
      : from(from), to(to), capacity(capacity), cost(cost), flow(flow) {}
  };

  explicit MinCostMaxFlow(int number_of_cities)
    : number_of_cities_(number_of_cities),
    graph_(number_of_cities_),
    potential_(number_of_cities_, 0),
    distance_(number_of_cities_, 0),
    parent_edge_(number_of_cities_, -1),
    in_queue_(number_of_cities_, false) {}

  void AddRoute(int from, int to, int capacity, int cost) {
    graph_[from].push_back((int)edges_.size());
    edges_.emplace_back(from, to, capacity, cost, 0);
    graph_[to].push_back((int)edges_.size());
    edges_.emplace_back(to, from, 0, -cost, 0);
  }

  int64_t FindMinCostMaxFlow(int source, int sink) {
    int64_t min_cost = 0;

    while (ShortestPath(source, sink)) {
      int flow = cKMax;
      for (int v = sink; v != source; v = edges_[parent_edge_[v]].from) {
        flow = std::min(flow, edges_[parent_edge_[v]].capacity -
          edges_[parent_edge_[v]].flow);
      }

      for (int v = sink; v != source; v = edges_[parent_edge_[v]].from) {
        edges_[parent_edge_[v]].flow += flow;
        edges_[parent_edge_[v] ^ 1].flow -= flow;
        min_cost += static_cast<int64_t>(flow) * edges_[parent_edge_[v]].cost;
      }
    }

    return min_cost;
  }

private:
  bool ShortestPath(int source, int sink) {
    std::fill(distance_.begin(), distance_.end(), cKMax);
    std::fill(in_queue_.begin(), in_queue_.end(), false);
    std::queue<int> queue;

    distance_[source] = 0;
    queue.push(source);
    in_queue_[source] = true;

    while (!queue.empty()) {
      int u = queue.front();
      queue.pop();
      in_queue_[u] = false;

      for (int edge_index : graph_[u]) {
        Edge& edge = edges_[edge_index];
        if (edge.flow < edge.capacity &&
          distance_[u] + edge.cost < distance_[edge.to]) {
          distance_[edge.to] = distance_[u] + edge.cost;
          parent_edge_[edge.to] = edge_index;
          if (!in_queue_[edge.to]) {
            queue.push(edge.to);
            in_queue_[edge.to] = true;
          }
        }
      }
    }

    return distance_[sink] != cKMax;
  }

  int number_of_cities_;
  std::vector<std::vector<int>> graph_;
  std::vector<Edge> edges_;
  std::vector<int> potential_;
  std::vector<int> distance_;
  std::vector<int> parent_edge_;
  std::vector<bool> in_queue_;
};

int main() {
  int number_of_cities;
  int number_of_routes;
  std::cin >> number_of_cities >> number_of_routes;

  MinCostMaxFlow graph(number_of_cities);

  for (int i = 0; i < number_of_routes; ++i) {
    int from;
    int to;
    int capacity;
    int cost;
    std::cin >> from >> to >> capacity >> cost;
    graph.AddRoute(from - 1, to - 1, capacity, cost);
  }

  int64_t result = graph.FindMinCostMaxFlow(0, number_of_cities - 1);
  std::cout << result;
}