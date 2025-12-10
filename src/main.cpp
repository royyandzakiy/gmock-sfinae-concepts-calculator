#include "conceptlib/calculator.h"
#include "inheritlib/calculator.h"
#include "sfinaelib/calculator.h"
#include <iostream>
#include <print>

auto main() -> int {
	std::println("Inheritence based");
	inheritlib::Calculator calculatorInh;
	inheritlib::CalculatorManager calcManagerInh(calculatorInh);
	std::println("(2 + 3) * 2 = {}", calcManagerInh.calculateSumAndProcess(2, 3));
	std::println("(2 * 3) * 2 = {}", calcManagerInh.doubleMultiply(2, 3));

	std::println("Template Sfinae based");
	sfinaelib::Calculator calculatorSfin;
	sfinaelib::CalculatorManager<sfinaelib::Calculator> calcManagerSfin(calculatorSfin);
	std::println("(2 + 3) * 2 = {}", calcManagerSfin.calculateSumAndProcess(2, 3));
	std::println("(2 * 3) * 2 = {}", calcManagerSfin.doubleMultiply(2, 3));

	std::println("Template Concepts based");
	conceptlib::Calculator calculatorConc;
	conceptlib::CalculatorManager<conceptlib::Calculator> calcManagerConc(calculatorConc);
	std::println("(2 + 3) * 2 = {}", calcManagerConc.calculateSumAndProcess(2, 3));
	std::println("(2 * 3) * 2 = {}", calcManagerConc.doubleMultiply(2, 3));

	return 0;
}