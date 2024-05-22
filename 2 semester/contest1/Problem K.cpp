#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int number_of_orders;
  int resources_limit;
  std::cin >> number_of_orders >> resources_limit;

  std::vector<int> resources(number_of_orders + 1);
  std::vector<int> awards(number_of_orders + 1);

  for (int i = 1; i <= number_of_orders; ++i) {
    std::cin >> resources[i];
  }

  for (int i = 1; i <= number_of_orders; ++i) {
    std::cin >> awards[i];
  }

  std::vector<std::vector<int>> dp(number_of_orders + 1,
                                   std::vector<int>(resources_limit + 1, 0));
  for (int i = 1; i < number_of_orders + 1; ++i) {
    for (int j = 1; j < resources_limit + 1; ++j) {
      if (j >= resources[i]) {
        dp[i][j] =
            std::max(dp[i - 1][j], dp[i - 1][j - resources[i]] + awards[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  std::vector<int> answer;

  int limit = resources_limit;
  for (int i = number_of_orders; i > 0; --i) {
    if (dp[i][limit] != dp[i - 1][limit]) {
      answer.push_back(i);
      limit -= resources[i];
    }
  }

  std::reverse(answer.begin(), answer.end());
  for (auto order : answer) {
    std::cout << order << "\n";
  }
}