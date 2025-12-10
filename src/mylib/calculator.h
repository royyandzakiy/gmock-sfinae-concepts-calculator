#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>

// --- C++20 Concept Definition ---
// This concept enforces the required public interface (duck typing contract).
template <typename T>
concept CalculatorConcept = requires(T calc, int a, int b, int number) {
	{ calc.add(a, b) } -> std::same_as<int>;
	{ calc.multiply(a, b) } -> std::same_as<int>;
	{ calc.isEven(number) } -> std::same_as<bool>;
	{ calc.processValue(number) } -> std::same_as<int>;
};

class Calculator {
  public:
	int add(int a, int b);
	int multiply(int a, int b);
	bool isEven(int number);
	int processValue(int value);
};

template <CalculatorConcept T_CalculatorLike> class CalculatorConsumer {
  private:
	T_CalculatorLike calculator_;

  public:
	// Dependency Injection via constructor
	CalculatorConsumer(T_CalculatorLike calculator) : calculator_(std::move(calculator)) {
	}

	// A method of the Consumer that uses the Calculator dependency.
	int calculateSumAndProcess(int a, int b) {
		int sum = calculator_.add(a, b);

		if (calculator_.isEven(sum)) {
			return calculator_.processValue(sum);
		}
		return sum;
	}

	// Another method to demonstrate mocking a different call
	int doubleMultiply(int a, int b) {
		return calculator_.multiply(a, b) * 2;
	}
};