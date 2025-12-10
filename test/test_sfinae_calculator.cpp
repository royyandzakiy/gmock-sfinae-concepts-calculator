// test_sfinae_calculator.cpp
#include "sfinae_mock_calculator.h" // Includes the Sfinae and CalculatorManager
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sfinaelib/calculator.h> // Includes the Sfinae and CalculatorManager

using ::testing::_;
using ::testing::Return;

// --- Tests ---
class SfinaeRealCalculatorManagerTest_F : public ::testing::Test {
  protected:
	sfinaelib::Calculator real_calc;
	sfinaelib::CalculatorManager<sfinaelib::Calculator> real_calc_mgr{real_calc};
};

TEST_F(SfinaeRealCalculatorManagerTest_F, CalculateSumAndProcess_WhenSumIsOdd_ShouldReturnRawSum) {
	EXPECT_EQ(real_calc_mgr.calculateSumAndProcess(2, 3), 5);
}

TEST_F(SfinaeRealCalculatorManagerTest_F, CalculateSumAndProcess_WhenSumIsEven_ShouldReturnProcessedValue) {
	EXPECT_EQ(real_calc_mgr.calculateSumAndProcess(4, 6), 20);
}

class SfinaeMockCalculatorManagerTest_F : public ::testing::Test {
  protected:
	MockSfinaeCalculator mock_calc;
	sfinaelib::CalculatorManager<MockSfinaeCalculator> mock_calc_mgr{mock_calc};
};

TEST_F(SfinaeMockCalculatorManagerTest_F,
	   CalculateSumAndProcess_WhenMockReturnsEvenSum_ShouldReturnMockedProcessedValue) {
	// Test Logic
	// 1. a call of add: 5 + 5 = 10 (input(s) required, output required)
	// 2. a call of isEven: isEven(10) = true; this triggers processValue (input required, output required)
	// 3. a call of processValue: processValue(10) = 99 (input required, output discarded)

	// Arrange
	const int DISCARDED_OUTPUT = 99;

	EXPECT_CALL(mock_calc, add(5, 15)).WillOnce(Return(20));
	EXPECT_CALL(mock_calc, isEven(20)).WillOnce(Return(true));
	EXPECT_CALL(mock_calc, processValue(20)).WillOnce(Return(DISCARDED_OUTPUT));

	// Act & Assert
	EXPECT_EQ(mock_calc_mgr.calculateSumAndProcess(5, 15), DISCARDED_OUTPUT);
}

TEST_F(SfinaeMockCalculatorManagerTest_F, DoubleMultiply_WhenMockReturnsAValue_ShouldReturnTwoTimesThatValue) {
	// Test Logic
	// 1. a call to multiply: 3 * any = 7 (input a required, input b discarded, output required)
	// 2. final processing: 7 * 2 = 14 (input required, output required)
	const int expected_value = 7 * 2;
	const int DISCARDED_INPUT_B = 4;

	// Arrange
	EXPECT_CALL(mock_calc, multiply(3, _)).WillOnce(Return(7));

	// Act & Assert
	EXPECT_EQ(mock_calc_mgr.doubleMultiply(3, DISCARDED_INPUT_B), expected_value);
}