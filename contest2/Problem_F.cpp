#include <iostream>
#include <string>
#include <vector>

class Heap {
 private:
  std::vector<std::pair<long long, int>> heap_;
  std::vector<int> sup_heap_;
  int heap_length_ = 0;

  void SiftDown() {
    int parent = 0;
    while (2 * parent + 1 < heap_length_) {
      int left_child = 2 * parent + 1;
      int right_child = 2 * parent + 2;
      int child = left_child;
      if (right_child < heap_length_ &&
          heap_[right_child] < heap_[left_child]) {
        child = right_child;
      }
      if (heap_[child] < heap_[parent]) {
        std::swap(sup_heap_[heap_[child].second],
                  sup_heap_[heap_[parent].second]);
        std::swap(heap_[child], heap_[parent]);
        parent = child;
      } else {
        break;
      }
    }
  }
  void SiftUp(int child) {
    while (child != 0) {
      if (heap_[child] < heap_[(child - 1) / 2]) {
        std::swap(sup_heap_[heap_[child].second],
                  sup_heap_[heap_[(child - 1) / 2].second]);
        std::swap(heap_[child], heap_[(child - 1) / 2]);
        child = (child - 1) / 2;
      } else {
        break;
      }
    }
  }

 public:
  explicit Heap(int heap_length) { sup_heap_.resize(heap_length + 1, -1); }
  void ExtractMin() {
    sup_heap_[heap_[heap_length_ - 1].second] = sup_heap_[heap_[0].second];
    sup_heap_[heap_[0].second] = -1;
    std::swap(heap_[0], heap_[heap_length_ - 1]);

    heap_.pop_back();
    heap_length_--;
    SiftDown();
  }
  void GetMin() { std::cout << heap_[0].first << '\n'; }
  void Insert(long long new_element, int request) {
    heap_.emplace_back(new_element, request);
    sup_heap_[request] = heap_length_;
    heap_length_++;
    SiftUp(heap_length_ - 1);
  }
  void DecreaseKey(long long value, int delta) {
    heap_[sup_heap_[value]].first -= delta;
    SiftUp(sup_heap_[value]);
  }
};

void Actions(Heap& heap, int request, std::string& key_word) {
  if (key_word == "insert") {
    long long new_element;
    std::cin >> new_element;
    heap.Insert(new_element, request);
  } else if (key_word == "getMin") {
    heap.GetMin();
  } else if (key_word == "extractMin") {
    heap.ExtractMin();
  } else {
    long long value;
    int delta;
    std::cin >> value >> delta;
    heap.DecreaseKey(value, delta);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int heap_length;
  std::cin >> heap_length;
  Heap heap(heap_length);
  for (int i = 1; i < heap_length + 1; ++i) {
    std::string key_word;
    std::cin >> key_word;
    Actions(heap, i, key_word);
  }
}