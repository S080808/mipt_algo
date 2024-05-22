#include <cmath>
#include <iostream>
#include <vector>
const int kBits = 8;
const int kNumbersInByte = 256;

void RadixSort(std::vector<long long>& array, int array_length) {
  long long max_element = 0;
  for (int i = 0; i < array_length; ++i) {
    max_element = std::max(max_element, array[i]);
  }
  for (int shift = 0; max_element >> shift > 0; shift += kBits) {
    std::vector<long long> copy_array;
    std::vector<std::vector<long long> > byte_values(kNumbersInByte);
    for (int i = 0; i < array_length; ++i) {
      byte_values[(array[i] >> shift) % kNumbersInByte].push_back(array[i]);
    }
    for (size_t byte = 0; byte < byte_values.size(); ++byte) {
      for (size_t number = 0; number < byte_values[byte].size(); ++number) {
        copy_array.push_back(byte_values[byte][number]);
      }
    }
    array = copy_array;
  }
}

int main() {
  int array_length;
  std::cin >> array_length;

  std::vector<long long> numbers_array(array_length);
  for (int i = 0; i < array_length; ++i) {
    std::cin >> numbers_array[i];
  }
  RadixSort(numbers_array, array_length);
  for (int i = 0; i < array_length; ++i) {
    std::cout << numbers_array[i] << '\n';
  }
}