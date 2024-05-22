#include <iostream>
#include <vector>

const int kMod = 10000000 + 4321;
const int k1 = 123;
const int k2 = 45;

void BubbleSort(auto left_border, auto right_border) {
  for (auto i = right_border; i > left_border; --i) {
    for (auto j = left_border; j < i; ++j) {
      if (*j > *(j + 1)) {
        std::swap(*j, *(j + 1));
      }
    }
  }
}

std::vector<int> GeneratorOfArray(int a_array_length, int a_first_element,
                                  int a_second_element) {
  std::vector<int> array(a_array_length);
  array[0] = a_first_element;
  array[1] = a_second_element;
  for (int i = 2; i < a_array_length; ++i) {
    array[i] = (array[i - 1] * k1 + array[i - 2] * k2) % kMod;
  }
  return array;
}

int MedianOfMedians(std::vector<int>& sub_array, auto left_border,
                    auto right_border) {
  int sub_array_length = sub_array[0];
  sub_array_length = right_border - left_border + 1;
  std::vector<int> medians_array;
  for (auto i = left_border; i + 4 <= right_border; i += 5) {
    BubbleSort(i, i + 4);
    medians_array.push_back(*(i + 2));
  }
  if (sub_array_length % 5 > 0) {
    BubbleSort(left_border + (sub_array_length / 5) * 5, right_border);
    medians_array.push_back(*(left_border + (sub_array_length / 5) * 5 +
                              (sub_array_length % 5 - 1) / 2));
  }

  int median_array_length = static_cast<int>(medians_array.size());
  if (median_array_length == 1) {
    return medians_array[0];
  }
  return MedianOfMedians(medians_array, medians_array.begin(),
                         medians_array.begin() + median_array_length - 1);
}

void Partition(auto left_border, auto right_border, int& left_length,
               int& middle_length, int pivot) {
  for (auto i = left_border; i <= right_border; ++i) {
    if (*i < pivot) {
      std::swap(*i, *(left_border + left_length));
      if (middle_length > 0) {
        std::swap(*i, *(left_border + left_length + middle_length));
      }
      left_length++;
    } else if (*i == pivot) {
      std::swap(*i, *(left_border + left_length + middle_length));
      middle_length++;
    }
  }
}

int DeterminedQuickSelect(std::vector<int>& a_array, int kth_statistics,
                          auto left_border, auto right_border) {
  if (right_border == left_border) {
    return *left_border;
  }

  int left_length = 0;
  int middle_length = 0;

  int pivot = MedianOfMedians(a_array, left_border, right_border);
  Partition(left_border, right_border, left_length, middle_length, pivot);

  if (left_border + left_length >= a_array.begin() + kth_statistics) {
    return DeterminedQuickSelect(a_array, kth_statistics, left_border,
                                 left_border + left_length - 1);
  }
  if (left_border + left_length + middle_length >=
      a_array.begin() + kth_statistics) {
    return *(left_length + left_border);
  }
  return DeterminedQuickSelect(a_array, kth_statistics,
                               left_border + left_length + middle_length,
                               right_border);
}

int main() {
  int a_array_length;
  std::cin >> a_array_length;
  int kth_statistics;
  std::cin >> kth_statistics;

  int a_first_element;
  int a_second_element;
  std::cin >> a_first_element >> a_second_element;

  std::vector<int> a_array =
      GeneratorOfArray(a_array_length, a_first_element, a_second_element);

  std::cout << DeterminedQuickSelect(a_array, kth_statistics, a_array.begin(),
                                     a_array.begin() + a_array_length - 1);
}