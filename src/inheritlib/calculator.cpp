#include "calculator.h"

int inheritlib::Calculator::add(int a, int b) {
	return a + b;
}

int inheritlib::Calculator::multiply(int a, int b) {
	return a * b;
}

bool inheritlib::Calculator::isEven(int number) {
	return number % 2 == 0;
}

int inheritlib::Calculator::processValue(int value) {
	return value * 2;
}