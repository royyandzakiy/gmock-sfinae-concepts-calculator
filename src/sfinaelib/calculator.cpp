#include "../../include/sfinaelib/calculator.h"

namespace sfinaelib {
int Calculator::add(int a, int b) {
	return a + b;
}

int Calculator::multiply(int a, int b) {
	return a * b;
}

bool Calculator::isEven(int number) {
	return number % 2 == 0;
}

int Calculator::processValue(int value) {
	return value * 2;
}
} // namespace sfinaelib