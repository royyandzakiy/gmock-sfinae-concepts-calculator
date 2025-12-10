#include "mylib/calculator.h"
#include <iostream>

int main() {
	Calculator calc;
	std::cout << "2 + 3 = " << calc.add(2, 3) << std::endl;
	return 0;
}