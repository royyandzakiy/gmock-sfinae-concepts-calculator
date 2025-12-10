#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>

namespace sfinaelib {

class Calculator {
  public:
	int add(int a, int b);
	int multiply(int a, int b);
	bool isEven(int number);
	int processValue(int value);
};

// --- C++20 Concept Definition ---
// This concept enforces the required public interface (duck typing contract).
template <typename T>
concept CalculatorLike = requires(T t, int a, int b) {
	{ t.add(a, b) } -> std::same_as<int>;
	{ t.multiply(a, b) } -> std::same_as<int>;
	{ t.isEven(a) } -> std::same_as<bool>;
	{ t.processValue(a) } -> std::same_as<int>;
};

template <CalculatorLike T> class CalculatorManager {
  public:
	// Non-owning dependency, but safe and modern.
	explicit CalculatorManager(std::reference_wrapper<T> calculator) : calculator_(calculator) {
	}

	int calculateSumAndProcess(int a, int b) {
		auto &c = calculator_.get();
		int sum = c.add(a, b);
		return c.isEven(sum) ? c.processValue(sum) : sum;
	}

	int doubleMultiply(int a, int b) {
		auto &c = calculator_.get();
		return c.multiply(a, b) * 2;
	}

  private:
	std::reference_wrapper<T> calculator_;
};

};