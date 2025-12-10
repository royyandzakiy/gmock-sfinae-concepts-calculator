#include "conceptlib/calculator.h"
#include "inheritlib/calculator.h"
#include <iostream>

int main() {
	conceptlib::Calculator calculator;
	conceptlib::CalculatorManager<conceptlib::Calculator> calcManager(calculator);
	std::cout << "(2 + 3) * 2 = " << calcManager.calculateSumAndProcess(2, 3) << std::endl;
	std::cout << "(2 * 3) * 2 = " << calcManager.doubleMultiply(2, 3) << std::endl;

	inheritlib::Calculator calculator2;
	inheritlib::CalculatorManager calcManager2(calculator2);
	std::cout << "(2 + 3) * 2 = " << calcManager2.calculateSumAndProcess(2, 3) << std::endl;
	std::cout << "(2 * 3) * 2 = " << calcManager2.doubleMultiply(2, 3) << std::endl;
	return 0;
}