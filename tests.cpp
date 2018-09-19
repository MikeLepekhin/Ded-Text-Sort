
/*!
 * \file
 * \brief This file contains tests for the function squareEquationSolver
 * \details Class Tester can be used as a handler for every boolean test function.
 * It reports whether program works correctly on the test or not and catches exceptions
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "stdlib_utf16.h"

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

bool strcmpTest() {
  return strlen_utf16(u"some simple string\n") == 18;
}

bool strlen1Test() {
  return strlen_utf16(u"some simple string\n") == 18;
}

bool strlen2Test() {
  return strlen_utf16(u"«Путин и мужик» (Они пахали).\n"
                        "В сапогах, в потёртой блузе,\n"
                        "С бодуна, во всей красе,\n"
                        "Шёл мужик по кукурузе,\n"
                        "По несжатой полосе.\n") == 29;
}

bool strcmp1Test() {
  return !strcmp_utf16(u"строка первая", u"строка вторая");
}

bool strcmp2Test() {
  return strcmp_utf16(u"префикс", u"префикс строки");
}

bool strcmp3Test() {
  return strcmp_utf16(u"!???separators '!!!are evil!!!", u"!????separators ,,,,are not evil!!!");
}

bool strcmpRev1Test() {
  return strcmp_rev(u"янем инревереп", u"целиком янем инревереп");
}

bool strcmpRev2Test() {
  return strcmp_rev(u"янем инревереп", u"!!!целиком янем инревереп");
}

int main() {
  Tester tester(
    std::make_pair(strlen1Test, "strlen_utf16. simple"),
    std::make_pair(strlen2Test, "strlen_utf16. more complex"),
    std::make_pair(strcmp1Test, "strcmp_utf16"),
    std::make_pair(strcmp2Test, "strcmp_utf16"),
    std::make_pair(strcmp3Test, "strcmp_utf16"),
    std::make_pair(strcmpRev1Test, "strcmp_rev"),
    std::make_pair(strcmpRev2Test, "strcmp_rev")
  );

  tester.start();
  return 0;
}
