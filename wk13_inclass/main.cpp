#include <iostream>
#include <numeric>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Constructor
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) {
            std::cerr << "Error: Denominator cannot be zero. Setting to 1." << std::endl;
            this->denominator = 1;
        }
    }

    // Member function overloads (Task 2, Task 4):

    // Task 2: Compound assignment: F1 += F2
    // Must return Fraction& to allow chaining (F1 += F2 += F3)
    Fraction& operator+=(const Fraction& rhs) {
        /*

         Fill in the blank here.

         */
        int denom = this->denominator * rhs.denominator;
        int num = this->numerator * rhs.denominator + rhs.numerator * this->denominator;
        int g = std::gcd(denom, num);
        this->denominator = denom/g;
        this->numerator = num/g;
        return *this;
    }

    // Task 4: Prefix increment: ++F
    // Must return Fraction& and take no explicit parameters
    Fraction& operator++() {
        /*

         Fill in the blank here.

         */
        if(this->denominator>0) this->numerator+=this->denominator;
        else this->numerator-=this->denominator;
        return *this;
    }

    // Friend function declarations (required for non-member operators)

    // Task 1: Binary addition: F1 + F2
    /* Complete the declaration here. */
    friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);

    // Task 3: Output stream: std::cout << F1
    /* Complete the declaration here. */
    friend std::ostream& operator<<(std::ostream& os, const Fraction& rhs);

};

// Non-member function definitions:

// Task 1: Binary addition: F1 + F2
// Returns a new Fraction object by value (T)
Fraction operator+ (const Fraction& lhs, const Fraction& rhs) {
    /*

     Fill in the blank here.

     */
    Fraction temp(lhs);
    temp += rhs;
    return temp;
}

// Task 3: Output stream: std::cout << F1
// Returns std::ostream& to allow chaining (cout << f1 << f2)
std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    /*

     Fill in the blank here.

     */
    os << f.numerator << "/" << f.denominator;
    return os;
}


// Main function
int main() {
    Fraction f1(1, 2);  // 1/2
    Fraction f2(3, 4);  // 3/4
    Fraction f3(1, 1);  // 1

    std::cout << "Given fractions:" << std::endl;
    std::cout << "   f1 = " << f1 << std::endl;
    std::cout << "   f2 = " << f2 << std::endl;
    std::cout << "   f3 = " << f3 << std::endl;

    // Task 1. Binary addition (+)
    Fraction f_sum = f1 + f2;
    std::cout << "Task 1: Binary addition (f1 + f2):" << std::endl;
    std::cout << "   " << f1 << " + " << f2 << " = " << f_sum << " (Expected result: 10/8 or 5/4)" << std::endl;

    // Task 2: Compound assignment (+=)
    f3 += f1; // F3 is now 1 + 1/2 = 3/2
    std::cout << "Task 2: Compound assignment (f3 += f1):" << std::endl;
    std::cout << "   f3 is: " << f3 << " (Expected result: 3/2)" << std::endl;

    Fraction f4(1, 8);
    f3 += (f4 += Fraction(1, 8)); // f4 becomes 2/8, then f3 adds 2/8 (3/2 + 2/8 = 14/8)
    std::cout << "   Chaining operation works! f3 += (f4 += 1/8) -> f3 is now: " << f3 << std::endl;

    // Task 4: Prefix increment (++)
    std::cout << "Task 4: Prefix increment (++f2):" << std::endl;
    std::cout << "   ++f2 is: " << ++f2 << std::endl; // F2 is now 3/4 + 1 = 7/4
    std::cout << "   f2 value after: " << f2 << std::endl;

    return 0;
}
