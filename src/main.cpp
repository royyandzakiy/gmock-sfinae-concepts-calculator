#include "conceptlib/calculator.h"
#include "inheritlib/calculator.h"
#include "sfinaelib/calculator.h"
#include <iostream>

int main() {
	std::cout << "Inheritence based" << std::endl;
	inheritlib::Calculator calculatorInh;
	inheritlib::CalculatorManager calcManagerInh(calculatorInh);
	std::cout << "(2 + 3) * 2 = " << calcManagerInh.calculateSumAndProcess(2, 3) << std::endl;
	std::cout << "(2 * 3) * 2 = " << calcManagerInh.doubleMultiply(2, 3) << std::endl;

	std::cout << "Template Sfinae based" << std::endl;
	sfinaelib::Calculator calculatorSfin;
	sfinaelib::CalculatorManager<sfinaelib::Calculator> calcManagerSfin(calculatorSfin);
	std::cout << "(2 + 3) * 2 = " << calcManagerSfin.calculateSumAndProcess(2, 3) << std::endl;
	std::cout << "(2 * 3) * 2 = " << calcManagerSfin.doubleMultiply(2, 3) << std::endl;

	std::cout << "Template Concepts based" << std::endl;
	conceptlib::Calculator calculatorConc;
	conceptlib::CalculatorManager<conceptlib::Calculator> calcManagerConc(calculatorConc);
	std::cout << "(2 + 3) * 2 = " << calcManagerConc.calculateSumAndProcess(2, 3) << std::endl;
	std::cout << "(2 * 3) * 2 = " << calcManagerConc.doubleMultiply(2, 3) << std::endl;
	return 0;
}