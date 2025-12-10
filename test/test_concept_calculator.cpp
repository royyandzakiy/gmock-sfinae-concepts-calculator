#include "concept_mock_calculator.h" // Includes the Concept and CalculatorManager
#include <conceptlib/calculator.h>	 // Includes the Concept and CalculatorManager
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

// --- Tests ---

/**
- We test our Manager logic, not the calculator 3rd party lib:
	- We are testing CalculatorManager, NOT Calculator (or MockCalculator).
	This mimics real situation where Calculator is like a WinRT::BluetoothAdvertisementWatcher,
	and we will NOT be testing the advwatcher itself, but instead we mock said advwatcher
	with mock_advwatcher, and insert it into the BleDeviceManager. our goal is to test
	BleDeviceManager has consistent logic.
- We test the flow inside our manager logic, ommit what we don't care:
	- we CARE about the input and output sameness between the all expected function calls sequence,
	we DON'T care about the final output result because it is NOT used elsewhere
	- This is the definition of isolation, we are verifying the contractual interaction and data flow between
	the Manager and the Dependency's interface, ignoring the dependency's internal logic entirely.
- BDD style naming of test:
	Given/When/Then
	Action___When Conditions Met___Should Result

	eg:
	- DoubleMultiply_WhenMockReturnsAValue_ShouldReturnTwoTimesThatValue
	- CalculateSumAndProcess_WhenSumIsOdd_ShouldReturnRawSum
 */

class ConceptRealCalculatorManagerTest_F : public ::testing::Test {
  protected:
	conceptlib::Calculator real_calc;
	conceptlib::CalculatorManager<conceptlib::Calculator> real_calc_mgr{real_calc};
};

TEST_F(ConceptRealCalculatorManagerTest_F, CalculateSumAndProcess_WhenSumIsOdd_ShouldReturnRawSum) {
	EXPECT_EQ(real_calc_mgr.calculateSumAndProcess(2, 3), 5);
}

TEST_F(ConceptRealCalculatorManagerTest_F, CalculateSumAndProcess_WhenSumIsEven_ShouldReturnProcessedValue) {
	EXPECT_EQ(real_calc_mgr.calculateSumAndProcess(4, 6), 20);
}

class ConceptMockCalculatorManagerTest_F : public ::testing::Test {
  protected:
	MockConceptCalculator mock_calc;
	conceptlib::CalculatorManager<MockConceptCalculator> mock_calc_mgr{mock_calc};
};

TEST_F(ConceptMockCalculatorManagerTest_F,
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

TEST_F(ConceptMockCalculatorManagerTest_F, DoubleMultiply_WhenMockReturnsAValue_ShouldReturnTwoTimesThatValue) {
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