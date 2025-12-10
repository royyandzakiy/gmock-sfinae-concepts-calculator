#include "templib/calculator.h"
#include <iostream>

int main() {
	templib::Calculator calculator;
	templib::CalculatorManager<templib::Calculator> calcManager(calculator);
	std::cout << "(2 + 3) * 2 = " << calcManager.calculateSumAndProcess(2, 3) << std::endl;
	std::cout << "(2 * 3) * 2 = " << calcManager.doubleMultiply(2, 3) << std::endl;
	return 0;
}