#include <iostream>
#include <queue>
#include <vector>

const long long cKInf = 1e+18;

int main() {
  int NNN;
  int UUU;
  int DDD;
  int III;
  int JJJ;
  int LLL;
  std::cin >> NNN >> UUU >> DDD >> III >> JJJ >> LLL;

  std::vector<std::vector<int>> teleports(LLL);
  for (int i = 0; i < LLL; ++i) {
    int KKK;
    std::cin >> KKK;
    teleports[i].resize(KKK);
    for (int j = 0; j < KKK; ++j) {
      std::cin >> teleports[i][j];
    }
  }

  std::vector<long long> min_cost(NNN + 1, cKInf);
  std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> queue;

  min_cost[1] = 0;
  queue.emplace(0, 1);

  while (!queue.empty()) {
    auto top = queue.top();
    long long cost = top.first;
    int floor = top.second;
    queue.pop();

    if (cost > min_cost[floor]) {
      continue;
    }

    if (floor < NNN && cost + UUU < min_cost[floor + 1]) {
      min_cost[floor + 1] = cost + UUU;
      queue.emplace(min_cost[floor + 1], floor + 1);
    }

    if (floor > 1 && cost + DDD < min_cost[floor - 1]) {
      min_cost[floor - 1] = cost + DDD;
      queue.emplace(min_cost[floor - 1], floor - 1);
    }

    for (std::vector<int>& teleport : teleports) {
      auto it = std::lower_bound(teleport.begin(), teleport.end(), floor);
      if (it != teleport.end() && *it == floor) {
        for (int dest : teleport) {
          if (dest != floor && cost + III + JJJ < min_cost[dest]) {
            min_cost[dest] = cost + III + JJJ;
            queue.emplace(min_cost[dest], dest);
          }
        }
      }
    }
  }

  std::cout << min_cost[NNN];
}