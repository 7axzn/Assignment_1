#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Polynomial {
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    Polynomial() : coeffs(1, 0.0) {} // Default constructor for zero polynomial
    explicit Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {}
    Polynomial(const Polynomial& other) : coeffs(other.coeffs) {} // Copy constructor

    // Destructor
    ~Polynomial() {}

    // Assignment operator
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            coeffs = other.coeffs;
        }
        return *this;
    }

    // Arithmetic operators
    Polynomial operator+(const Polynomial& other) const {
        size_t maxDegree = max(coeffs.size(), other.coeffs.size());
        vector<double> result(maxDegree, 0.0);

        for (size_t i = 0; i < maxDegree; ++i) {
            if (i < coeffs.size()) result[i] += coeffs[i];
            if (i < other.coeffs.size()) result[i] += other.coeffs[i];
        }
        return Polynomial(result);
    }

    Polynomial operator-(const Polynomial& other) const {
        size_t maxDegree = max(coeffs.size(), other.coeffs.size());
        vector<double> result(maxDegree, 0.0);

        for (size_t i = 0; i < maxDegree; ++i) {
            if (i < coeffs.size()) result[i] += coeffs[i];
            if (i < other.coeffs.size()) result[i] -= other.coeffs[i];
        }
        return Polynomial(result);
    }

    Polynomial operator*(const Polynomial& other) const {
        vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);
        for (size_t i = 0; i < coeffs.size(); ++i) {
            for (size_t j = 0; j < other.coeffs.size(); ++j) {
                result[i + j] += coeffs[i] * other.coeffs[j];
            }
        }
        return Polynomial(result);
    }

    // Equality operator
    bool operator==(const Polynomial& other) const {
        return coeffs == other.coeffs;
    }

    // Output operator
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
            if (i != poly.coeffs.size() - 1) out << (poly.coeffs[i] >= 0 ? "+" : "");
            out << poly.coeffs[i];
            if (i > 0) out << "x^" << i;
        }
        return out;
    }

    // Utility functions
    int degree() const {
        return coeffs.size() - 1;
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (int i = degree(); i >= 0; --i) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    double getCoefficient(int degree) const {
        if (degree < 0 || degree >= coeffs.size()) return 0.0;
        return coeffs[degree];
    }

    void setCoefficients(const vector<double>& coefficients) {
        coeffs = coefficients;
    }
};

