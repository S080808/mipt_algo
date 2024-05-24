#include <iostream>
#include <vector>
const int kInf = 1e+9;
const int kMaxOfPlanes = 20;

int main() {
  int number_of_floors;
  int number_of_planes;
  std::cin >> number_of_floors >> number_of_planes;

  number_of_planes = std::min(kMaxOfPlanes, number_of_planes);
  number_of_floors -= 1;

  if (number_of_floors == 0) {
    std::cout << 0;
    return 0;
  }
  if (number_of_floors > 0 && number_of_planes == 0) {
    std::cout << -1;
    return 0;
  }
  std::vector<std::vector<long long>> dp(
    number_of_floors + 1, std::vector<long long>(number_of_planes + 1, 0));

  for (int i = 1; i < number_of_floors + 1; ++i) {
    dp[i][1] = i;
    dp[i][0] = kInf;
  }
  for (int i = 1; i < number_of_planes + 1; ++i) {
    dp[1][i] = 1;
  }

  for (int i = 2; i < number_of_planes + 1; ++i) {
    for (int j = 2; j < number_of_floors + 1; ++j) {
      int ll = 1;
      int rr = j;

      while (rr - ll >= 2) {
        int mm = (ll + rr) / 2;
        if (dp[mm - 1][i - 1] >= dp[j - mm][i]) {
          rr = mm;
        }
        else {
          ll = mm;
        }
      }

      dp[j][i] = 1 + std::max(dp[j - rr][i], dp[rr - 1][i - 1]);
    }
  }

  std::cout << dp[number_of_floors][number_of_planes];
}