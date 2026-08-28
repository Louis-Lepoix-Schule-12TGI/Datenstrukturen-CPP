#include <iostream>
#include <string>
#include <memory>
#include "Stapel.h"

/**
 * @brief Helper function to run a specific test sequence and report results.
 * Works with both int and std::string types using shared_ptr semantics.
 */
template<typename T>
void run_stapel_test(const std::string& name, Stapel<T>& stack) {
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
    T item1, item2, item3;
    
    if constexpr (std::is_same_v<T, std::string>) {
        item1 = "First Item"; 
        item2 = "Second Item";
        item3 = "Third Item - Top";
    } else { // int or other numeric type
        item1 = 1;
        item2 = 2;
        item3 = 3;
    }

    stack.push(item1);
    std::cout << "[INFO] Pushed: " << (typeid(T) == typeid(std::string) ? "\"" : "") 
              << item1 
              << (typeid(T) == typeid(std::string) ? "\"" : "") << std::endl;
              
    stack.push(item2);
    std::cout << "[INFO] Pushed: " << (typeid(T) == typeid(std::string) ? "\"" : "") 
              << item2 
              << (typeid(T) == typeid(std::string) ? "\"" : "") << std::endl;

    stack.push(item3);
    std::cout << "[INFO] Pushed: " << (typeid(T) == typeid(std::string) ? "\"" : "") 
              << item3 
              << (typeid(T) == typeid(std::string) ? "\"" : "") << std::endl;

    // 3. Test Top operation before pop (Check current top)
    try {
        T top_item = stack.top();
        if constexpr (std::is_same_v<T, std::string>) {
            if (top_item != item3) {
                std::cerr << "[FAIL] Top check failed: Expected \"" << item3 
                          << "\", got \"" << top_item << "\"." << std::endl;
            } else {
                 std::cout << "[PASS] Top check: Correctly retrieved current top element (" 
                          << item3 << ")." << std::endl;
            }
        } else {
             if (top_item != item3) {
                std::cerr << "[FAIL] Top check failed: Expected " << static_cast<int>(item3) 
                          << ", got " << static_cast<int>(top_item) << "." << std::endl;
            } else {
                 std::cout << "[PASS] Top check: Correctly retrieved current top element (" 
                          << static_cast<int>(item3) << ")." << std::endl;
            }
        }

    } catch (const std::out_of_range& e) {
        std::cerr << "[FAIL] Top check failed: Caught unexpected exception on non-empty stack. (" 
                  << e.what() << ")" << std::endl;
    }

    // 4. Test LIFO Pop cycle
    try {
        T popped1 = stack.pop(); // Should be item3 (most recent)
        if constexpr (std::is_same_v<T, std::string>) {
             if (popped1 != item3) {
                std::cerr << "[FAIL] Pop 1 failed: Expected \"" << item3 
                          << "\", got \"" << popped1 << "\"." << std::endl;
            } else {
                 std::cout << "[PASS] Popped item 3 successfully. Current Top should be item2 (" 
                          << item2 << ")." << std::endl;
            }
        } else {
             if (popped1 != item3) {
                std::cerr << "[FAIL] Pop 1 failed: Expected " << static_cast<int>(item3) 
                          << ", got " << static_cast<int>(popped1) << "." << std::endl;
            } else {
                 std::cout << "[PASS] Popped item 3 successfully. Current Top should be item2 (" 
                          << static_cast<int>(item2) << ")." << std::endl;
            }
        }

        T popped2 = stack.pop(); // Should be item2 (now most recent after pop1)
         if constexpr (std::is_same_v<T, std::string>) {
             if (popped2 != item2) {
                std::cerr << "[FAIL] Pop 2 failed: Expected \"" << item2 
                          << "\", got \"" << popped2 << "\"." << std::endl;
            } else {
                 std::cout << "[PASS] Popped item 2 successfully. Current Top should be item1 (" 
                          << item1 << ")." << std::endl;
            }
        } else {
             if (popped2 != item2) {
                std::cerr << "[FAIL] Pop 2 failed: Expected " << static_cast<int>(item2) 
                          << ", got " << static_cast<int>(popped2) << "." << std::endl;
            } else {
                 std::cout << "[PASS] Popped item 2 successfully. Current Top should be item1 (" 
                          << static_cast<int>(item1) << ")." << std::endl;
            }
        }

    } catch (const std::out_of_range& e) {
        std::cerr << "[CRITICAL FAIL] Pop cycle failed unexpectedly: " << e.what() << std::endl;
    }

    // 5. Test Top of remaining element
    try {
        T currentTop = stack.top(); // Should be item1
        if constexpr (std::is_same_v<T, std::string>) {
            if (currentTop != item1) {
                std::cerr << "[FAIL] Remaining Top check failed: Expected \"" << item1 
                          << "\", got \"" << currentTop << "\"." << std::endl;
            } else {
                 std::cout << "[PASS] Remaining Top check: Correctly retrieved last element (" 
                          << item1 << ")." << std::endl;
            }
        } else {
             if (currentTop != item1) {
                std::cerr << "[FAIL] Remaining Top check failed: Expected " << static_cast<int>(item1) 
                          << ", got " << static_cast<int>(currentTop) << "." << std::endl;
            } else {
                 std::cout << "[PASS] Remaining Top check: Correctly retrieved last element (" 
                          << static_cast<int>(item1) << ")." << std::endl;
            }
        }

    } catch (const std::out_of_range& e) {
        std::cerr << "[FAIL] Remaining Top check failed with exception: " << e.what() << std::endl;
    }

    // 6. Test Empty Stack Exception Handling (Crucial edge case)
    try {
        stack.pop(); // Should throw - stack has only one element now!
        std::cerr << "[FAIL] Empty stack test failed: Expected an exception, but the program continued." 
                  << std::endl;

    } catch (const std::out_of_range& e) {
        std::cout << "[PASS] Exception Handling (Pop): Successfully caught expected 'Stack is empty' error. (" 
                  << e.what() << ")" << std::endl;
    }

    // 7. Test Empty Stack Top exception handling
    try {
         stack.top();
         std::cerr << "[FAIL] Empty stack test failed: Expected an exception on top(), but the program continued." 
                   << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "[PASS] Exception Handling (Top): Successfully caught expected 'Stack is empty' error. (" 
                  << e.what() << ")" << std::endl;
    }

    // 8. Final State Check - Stack should be empty now!
     if (!stack.istLeer()) {
        std::cerr << "[FAIL] Final state check failed: Stack reported as not empty after full test cycle." 
                  << std::endl;
    } else {
        std::cout << "[PASS] Final state: Stack is correctly reported as empty." << std::endl;
    }
};

// Main function to run the tests for both types
int main() {
    std::cout << "****************************************\n";
    std::cout << "  Stapel Class Unit Test Suite (C++)\n";
    std::cout << "  Version: shared_ptr implementation   \n";
    std::cout << "****************************************\n";

    // --- Test Case 1: Testing with std::string ---
    {
        Stapel<std::string> string_stack;
        run_stapel_test("String Type Stack (LIFO) - shared_ptr", string_stack);
    }
    
    // --- Test Case 2: Testing with int ---
    {
        Stapel<int> int_stack;
        run_stapel_test("Integer Type Stack (LIFO) - shared_ptr", int_stack);
    }

    std::cout << "\n========================================\n";
    std::cout << "All tests finished. Check output above for PASS/FAIL status!\n";
    std::cout << "========================================\n";
    
    return 0;
}
