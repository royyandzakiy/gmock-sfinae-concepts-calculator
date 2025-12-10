#include "../../include/templatelib/calculator.h"

int templatelib::Calculator::add(int a, int b) {
	return a + b;
}

int templatelib::Calculator::multiply(int a, int b) {
	return a * b;
}

bool templatelib::Calculator::isEven(int number) {
	return number % 2 == 0;
}

int templatelib::Calculator::processValue(int value) {
	return value * 2;
}