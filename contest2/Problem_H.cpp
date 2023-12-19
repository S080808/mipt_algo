#include <iostream>
#include <string>
#include <vector>

class Heap {
 public:
  void ExtractMin() {
    if (heap_length_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << min_heap_[0].first << '\n';
    size_t tmp = static_cast<size_t>(min_heap_[0].second);
    SwapMin(0, heap_length_ - 1);
    SwapMax(tmp, heap_length_ - 1);
    min_heap_.pop_back();
    max_heap_.pop_back();
    heap_length_--;
    MinSiftDown(0);
    if (tmp < heap_length_) {
      MaxSiftUp(tmp);
      MaxSiftDown(tmp);
    }
  }

  void ExtractMax() {
    if (heap_length_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << max_heap_[0].first << '\n';
    size_t tmp = static_cast<size_t>(max_heap_[0].second);
    SwapMax(0, heap_length_ - 1);
    SwapMin(tmp, heap_length_ - 1);
    max_heap_.pop_back();
    min_heap_.pop_back();
    heap_length_--;
    MaxSiftDown(0);
    if (tmp < heap_length_) {
      MinSiftUp(tmp);
      MinSiftDown(tmp);
    }
  }

  void Clear() {
    max_heap_.clear();
    min_heap_.clear();
    heap_length_ = 0;
  }
  void Size() const { std::cout << heap_length_ << '\n'; }

  void GetMin() {
    if (heap_length_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << min_heap_[0].first << '\n';
  }
  void GetMax() {
    if (heap_length_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << max_heap_[0].first << '\n';
  }
  void Insert(int new_element) {
    min_heap_.emplace_back(new_element, heap_length_);
    max_heap_.emplace_back(new_element, heap_length_);
    heap_length_++;
    MinSiftUp(heap_length_ - 1);
    MaxSiftUp(heap_length_ - 1);
  }

 private:
  void MinSiftDown(size_t parent) {
    while (2 * parent + 1 < heap_length_) {
      size_t left_child = 2 * parent + 1;
      size_t right_child = 2 * parent + 2;
      size_t child = left_child;
      if (right_child < heap_length_ &&
          min_heap_[right_child] < min_heap_[left_child]) {
        child = right_child;
      }
      if (min_heap_[child] < min_heap_[parent]) {
        SwapMin(parent, child);
        parent = child;
      } else {
        break;
      }
    }
  }
  void MaxSiftDown(size_t parent) {
    while (2 * parent + 1 < heap_length_) {
      size_t left_child = 2 * parent + 1;
      size_t right_child = 2 * parent + 2;
      size_t child = left_child;
      if (right_child < heap_length_ &&
          max_heap_[right_child] > max_heap_[left_child]) {
        child = right_child;
      }
      if (max_heap_[child] > max_heap_[parent]) {
        SwapMax(parent, child);
        parent = child;
      } else {
        break;
      }
    }
  }
  void MinSiftUp(size_t child) {
    while (child != 0) {
      if (min_heap_[child] < min_heap_[(child - 1) / 2]) {
        SwapMin(child, (child - 1) / 2);
        child = (child - 1) / 2;
      } else {
        break;
      }
    }
  }
  void MaxSiftUp(size_t child) {
    while (child != 0) {
      if (max_heap_[child] > max_heap_[(child - 1) / 2]) {
        SwapMax(child, (child - 1) / 2);
        child = (child - 1) / 2;
      } else {
        break;
      }
    }
  }

  void SwapMin(size_t ind1, size_t ind2) {
    std::swap(min_heap_[ind1], min_heap_[ind2]);
    std::swap(max_heap_[min_heap_[ind1].second].second,
              max_heap_[min_heap_[ind2].second].second);
  }

  void SwapMax(size_t ind1, size_t ind2) {
    std::swap(min_heap_[max_heap_[ind1].second].second,
              min_heap_[max_heap_[ind2].second].second);
    std::swap(max_heap_[ind1], max_heap_[ind2]);
  }
  std::vector<std::pair<int, int>> min_heap_;
  std::vector<std::pair<int, int>> max_heap_;
  size_t heap_length_ = 0;
};

void Actions(Heap& heap, std::string& key_word) {
  if (key_word == "insert") {
    int new_element;
    std::cin >> new_element;
    std::cout << "ok\n";
    heap.Insert(new_element);
  } else if (key_word == "get_max") {
    heap.GetMax();
  } else if (key_word == "get_min") {
    heap.GetMin();
  } else if (key_word == "extract_min") {
    heap.ExtractMin();
  } else if (key_word == "extract_max") {
    heap.ExtractMax();
  } else if (key_word == "clear") {
    heap.Clear();
    std::cout << "ok\n";
  } else if (key_word == "size") {
    heap.Size();
  }
}

int main() {
  int request_number;
  std::cin >> request_number;
  Heap heap;
  for (int i = 0; i < request_number; ++i) {
    std::string key_word;
    std::cin >> key_word;
    Actions(heap, key_word);
  }
}