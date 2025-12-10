#include "inheritlib/calculator.h"
#include "templatelib/calculator.h"
#include <iostream>

int main() {
	templatelib::Calculator calculator;
	templatelib::CalculatorManager<templatelib::Calculator> calcManager(calculator);
	std::cout << "(2 + 3) * 2 = " << calcManager.calculateSumAndProcess(2, 3) << std::endl;
	std::cout << "(2 * 3) * 2 = " << calcManager.doubleMultiply(2, 3) << std::endl;

	inheritlib::Calculator calculator2;
	return 0;
}