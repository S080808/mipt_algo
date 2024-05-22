#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int nn;
  std::cin >> nn;
  std::vector<int> arr(nn);

  for (int i = 0; i < nn; ++i) {
    std::cin >> arr[i];
  }

  std::reverse(arr.begin(), arr.end());

  std::vector<int> dp;
  std::vector<int> prev(nn + 1);
  std::vector<int> pos(nn + 1);
  int ans = 0;

  for (int i = 0; i < nn; ++i) {
    auto iter = std::upper_bound(dp.begin(), dp.end(), arr[i]);
    auto ind = iter - dp.begin();

    if (iter == dp.end()) {
      dp.push_back(arr[i]);
    } else {
      *iter = arr[i];
    }

    pos[ind] = i;
    prev[i] = ind > 0 ? pos[ind - 1] : -1;

    if (ind == ans) {
      ++ans;
    }
  }

  std::cout << ans << '\n';
  for (int i = pos[ans - 1]; i >= 0; i = prev[i]) {
    std::cout << nn - i << " ";
  }
}