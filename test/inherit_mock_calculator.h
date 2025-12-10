// inherit_mock_calculator.h
#include <gmock/gmock.h>
#include <inheritlib/calculator.h>

// --- Mock Inherited Calculator (Adhering to Inheritance) ---
// This mock must satisfy the ICalculator interface.
class MockInheritCalculator : public inheritlib::ICalculator {
  public:
	MOCK_METHOD(int, add, (int a, int b), (override));
	MOCK_METHOD(int, multiply, (int a, int b), (override));
	MOCK_METHOD(bool, isEven, (int number), (override));
	MOCK_METHOD(int, processValue, (int value), (override));
};