// template_mock_calculator.h
#include <gmock/gmock.h>

// --- Mock Calculator (Adhering to Duck Typing/Concept) ---
// This mock must satisfy the CalculatorLike requirements.
class MockTemplateCalculator {
  public:
	// MOCK_METHOD macros are used directly; no virtual keywords needed.
	MOCK_METHOD(int, add, (int a, int b));
	MOCK_METHOD(int, multiply, (int a, int b));
	MOCK_METHOD(bool, isEven, (int number));
	MOCK_METHOD(int, processValue, (int value));
};
