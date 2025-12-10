#include "calculator.h"

int templib::Calculator::add(int a, int b) {
	return a + b;
}

int templib::Calculator::multiply(int a, int b) {
	return a * b;
}

bool templib::Calculator::isEven(int number) {
	return number % 2 == 0;
}

int templib::Calculator::processValue(int value) {
	return value * 2;
}