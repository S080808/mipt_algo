#include <iostream>
#include <string>
#include <vector>

class Deque {
 public:
  void EnqueueCase(int new_element) {
    int minimum = input_stack_.empty()
                      ? new_element
                      : std::min(new_element, input_stack_.back().second);
    input_stack_.emplace_back(new_element, minimum);
    std::cout << "ok\n";
  }

  void DequeueAndFrontCase(bool is_dequeue) {
    if (input_stack_.empty() && output_stack_.empty()) {
      std::cout << "error\n";
      return;
    }
    if (output_stack_.empty()) {
      while (!input_stack_.empty()) {
        int element = input_stack_.back().first;
        input_stack_.pop_back();
        int minimum = output_stack_.empty()
                          ? element
                          : std::min(element, output_stack_.back().second);
        output_stack_.emplace_back(element, minimum);
      }
    }
    std::cout << output_stack_.back().first << '\n';
    if (is_dequeue) {
      output_stack_.pop_back();
    }
  }
  void GetMin() {
    if (input_stack_.empty() && output_stack_.empty()) {
      std::cout << "error\n";
      return;
    }
    if (input_stack_.empty() || output_stack_.empty()) {
      std::cout << (input_stack_.empty() ? output_stack_.back().second
                                         : input_stack_.back().second)
                << '\n';
    } else {
      std::cout << std::min(input_stack_.back().second,
                            output_stack_.back().second)
                << '\n';
    }
  }
  void ClearCase() {
    input_stack_.clear();
    output_stack_.clear();
    std::cout << "ok\n";
  }

  void SizeCase() {
    std::cout << input_stack_.size() + output_stack_.size() << '\n';
  }

 private:
  std::vector<std::pair<int, int>> input_stack_;
  std::vector<std::pair<int, int>> output_stack_;
};

void Actions(int requests_number) {
  Deque deque;
  for (int i = 0; i < requests_number; ++i) {
    std::string key_word;
    std::cin >> key_word;
    if (key_word == "enqueue") {
      int new_element;
      std::cin >> new_element;
      deque.EnqueueCase(new_element);
    } else if (key_word == "dequeue") {
      deque.DequeueAndFrontCase(true);
    } else if (key_word == "front") {
      deque.DequeueAndFrontCase(false);
    } else if (key_word == "size") {
      deque.SizeCase();
    } else if (key_word == "clear") {
      deque.ClearCase();
    } else if (key_word == "min") {
      deque.GetMin();
    }
  }
}

int main() {
  int requests_number;
  std::cin >> requests_number;
  Actions(requests_number);
}