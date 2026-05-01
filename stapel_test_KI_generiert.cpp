#include <iostream>
#include <string>
#include <typeinfo> // Required for typeid
// Include the header that defines the Stapel class
#include "Stapel.h" 

/**
 * @brief Helper function to run a specific test sequence and report results.
 * @tparam T The type stored in the stack (e.g., int, std::string).
 * @param name Name of the test group.
 * @param stack Object instance to be tested.
 */
template<typename T>
void run_test(const std::string& name, Stapel<T>& stack) {
    std::cout << "\n========================================\n";
    std::cout << "STARTING TEST: " << name << "\n";
    std::cout << "========================================";

    // 1. Test initial state (Stack should be empty)
    if (!stack.istLeer()) {
        std::cerr << "[FAIL] Initial check failed: Stack reported as not empty." << std::endl;
    } else {
        std::cout << "[PASS] Initial state: Stack is correctly reported as empty." << std::endl;
    }

    // 2. Test Push operation (Populating the stack)
    T item1;
    T item2;
    T item3;

    // Use C++17 if constexpr to handle type-specific initialization
    if constexpr (std::is_same_v<T, std::string>) {
        item1 = T("First Item"); 
        item2 = T("Second Item");
        item3 = T("Third Item - Top");
    } else { // Assuming int or other numeric type for simplicity in this test case
        // We must explicitly cast to avoid the const char* -> int conversion warning/error.
        item1 = reinterpret_cast<T>(1);
        item2 = reinterpret_cast<T>(2);
        item3 = reinterpret_cast<T>(3);
    }

    stack.push(item1);
    std::cout << "[INFO] Pushed: " << (typeid(T) == typeid(std::string) ? "String" : "Value") << " 1" << std::endl;
    
    stack.push(item2);
    std::cout << "[INFO] Pushed: " << (typeid(T) == typeid(std::string) ? "String" : "Value") << " 2" << std::endl;

    // 3. Test Top operation before pop (Check current top)
    try {
        T top_item = stack.top();
        if constexpr (std::is_same_v<T, std::string>) {
             if (top_item != item2) { // String comparison is safe here
                std::cerr << "[FAIL] Top check failed: Expected " << "Second Item" 
                          << ", got wrong element." << std::endl;
            } else {
                 std::cout << "[PASS] Top check: Correctly retrieved current top element (String 2)." << std::endl;
            }
        } else {
             // Integer comparison is safe here, but requires casting for logging clarity.
             if (top_item != item2) {
                std::cerr << "[FAIL] Top check failed: Expected " << static_cast<int>(item2) 
                          << ", got wrong element." << std::endl;
            } else {
                 std::cout << "[PASS] Top check: Correctly retrieved current top element (Value 2)." << std::endl;
            }
        }

    } catch (const std::out_of_range& e) {
        std::cerr << "[FAIL] Top check failed: Caught unexpected exception on non-empty stack. (" << e.what() << ")" << std::endl;
    }

    // 4. Test LIFO Pop cycle
    try {
        T popped1 = stack.pop(); // Should be item2
        if constexpr (std::is_same_v<T, std::string>) {
             if (popped1 != item2) {
                std::cerr << "[FAIL] Pop 1 failed: Expected " << "Second Item" 
                          << ", got wrong element." << std::endl;
            } else {
                 std::cout << "[PASS] Popped item 2 successfully. Current Top should be item1." << std::endl;
            }
        } else {
             if (popped1 != item2) {
                std::cerr << "[FAIL] Pop 1 failed: Expected " << static_cast<int>(item2) 
                          << ", got wrong element." << std::endl;
            } else {
                 std::cout << "[PASS] Popped item 2 successfully. Current Top should be item1." << std::endl;
            }
        }

        T popped2 = stack.pop(); // Should be item1
         if constexpr (std::is_same_v<T, std::string>) {
             if (popped2 != item1) {
                std::cerr << "[FAIL] Pop 2 failed: Expected " << "First Item" 
                          << ", got wrong element." << std::endl;
            } else {
                 std::cout << "[PASS] Popped item 1 successfully. Stack should now be empty." << std::endl;
            }
        } else {
             if (popped2 != item1) {
                std::cerr << "[FAIL] Pop 2 failed: Expected " << static_cast<int>(item1) 
                          << ", got wrong element." << std::endl;
            } else {
                 std::cout << "[PASS] Popped item 1 successfully. Stack should now be empty." << std::endl;
            }
        }

    } catch (const std::out_of_range& e) {
        // This is a failure if it happens prematurely, but we handle that in step 5.
        std::cerr << "[CRITICAL FAIL] Pop cycle failed unexpectedly: " << e.what() << std::endl;
    }

    // 5. Test Empty Stack Exception Handling (Crucial edge case)
    try {
        // Try to pop one more time when empty
        stack.pop(); 
        std::cerr << "[FAIL] Empty stack test failed: Expected an exception, but the program continued." << std::endl;

    } catch (const std::out_of_range& e) {
        std::cout << "[PASS] Exception Handling (Pop): Successfully caught expected 'Stack is empty' error. (" << e.what() << ")" << std::endl;
    }

    // 6. Test Empty Stack Top exception handling
    try {
         stack.top();
         std::cerr << "[FAIL] Empty stack test failed: Expected an exception on top(), but the program continued." << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "[PASS] Exception Handling (Top): Successfully caught expected 'Stack is empty' error." << std::endl;
    }

    // 7. Final State Check
     if (!stack.istLeer()) {
        std::cerr << "[FAIL] Final state check failed: Stack reported as not empty after full test cycle." << std::endl;
    } else {
        std::cout << "[PASS] Final state: Stack is correctly reported as empty." << std::endl;
    }
}

// Main function to run the tests for two types (string and int)
int main() {
    std::cout << "****************************************\n";
    std::cout << "  Stapel Class Unit Test Suite (C++)   \n";
    std::cout << "****************************************\n";

    // --- Test Case 1: Testing with std::string ---
    {
        Stapel<std::string> string_stack;
        run_test("String Type Stack (LIFO)", string_stack);
    }
    
    // --- Test Case 2: Testing with int ---
    {
        Stapel<int> int_stack;
        run_test("Integer Type Stack (LIFO)", int_stack);
    }

    std::cout << "\n========================================\n";
    std::cout << "All tests finished. Please check the output for PASS/FAIL status.\n";
    std::cout << "========================================\n";
    
    return 0;
}