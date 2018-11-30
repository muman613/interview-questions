/**
 * RPN Calculator exercise solution by Michael Uman (Question by Nutanix)
 */

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <exception>
#include <algorithm>

using namespace std;

using string_vec = vector<string>;

/**
 * Exception class thrown by RPN calculator class on invalid input.
 */
class InvalidInput : public exception {
public:
    InvalidInput() = default;
    explicit InvalidInput(const string & error)  {
        err = error;
    }
    const char *what() const noexcept override {
        return err.c_str();
    }

    string err = "InvalidInput";
};

/**
 * Calculator class performs RPN operation on input strings.
 */
class rpnCalculator {
public:
    int calculate(const string_vec & input_vec);
    void clear() {
        clear_stack();
    }
private:
    static bool is_number(const string &s);
    void clear_stack();
    stack<int> dataStack;
};

/**
 * Check if the input string is a numeric value
 * @param s input string
 * @return true if the value represents a number
 */
bool rpnCalculator::is_number(const string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}


void rpnCalculator::clear_stack() {
    for (int x = 0 ; x < dataStack.size() ; x++) {
        dataStack.pop();
    }
}
/**
 * Perform the calculation on the input string vector
 * @param input_vec
 * @return
 */
int rpnCalculator::calculate(const string_vec &input_vec) {
    int n = (dataStack.empty())?1:0;

    if (input_vec.size() < 2 + n) {
        cerr << "ERROR: Invalid input" << endl;
        throw InvalidInput();
    }

    for (auto const & value : input_vec) {
        // is this an arithmetic operator
        if ((value == "+") || (value == "-") || (value == "*") || (value == "/")) {
            // Make sure there are at least two values on the stack for a binary operator
            if (dataStack.size() < 2) {
                cerr << "ERROR: Not enough data on the stack" << endl;
                throw InvalidInput();
            }

            char op = value[0];
            int a = dataStack.top();
            dataStack.pop();
            int b = dataStack.top();
            dataStack.pop();
            int result = 0;

            switch (op) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = b / a;
                    break;
                default:
                    // should never happen
                    break;
            }

            dataStack.push(result);
        } else {
            if (is_number(value)) {
                dataStack.push(std::stoi(value));
            } else {
                throw InvalidInput("Non-numeric or non-operator token found");
            }
        }
    }

    if (dataStack.size() != 1) {
        cerr << "ERROR: Calculation is incomplete" << endl;
        throw InvalidInput("Calculation is incomplete");
    }

    return dataStack.top();
}

int main() {
    rpnCalculator calc;
    string_vec  input;
    int result = 0;

    // For the input "4", "3", "3", "+", "*" the output should be
    // (3 + 3) * 4 => 6 * 4 => 24

    input = { "4", "3", "3", "+", "*" };
    result = calc.calculate(input);
    cout << "The result of the calculation is " << result << endl;

    // Now add to the result of the previous calculation
    result = calc.calculate({ "2", "/"});
    cout << "The result of the calculation is " << result << endl;

    // For the input "4", "3", "*", "2", "+" the output should be
    // (4 * 3) + 2 => 12 * 2 => 14

    calc.clear();
    input = { "4", "3", "*", "2", "+" };
    result = calc.calculate(input);
    cout << "The result of the calculation is " << result << endl;

    // Now add a non-numeric/non-operator string to the input vector and rerun calculate,
    // this time the calculate function will throw an exception.

    try {
        input.push_back("X");
        result = calc.calculate(input);
        cout << "The result of the calculation is " << result << endl;

    }
    catch (const InvalidInput &ex) {
        cerr << "Caught exception : " << ex.what() << endl;
    }

    return 0;
}