#include <iostream>
#include <string>
#include <vector>

void EnqueueCase(std::vector<std::pair<int, int>>& input_stack,
                 int new_element) {
  int minimum = input_stack.empty()
                    ? new_element
                    : std::min(new_element, input_stack.back().second);
  input_stack.emplace_back(new_element, minimum);
  std::cout << "ok\n";
}
void DequeueAndFrontCase(std::vector<std::pair<int, int>>& input_stack,
                         std::vector<std::pair<int, int>>& output_stack,
                         bool is_dequeue) {
  if (input_stack.empty() && output_stack.empty()) {
    std::cout << "error\n";
    return;
  }
  if (output_stack.empty()) {
    while (!input_stack.empty()) {
      int element = input_stack.back().first;
      input_stack.pop_back();
      int minimum = output_stack.empty()
                        ? element
                        : std::min(element, output_stack.back().second);
      output_stack.emplace_back(element, minimum);
    }
  }
  std::cout << output_stack.back().first << '\n';
  if (is_dequeue) {
    output_stack.pop_back();
  }
}
void GetMin(std::vector<std::pair<int, int>>& input_stack,
            std::vector<std::pair<int, int>>& output_stack) {
  if (input_stack.empty() && output_stack.empty()) {
    std::cout << "error\n";
    return;
  }
  if (input_stack.empty() || output_stack.empty()) {
    std::cout << (input_stack.empty() ? output_stack.back().second
                                      : input_stack.back().second)
              << '\n';
  } else {
    std::cout << std::min(input_stack.back().second, output_stack.back().second)
              << '\n';
  }
}
void ClearCase(std::vector<std::pair<int, int>>& input_stack,
               std::vector<std::pair<int, int>>& output_stack) {
  input_stack.clear();
  output_stack.clear();
  std::cout << "ok\n";
}
void SizeCase(std::vector<std::pair<int, int>>& input_stack,
              std::vector<std::pair<int, int>>& output_stack) {
  std::cout << input_stack.size() + output_stack.size() << '\n';
}

void Actions(int requests_number, std::vector<std::pair<int, int>>& input_stack,
             std::vector<std::pair<int, int>>& output_stack) {
  for (int i = 0; i < requests_number; ++i) {
    std::string key_word;
    std::cin >> key_word;
    if (key_word == "enqueue") {
      int new_element;
      std::cin >> new_element;
      EnqueueCase(input_stack, new_element);
    } else if (key_word == "dequeue") {
      DequeueAndFrontCase(input_stack, output_stack, true);
    } else if (key_word == "front") {
      DequeueAndFrontCase(input_stack, output_stack, false);
    } else if (key_word == "size") {
      SizeCase(input_stack, output_stack);
    } else if (key_word == "clear") {
      ClearCase(input_stack, output_stack);
    } else if (key_word == "min") {
      GetMin(input_stack, output_stack);
    }
  }
}

int main() {
  std::vector<std::pair<int, int>> input_stack;
  std::vector<std::pair<int, int>> output_stack;
  int requests_number;
  std::cin >> requests_number;
  Actions(requests_number, input_stack, output_stack);
}