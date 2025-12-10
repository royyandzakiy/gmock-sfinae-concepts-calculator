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

// --- C++17 Type Traits Definition ---
template <typename T, typename = void> struct is_calculator_like_type_trait : std::false_type {};
template <typename T>
struct is_calculator_like_type_trait<
	T, std::void_t<
		   // function expression check
		   decltype(std::declval<T>().add(0, 0)), decltype(std::declval<T>().multiply(0, 0)),
		   decltype(std::declval<T>().isEven(0)), decltype(std::declval<T>().processValue(0)),

		   // type check
		   std::enable_if<std::is_same<decltype(std::declval<T>().add(0, 0)), int>::value>,
		   std::enable_if<std::is_same<decltype(std::declval<T>().multiply(0, 0)), int>::value>,
		   std::enable_if<std::is_same<decltype(std::declval<T>().isEven(0)), bool>::value>,
		   std::enable_if<std::is_same<decltype(std::declval<T>().processValue(0)), int>::value>>> : std::true_type {};

template <typename T> constexpr bool is_calculator_like_type_trait_v = is_calculator_like_type_trait<T>::value;

template <typename T, typename = std::enable_if_t<is_calculator_like_type_trait_v<T>>> class CalculatorManager {
	static_assert(is_calculator_like_type_trait_v<T>,
				  "Type does not have required methodes: add(), multiply(), isEven(), processValue()");

  public:
	// Non-owning dependency, but safe and modern.
	explicit CalculatorManager(std::reference_wrapper<T> calculator) : calculator_(calculator) {
	}

	int calculateSumAndProcess(int a, int b) {
		auto &c = calculator_.get();
		int sum = c.add(a, b);
		return c.isEven(sum) ? c.processValue(sum) : sum;
		return 0;
	}

	int doubleMultiply(int a, int b) {
		auto &c = calculator_.get();
		return c.multiply(a, b) * 2;
		return 0;
	}

  private:
	std::reference_wrapper<T> calculator_;
};

}; // namespace sfinaelib