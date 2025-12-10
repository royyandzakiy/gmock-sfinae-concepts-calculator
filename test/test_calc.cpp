#include "calculator.h" // Includes the Concept and CalculatorManager
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

// --- Mock Calculator (Adhering to Duck Typing/Concept) ---
// This mock must satisfy the CalculatorLike requirements.
class MockCalculator {
  public:
	// MOCK_METHOD macros are used directly; no virtual keywords needed.
	MOCK_METHOD(int, add, (int a, int b));
	MOCK_METHOD(int, multiply, (int a, int b));
	MOCK_METHOD(bool, isEven, (int number));
	MOCK_METHOD(int, processValue, (int value));
};

// --- Tests ---

// Test the Consumer with the REAL Dependency (Sanity Check)
TEST(CalculatorManagerTest, RealDependency) {
	templatelib::Calculator real_calc;
	// T_Calculator = Calculator. Concept check passes.
	templatelib::CalculatorManager<templatelib::Calculator> real_calc_manager(real_calc);

	// 2 + 3 = 5 (odd), returns 5
	EXPECT_EQ(real_calc_manager.calculateSumAndProcess(2, 3), 5);

	// 4 + 6 = 10 (even), processValue(10) returns 20
	EXPECT_EQ(real_calc_manager.calculateSumAndProcess(4, 6), 20);
}

// Test the Consumer with the MOCK Dependency (Isolation)
TEST(CalculatorManagerTest, MockDependencyInjection) {
	MockCalculator mock_calc;

	// Set expectations for calculateSumAndProcess (Case: Sum is Processed)
	EXPECT_CALL(mock_calc, add(5, 5)).WillOnce(Return(10));
	EXPECT_CALL(mock_calc, isEven(10)).WillOnce(Return(true));
	EXPECT_CALL(mock_calc, processValue(10)).WillOnce(Return(99)); // Mock the final value to test flow control

	// T_Calculator = MockCalculator. Concept check passes.
	templatelib::CalculatorManager<MockCalculator> mock_calc_manager_1(mock_calc);
	EXPECT_EQ(mock_calc_manager_1.calculateSumAndProcess(5, 5), 99);

	// Set expectations for doubleMultiply
	EXPECT_CALL(mock_calc, multiply(3, _)).WillOnce(Return(7)); // Mock multiply(3, X) to return 7

	templatelib::CalculatorManager<MockCalculator> mock_calc_manager_2(mock_calc);
	// doubleMultiply(3, 4) should return 7 * 2 = 14
	EXPECT_EQ(mock_calc_manager_2.doubleMultiply(3, 4), 14);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}