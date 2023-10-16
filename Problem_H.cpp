#include <iostream>
#include <vector>

void BubbleSort(std::vector<int>& array, auto left_border, auto right_border) {
  for (auto i = right_border; i > left_border; --i) {
    for (auto j = left_border; j < i; ++j) {
      if (array[j] > array[j + 1]) {
        std::swap(array[j], array[j + 1]);
      }
    }
  }
}

int MedianOfMedians(std::vector<int>& array, int left_border,
                    int right_border) {
  int array_length = right_border - left_border + 1;
  std::vector<int> medians_array;
  for (auto i = left_border; i + 4 <= right_border; i += 5) {
    BubbleSort(array, i, i + 4);
    medians_array.push_back(array[i + 2]);
  }
  if (array_length % 5 > 0) {
    BubbleSort(array, left_border + (array_length / 5) * 5, right_border);
    medians_array.push_back(array[left_border + (array_length / 5) * 5 +
                                  (array_length % 5 - 1) / 2]);
  }

  int median_array_length = static_cast<int>(medians_array.size());
  if (median_array_length == 1) {
    return medians_array[0];
  }
  return MedianOfMedians(medians_array, 0, median_array_length - 1);
}

int Partition(std::vector<int>& array, int left_border, int right_border,
              int& left_length, int pivot) {
  int middle_length = 0;
  for (int i = left_border; i <= right_border; ++i) {
    if (array[i] < pivot) {
      std::swap(array[i], array[left_border + left_length]);
      if (middle_length > 0) {
        std::swap(array[i], array[left_border + left_length + middle_length]);
      }
      left_length++;
    } else if (array[i] == pivot) {
      std::swap(array[i], array[left_border + left_length + middle_length]);
      middle_length++;
    }
  }
  return middle_length;
}

int DeterminedQuickSelect(std::vector<int>& array, int kth_statistics,
                          int left_border, int right_border) {
  if (right_border <= left_border) {
    return array[left_border];
  }

  int pivot = MedianOfMedians(array, left_border, right_border);
  int left_length = 0;
  int middle_length =
      Partition(array, left_border, right_border, left_length, pivot);

  if (left_border + left_length >= kth_statistics) {
    return DeterminedQuickSelect(array, kth_statistics, left_border,
                                 left_border + left_length - 1);
  }
  if (left_border + left_length + middle_length >= kth_statistics) {
    return array[left_length + left_border];
  }
  return DeterminedQuickSelect(array, kth_statistics,
                               left_border + left_length + middle_length,
                               right_border);
}

void DeterminedQuickSort(std::vector<int>& array, int left_border,
                         int right_border) {
  int array_length = right_border - left_border + 1;
  if (array_length < 2) {
    return;
  }
  int pivot = DeterminedQuickSelect(array, left_border + array_length / 2,
                                    left_border, right_border);
  int left_length = 0;
  int middle_length =
      Partition(array, left_border, right_border, left_length, pivot);
  DeterminedQuickSort(array, left_border, left_border + left_length - 1);
  DeterminedQuickSort(array, left_border + left_length + middle_length,
                      right_border);
}

int main() {
  int array_length;
  std::cin >> array_length;
  std::vector<int> array(array_length);
  for (int i = 0; i < array_length; ++i) {
    std::cin >> array[i];
  }
  DeterminedQuickSort(array, 0, array_length - 1);
  for (int i = 0; i < array_length; ++i) {
    std::cout << array[i] << " ";
  }
}