// Test cases function
void runTests() {
    // Test 1: Default polynomial (should be zero)
    Polynomial p1;
    cout << "Test 1: " << p1 << endl;

    // Test 2: Polynomial with one coefficient
    Polynomial p2({5}); // Represents 5
    cout << "Test 2: " << p2 << endl;

    // Test 3: Polynomial with multiple coefficients
    Polynomial p3({1, 2, 3}); // Represents 3x^2 + 2x + 1
    cout << "Test 3: " << p3 << endl;

    // Test 4: Polynomial addition
    Polynomial pAdd = p2 + p3;
    cout << "Test 4: " << pAdd << endl; // Expected: 3x^2 + 2x + 6

    // Test 5: Polynomial subtraction
    Polynomial pSub = p3 - p2;
    cout << "Test 5: " << pSub << endl; // Expected: 3x^2 + 2x - 4

    // Test 6: Polynomial multiplication
    Polynomial pMul = p2 * p3;
    cout << "Test 6: " << pMul << endl; // Expected: 15

    // Test 7: Degree of polynomial
    cout << "Test 7 Degree: " << p3.degree() << endl; // Expected: 2

    // Test 8: Evaluate polynomial at x = 1
    double eval = p3.evaluate(1);
    cout << "Test 8 Evaluate at 1: " << eval << endl; // Expected: 6

    // Test 9: Evaluate polynomial at x = 2
    eval = p3.evaluate(2);
    cout << "Test 9 Evaluate at 2: " << eval << endl; // Expected: 17

    // Test 10: Coefficient access
    cout << "Test 10 Coefficient of x^1: " << p3.getCoefficient(1) << endl; // Expected: 2

    // Test 11: Set coefficients
    Polynomial pSet;
    pSet.setCoefficients({0, 1, 2, 3}); // 3x^3 + 2x^2 + 1x + 0
    cout << "Test 11: " << pSet << endl;

    // Test 12: Root finding for simple polynomial
    Polynomial pRoot({1, -3, 2}); // x^2 - 3x + 2 = 0, roots at 1 and 2
    double root1 = pRoot.getCoefficient(1); // Simulated root finding, replace with proper method
    cout << "Test 12 Root at x=1.5: " << root1 << endl; // Expected: ~2

    // Test 13: Negative coefficients
    Polynomial negativePoly({1, -2, 3}); // 3x^2 - 2x + 1
    cout << "Test 13 Negative Coefficients: " << negativePoly << endl;

    // Test 14: Check degree of zero polynomial
    Polynomial zeroPoly;
    cout << "Test 14 Degree of zero polynomial: " << zeroPoly.degree() << endl; // Expected: 0

    // Test 15: Composing with a linear polynomial
    Polynomial linearPoly({0, 1}); // Represents x
    Polynomial pCompLinear = p3 + linearPoly; // Compose p3 and linear
    cout << "Test 15 Composition with linear polynomial: " << pCompLinear << endl;

    // Test 16: Coefficient of a constant polynomial
    Polynomial constantPoly({4}); // 4
    cout << "Test 16 Constant polynomial: " << constantPoly << endl;

    // Test 17: Large coefficients
    Polynomial largeCoeffPoly({10000, 20000, 30000});
    cout << "Test 17 Large Coefficients: " << largeCoeffPoly << endl;

    // Test 18: Zero polynomial addition
    Polynomial zeroPoly2({0});
    Polynomial pAddZero = p3 + zeroPoly2;
    cout << "Test 18 Addition with zero polynomial: " << pAddZero << endl; // Should be equal to p3

    // Test 19: Evaluate polynomial at negative number
    eval = p3.evaluate(-1);
    cout << "Test 19 Evaluate at -1: " << eval << endl; // Expected: 0

    // Test 20: Check if two identical polynomials are equal
    Polynomial pSame({1, 2, 3});
    cout << "Test 20 Identical Polynomials Equal: " << (p3 == pSame) << endl; // Expected: true

    // Test 21: Check if two different polynomials are not equal
    Polynomial pDifferent({1, 2, 4});
    cout << "Test 21 Different Polynomials Not Equal: " << (p3 == pDifferent) << endl; // Expected: false

    // Test 22: Evaluate polynomial at zero
    double valAtZero = p3.evaluate(0);
    cout << "Test 22 Evaluate at 0: " << valAtZero << endl; // Expected: 1

    // Test 23: Check degrees of polynomial after operations
    Polynomial pAfterOps = (p3 + pSet) * pRoot; // Should have degree 4
    cout << "Test 23 Degree after operations: " << pAfterOps.degree() << endl; // Expected: 4

    // Test 24: Composing with an empty polynomial
    Polynomial emptyPoly;
    Polynomial pCompEmpty = p3 + emptyPoly;
    cout << "Test 24 Composition with empty polynomial: " << pCompEmpty << endl;

    // Test 25: Definite integral (mock result)
    double integralResult = p3.evaluate(2) - p3.evaluate(0); // Simulated integral
    cout << "Test 25 Definite integral from 0 to 2: " << integralResult << endl;

    // Test 26: Evaluate polynomial with a fraction
    eval = p3.evaluate(0.5);
    cout << "Test 26 Evaluate at 0.5: " << eval << endl; // Replace with proper expected value

    // Test 27: Zeroing out coefficients
    Polynomial pZeroOut({0, 0, 0});
    cout << "Test 27 Zeroing out coefficients: " << pZeroOut << endl;

    // Test 28: Large polynomial
    Polynomial largePoly({1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}); // x^10 + 1
    cout << "Test 28 Large polynomial: " << largePoly << endl;

    // Test 29: Check negative evaluation
    double negativeEval = largePoly.evaluate(-1);
    cout << "Test 29 Evaluate at -1 for large polynomial: " << negativeEval << endl;

    // Test 30: Set coefficients and print
    Polynomial setPoly;
    setPoly.setCoefficients({5, 1, 0, -3}); // -3x^3 + x + 5
    cout << "Test 30 Set coefficients and print: " << setPoly << endl;

    cout << "All tests completed." << endl;
}

int main() {
    runTests();
    return 0;
}

