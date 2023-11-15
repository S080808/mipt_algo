#include <iostream>
#include <vector>

class GoblinQueue {
 private:
  int array_size_;
  std::vector<int> goblins_;

 public:
  void PushBack(int& goblin) { goblins_.push_back(goblin); }

  void PrioritizedPushBack(int& goblin) {
    array_size_ = static_cast<int>(goblins_.size());
    goblins_.insert(goblins_.begin() + (array_size_ + 1) / 2, goblin);
  }

  int Front() { return goblins_.front(); }

  void PopFront() { goblins_.erase(goblins_.begin()); }
};

void Actions(GoblinQueue goblin_queue, int requests_number) {
  for (int i = 0; i < requests_number; ++i) {
    char sign;
    std::cin >> sign;
    if (sign == '-') {
      std::cout << goblin_queue.Front() << '\n';
      goblin_queue.PopFront();
    } else {
      int goblin;
      std::cin >> goblin;
      sign == '+' ? goblin_queue.PushBack(goblin)
                  : goblin_queue.PrioritizedPushBack(goblin);
    }
  }
}

int main() {
  int requests_number;
  std::cin >> requests_number;

  GoblinQueue goblin_queue;
  Actions(goblin_queue, requests_number);
}