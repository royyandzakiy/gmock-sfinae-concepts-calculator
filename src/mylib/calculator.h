#pragma once

class Calculator {
  public:
	virtual ~Calculator() = default;

	virtual int add(int a, int b);
	virtual int multiply(int a, int b);
	virtual bool isEven(int number);

	// A method that uses a dependency (for mocking demonstration)
	virtual int processValue(int value);
};