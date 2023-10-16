#include <iostream>
#include <vector>

int main() {
  int ingredients_number = 8;
  std::vector<int> ingredients = {2, 3, 4, 5, 2, 3, 5, 1};
  std::vector<int> stack_of_ingredients;
  int answer = 0;
  stack_of_ingredients.push_back(ingredients[0]);
  for (int ingredient = 1; ingredient < ingredients_number; ++ingredient) {
    int current_ingredient = ingredients[ingredient];
    if (current_ingredient > stack_of_ingredients.back()) {
      stack_of_ingredients.push_back(current_ingredient);
    }
    int counter = 1;
    while (!stack_of_ingredients.empty() && stack_of_ingredients.back() >= current_ingredient) {
      answer = std::max(answer, counter * stack_of_ingredients.back());
      stack_of_ingredients.pop_back();
    }
  }
  std::cout << answer;
}