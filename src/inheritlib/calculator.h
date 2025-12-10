#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>

namespace inheritlib {

class Calculator {
  public:
	int add(int a, int b);
	int multiply(int a, int b);
	bool isEven(int number);
	int processValue(int value);
};

};