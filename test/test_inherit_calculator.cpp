// test_inherit_calculator.cpp
#include "inherit_mock_calculator.h" // Includes the Concept and CalculatorManager
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <inheritlib/calculator.h> // Includes the Concept and CalculatorManager

using ::testing::_;
using ::testing::Return;

// --- Tests ---

TEST(InheritCalculatorTest, CalculateSumAndProcess_WhenSumIsOdd_ShouldReturnRawSum) {
	inheritlib::Calculator real_calc;
	inheritlib::CalculatorManager real_calc_manager(real_calc);

	// Arrange

	// Act & Assert
	// Case 1: 2 + 3 = 5 (odd), returns 5; (if isEven is false, return the sum directly.)
	EXPECT_EQ(real_calc_manager.calculateSumAndProcess(2, 3), 5);
}

TEST(InheritCalculatorTest, CalculateSumAndProcess_WhenSumIsEven_ShouldReturnProcessedValue) {
	inheritlib::Calculator real_calc;
	inheritlib::CalculatorManager real_calc_manager(real_calc);

	// Arrange

	// Act & Assert
	// Case 2: 4 + 6 = 10 (even), processValue(10) returns 20; (if isEven is true, return processValue(sum).)
	EXPECT_EQ(real_calc_manager.calculateSumAndProcess(4, 6), 20);
}

TEST(InheritCalculatorTest, MockCalculateSumAndProcess_WhenMockReturnsEvenSum_ShouldReturnMockedProcessedValue) {
	MockInheritCalculator mock_calc;
	inheritlib::CalculatorManager mock_calc_manager(mock_calc);

	// Arrange
	// 1. sum: 5 + 5 = 10
	// 2. check: isEven(10) = true (triggers processValue)
	// 3. process: processValue(10) = 99 (mock the final output)
	EXPECT_CALL(mock_calc, add(5, 5)).WillOnce(Return(10));
	EXPECT_CALL(mock_calc, isEven(10)).WillOnce(Return(true));
	EXPECT_CALL(mock_calc, processValue(10)).WillOnce(Return(99));

	// Act & Assert
	// The call should trigger the mock sequence and return 99, testing the flow control.
	EXPECT_EQ(mock_calc_manager.calculateSumAndProcess(5, 5), 99);
}

TEST(InheritCalculatorTest, MockDoubleMultiply_ShouldReturnTwoTimesMockedMultiplyResult) {
	MockInheritCalculator mock_calc;
	inheritlib::CalculatorManager mock_calc_manager(mock_calc);
	int expected_value = 14; // Mocked multiply result (7) * 2 = 14

	// Arrange
	// Mock multiply(3, X) to return 7, regardless of the second argument.
	EXPECT_CALL(mock_calc, multiply(3, _)).WillOnce(Return(7));

	// Act & Assert
	// doubleMultiply(3, 4) should call mock_calc.multiply(3, 4), get 7, and return 7 * 2 = 14
	EXPECT_EQ(mock_calc_manager.doubleMultiply(3, 4), expected_value);
}