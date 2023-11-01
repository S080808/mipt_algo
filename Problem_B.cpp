#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
const int kPrecision = 10;
void BuildingAnswer(int requests_number,
                    std::vector<std::pair<double, double>> requests_array,
                    std::vector<double>& prefix_product_log) {
  for (int i = 0; i < requests_number; ++i) {
    int left = requests_array[i].first;
    int right = requests_array[i].second;
    std::cout << std::fixed << std::setprecision(kPrecision);
    if (left > 0) {
      std::cout << exp(
          1.0 / (right - left + 1) *
              (prefix_product_log[right] - prefix_product_log[left - 1]));
      std::cout << std::endl;
    } else {
      std::cout << exp(1.0 / (right - left + 1) * prefix_product_log[right]);
      std::cout << std::endl;
    }
  }
}

std::vector<double> PreCount(int plants_number, std::vector<double>& loudness) {
  std::vector<double> prefix_product_log(plants_number);
  double log_of_product_of_loudness = 0;
  for (int i = 0; i < plants_number; ++i) {
    log_of_product_of_loudness += log(loudness[i]);
    prefix_product_log[i] = log_of_product_of_loudness;  // боимся переполнения
  }
  return prefix_product_log;
}

void MiddleNoise(int plants_number, std::vector<double>& loudness) {
  std::vector<double> prefix_product_log = PreCount(plants_number, loudness);

  int requests_number;
  std::cin >> requests_number;

  std::vector<std::pair<double, double>> requests_array(requests_number);
  for (int i = 0; i < requests_number; ++i) {
    std::cin >> requests_array[i].first >> requests_array[i].second;
  }
  BuildingAnswer(requests_number, requests_array, prefix_product_log);
}

int main() {
  int plants_number;
  std::cin >> plants_number;

  std::vector<double> loudness(plants_number);
  for (int i = 0; i < plants_number; ++i) {
    std::cin >> loudness[i];
  }
  MiddleNoise(plants_number, loudness);
}