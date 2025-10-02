#include <iostream>
#include "test.h"

int main() {
  test();
  std::string name;
  std::cin >> name;
  std::cout << "Hello, " << name;
}