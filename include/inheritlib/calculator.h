#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>

namespace inheritlib {

class ICalculator {
  public:
	virtual ~ICalculator() = default;

	virtual int add(int a, int b) = 0;
	virtual int multiply(int a, int b) = 0;
	virtual bool isEven(int number) = 0;
	virtual int processValue(int value) = 0;
};

class Calculator : public ICalculator {
  public:
	int add(int a, int b) override;
	int multiply(int a, int b) override;
	bool isEven(int number) override;
	int processValue(int value) override;
};

class CalculatorManager {
  public:
	// Non-owning dependency, but safe and modern.
	explicit CalculatorManager(std::reference_wrapper<ICalculator> calculator) : calculator_(calculator) {
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
	std::reference_wrapper<ICalculator> calculator_;
};

};