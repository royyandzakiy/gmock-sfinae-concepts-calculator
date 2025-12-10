// inherit_mock_calculator.h
#include <gmock/gmock.h>
#include <inheritlib/calculator.h>

// --- Mock Calculator (Adhering to Duck Typing/Concept) ---
// This mock must satisfy the CalculatorLike requirements.
class MocInheritCalculator : public inheritlib::ICalculator {
  public:
	// MOCK_METHOD macros are used directly; no virtual keywords needed.
	MOCK_METHOD(int, add, (int a, int b), (override));
	MOCK_METHOD(int, multiply, (int a, int b), (override));
	MOCK_METHOD(bool, isEven, (int number), (override));
	MOCK_METHOD(int, processValue, (int value), (override));
};