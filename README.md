# GMock Testing: Inheritance, Sfinae, Concepts

This codebase demonstrates three approaches to dependency abstraction in C++ and how each can be cleanly unit-tested with GoogleTest and GoogleMock:

1. **Concept-based (duck-typed) dependency injection**
2. **Interface/inheritance-based dependency injection**
3. **SFINAE-based template constraint injection**

Each approach provides a mockable dependency that can be injected into `CalculatorManager`, allowing us to validate the manager’s logic in isolation.

The goal is **not** to test the underlying calculator implementations. The goal is to verify that `CalculatorManager` correctly orchestrates its dependency through defined interactions, inputs, and outputs.

---

# Testing Strategy

## 1. What We Test

We test **only the manager logic** (e.g., `CalculatorManager<T>`).
We do **not** test the actual calculator implementation, similar to how you would mock a system object such as `WinRT::BluetoothAdvertisementWatcher` when testing a BLE device manager. Here we assume calculator is a non-changable 3rd party class.

The manager is the unit under test; the calculator is treated purely as a dependency interface.

## 2. What We Care About

Our tests assert:

* The expected sequence of calls on the mock dependency
* That each call receives the correct inputs
* That the manager behaves correctly based on the mock outputs

We do **not** validate the correctness of the calculator’s internal computation; these values are completely under test control.

This is isolation testing: validating the contractual interaction and data flow between the manager and its dependency.

## 3. Test Naming (BDD Style)

Tests are named using a **Given / When / Then** structure in a compact Action_WhenCondition_ShouldResult format.

Examples:

* `DoubleMultiply_WhenMockReturnsAValue_ShouldReturnTwoTimesThatValue`
* `CalculateSumAndProcess_WhenSumIsOdd_ShouldReturnRawSum`

---

# Example Interactions

### Example 1: Verifying a Sequence of Multiple Calls

```cpp
TEST_F(ConceptMockCalculatorManagerTest_F,
       CalculateSumAndProcess_WhenMockReturnsEvenSum_ShouldReturnMockedProcessedValue) {
    // Test flow:
    // 1. add(5, 15) → 20
    // 2. isEven(20) → true
    // 3. processValue(20) → 99 (returned from manager)

    const int DISCARDED_OUTPUT = 99;

    EXPECT_CALL(mock_calc, add(5, 15)).WillOnce(Return(20));
    EXPECT_CALL(mock_calc, isEven(20)).WillOnce(Return(true));
    EXPECT_CALL(mock_calc, processValue(20)).WillOnce(Return(DISCARDED_OUTPUT));

    EXPECT_EQ(mock_calc_mgr.calculateSumAndProcess(5, 15), DISCARDED_OUTPUT);
}
```

This test verifies that `CalculatorManager` correctly coordinates multiple dependent calls.

### Example 2: Omitting Unimportant Values

When a particular input to the dependency is irrelevant to the test, we explicitly mark it as discarded using GoogleMock wildcards:

```cpp
TEST_F(ConceptMockCalculatorManagerTest_F,
       DoubleMultiply_WhenMockReturnsAValue_ShouldReturnTwoTimesThatValue) {
    // multiply(3, _) → 7, final result is 7 * 2

    const int expected_value = 14;
    const int DISCARDED_INPUT_B = 4;

    EXPECT_CALL(mock_calc, multiply(3, _)).WillOnce(Return(7));

    EXPECT_EQ(mock_calc_mgr.doubleMultiply(3, DISCARDED_INPUT_B), expected_value);
}
```

This ensures test clarity: we verify only the inputs that matter to the scenario.

---

# Codebase Context (Short Guide)

Below is a brief orientation of the relevant components.

### Concept-Based Mock

Located in `concept_mock_calculator.h`:

```cpp
class MockConceptCalculator {
public:
    MOCK_METHOD(int, add, (int a, int b));
    MOCK_METHOD(int, multiply, (int a, int b));
    MOCK_METHOD(bool, isEven, (int number));
    MOCK_METHOD(int, processValue, (int value));
};
```

No inheritance is needed; the mock satisfies a *concept* that the manager is templated against.

### Inheritance-Based Mock

Located in `inherit_mock_calculator.h`:

```cpp
class MockInheritCalculator : public inheritlib::ICalculator {
public:
    MOCK_METHOD(int, add, (int a, int b), (override));
    MOCK_METHOD(int, multiply, (int a, int b), (override));
    MOCK_METHOD(bool, isEven, (int number), (override));
    MOCK_METHOD(int, processValue, (int value), (override));
};
```

This mock explicitly implements the interface.

### SFINAE-Based Mock

Structure mirrors the concept-based mock but relies on SFINAE constraints.

### Test Layout

Each testing folder (`concept`, `inherit`, `sfinae`) contains:

* Real calculator tests
* Manager tests using mocks
* Identical behavior scenarios implemented across all three abstractions for comparison

This allows you to assess how gMock interacts with concept-based mocks, interface-based mocks, and SFINAE-validated mocks.

---

# Summary

* The manager is the unit under test; calculators are mocked dependencies.
* Tests verify interaction flow, not business logic of the calculator.
* gMock is used to validate call sequences, required inputs, and manager-driven branching.
* Wildcards allow omission of irrelevant values.
* All three architectural patterns (concepts, inheritance, SFINAE) are demonstrated and tested consistently.

If you need a polished Markdown document version or want this embedded back into your repository as a README with structure, I can prepare that as well.
