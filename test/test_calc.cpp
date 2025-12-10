#include "calculator.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::NiceMock;
using ::testing::Return;

// Mock class for Calculator
class MockCalculator : public Calculator {
  public:
	MOCK_METHOD(int, add, (int a, int b), (override));
	MOCK_METHOD(int, multiply, (int a, int b), (override));
	MOCK_METHOD(bool, isEven, (int number), (override));
	MOCK_METHOD(int, processValue, (int value), (override));
};

// Basic test without mocking
TEST(CalculatorTest, BasicOperations) {
	Calculator calc;
	EXPECT_EQ(calc.add(2, 3), 5);
	EXPECT_EQ(calc.multiply(4, 5), 20);
	EXPECT_TRUE(calc.isEven(4));
	EXPECT_FALSE(calc.isEven(5));
}

// Test using mock
TEST(CalculatorTest, MockUsage) {
	NiceMock<MockCalculator> mockCalc;

	// Set expectations
	EXPECT_CALL(mockCalc, add(2, 3)).WillOnce(Return(100)); // Mocked to return 100

	EXPECT_CALL(mockCalc, isEven(4)).WillOnce(Return(false)); // Mocked to return false

	// Use the mock
	EXPECT_EQ(mockCalc.add(2, 3), 100);
	EXPECT_FALSE(mockCalc.isEven(4));
}

// Test with argument matchers
TEST(CalculatorTest, WithMatchers) {
	MockCalculator mockCalc;

	// Any argument
	EXPECT_CALL(mockCalc, add(testing::_, testing::_)).WillOnce(Return(42));

	// Specific argument
	EXPECT_CALL(mockCalc, isEven(10)).WillOnce(Return(true));

	EXPECT_EQ(mockCalc.add(1, 2), 42);
	EXPECT_TRUE(mockCalc.isEven(10));
}

// Test multiple calls
TEST(CalculatorTest, MultipleCalls) {
	MockCalculator mockCalc;

	EXPECT_CALL(mockCalc, multiply(testing::_, testing::_)).Times(2).WillOnce(Return(10)).WillOnce(Return(20));

	EXPECT_EQ(mockCalc.multiply(1, 2), 10);
	EXPECT_EQ(mockCalc.multiply(3, 4), 20);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}