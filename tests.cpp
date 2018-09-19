
/*!
 * \file
 * \brief This file contains tests for the function squareEquationSolver
 * \details Class Tester can be used as a handler for every boolean test function.
 * It reports whether program works correctly on the test or not and catches exceptions
 */

#include <iostream>
#include <vector>
#include <algorithm>

class Tester {
 private:
  void test(bool (*foo)(), size_t test_id = 1, const std::string& title = "") {
    std::cout << "Test #" << test_id << ": '" << title << "'\n";
    try {
      bool passed = foo();

      std::cout << "Status: ";
      if (passed) {
        std::cout << "passed\n";
      } else {
        std::cout << "failed\n";
      }
    } catch (std::exception&) {
      std::cerr << "!!! exception was caught\n";
      std::cout << "Status: failed\n";
    }
    std::cout << '\n';
  }

  std::vector<std::pair<bool(*)(), std::string>> functions_;

 public:
  template <typename P, typename... Args>
  Tester(const P& function, const Args&... rest):
    Tester(rest...) {
    functions_.push_back(function);
  }

  Tester() {}

  void start() {
    std::reverse(functions_.begin(), functions_.end());
    for (size_t function_id = 0; function_id < functions_.size(); ++function_id) {
      test(functions_[function_id].first, function_id + 1, functions_[function_id].second);
    }
  }
};


int main() {
  Tester tester;

  tester.start();
  return 0;
}
