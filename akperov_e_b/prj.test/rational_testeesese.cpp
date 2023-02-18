#include <rational/rational.hpp>
#include <iostream>

void testInput(const std::string& str)
{
    try {
        std::istringstream istrm(str);
        std::cout << "Trying to make " << str << " -> ";
        Rational z;
        istrm >> z;
        std::cout << "Read Success: " << z << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void TestMathOp(
    const Rational& lhs,
    const Rational& rhs,
    const Rational& res,
    const std::string& op_str
) {
    std::cout << lhs << " " << op_str << " " << rhs << 
        "->" << res << std::endl;
}

void TestMathOp(
    const Rational& lhs,
    const int& rhs,
    const Rational& res,
    const std::string& op_str
) {
    std::cout << lhs << " " << op_str << "  " << rhs <<
        " ->" << res << std::endl;
}

void TestMathOp(
    const int& lhs,
    const Rational& rhs,
    const Rational& res,
    const std::string& op_str
) {
    std::cout << " " << lhs << "  " << op_str << " " << rhs <<
        "->" << res << std::endl;
}

void TestLogicOp(
    const Rational& lhs,
    const Rational& rhs,
    const bool& res,
    const std::string& op_str
) {
    std::cout  << lhs << " " << op_str << " " << rhs <<
        " -> " << res << std::endl;
}

void TestLogicOp(
    const Rational& lhs,
    const int32_t& rhs,
    const bool& res,
    const std::string& op_str
) {
    std::cout << lhs << " " << op_str << " " << rhs <<
        " -> " << res << std::endl;
}

int main() {
    std::cout << "Checking Math Operator +" << std::endl;
    Rational x(2, 3);
    Rational y(1, 2);
    TestMathOp(x, y, x + y, "+");
    x = Rational(5, 2);
    TestMathOp(x, y, x + y, "+");
    TestMathOp(x, 2, x + 2, "+");
    TestMathOp(2, x, 2 + x, "+");

    std::cout << "\nChecking Math Operator -" << std::endl;
    x=Rational(2, 3);
    TestMathOp(x, y, x - y, "-");
    x = Rational(5, 2);
    TestMathOp(x, y, x - y, "-");
    TestMathOp(x, 2, x - 2, "-");
    TestMathOp(2, x, 2 - x, "-");

    std::cout << "\nChecking Math Operator *" << std::endl;
    x = Rational(2, 3);
    TestMathOp(x, y, x * y, "*");
    x = Rational(5, 2);
    TestMathOp(x, y, x * y, "*");
    TestMathOp(x, 2, x * 2, "*");
    TestMathOp(2, x, 2 * x, "*");

    std::cout << "\nChecking Math Operator /" << std::endl;
    x = Rational(2, 3);
    TestMathOp(x, y, x / y, "/");
    x = Rational(5, 2);
    TestMathOp(x, y, x / y, "/");
    TestMathOp(x, 2, x / 2, "/");
    TestMathOp(2, x, 2 / x, "/");

    std::cout << "\nChecking Math Operator +=" << std::endl;
    x = Rational(2, 3);
    std::cout << x << " += " << y << " -> ";
    x += y;
    std::cout << x << std::endl;
    std::cout << x << " += " << 1 << " -> ";
    x += 1;
    std::cout << x << std::endl;

    std::cout << "\nChecking Math Operator -=" << std::endl;
    x = Rational(2, 3);
    std::cout << x << " -= " << y << " -> ";
    x -= y;
    std::cout << x << std::endl;
    std::cout << x << " -= " << 1 << " -> ";
    x -= 1;
    std::cout << x << std::endl;

    std::cout << "\nChecking Math Operator *=" << std::endl;
    x = Rational(2, 3);
    std::cout << x << " *= " << y << " -> ";
    x *= y;
    std::cout << x << std::endl;
    std::cout << x << " *= " << 3 << " -> ";
    x *= 3;
    std::cout << x << std::endl;

    std::cout << "\nChecking Math Operator /=" << std::endl;
    x = Rational(2, 3);
    std::cout << x << " /= " << y << " -> ";
    x /= y;
    std::cout << x << std::endl;
    std::cout << x << " /= " << 2 << " -> ";
    x *= 2;
    std::cout << x << std::endl;

    std::cout << "\nChecking Math Operator -" << std::endl;
    x = Rational(2, 3);
    std::cout << "- " << x << " -> " << -x << std::endl;

    std::cout << "\nChecking Math Operator --" << std::endl;
    x = Rational(2, 3);
    std::cout << x << " --    -> ";
    std::cout << x-- << std::endl;

    std::cout << "\nChecking Math Operator ++" << std::endl;
    x = Rational(2, 3);
    std::cout << x << " ++    -> ";
    std::cout << x++ << std::endl;

    std::cout << "\nChecking Logic Operator >" << std::endl;
    x = Rational(2, 3);
    TestLogicOp(x, y, x > y, ">");
    TestLogicOp(y, x, y > x, ">");
    TestLogicOp(x * 2, 1, x*2 > 1, ">");

    std::cout << "\nChecking Logic Operator <" << std::endl;
    x = Rational(2, 3);
    TestLogicOp(x, y, x < y, "<");
    TestLogicOp(y, x, y < x, "<");
    TestLogicOp(x * 2, 1, x * 2 < 1, "<");
        
    std::cout << "\nChecking Logic Operator >=" << std::endl;
    x = Rational(2, 3);
    TestLogicOp(x, y, x >= y, ">=");
    TestLogicOp(y, x, y >= x, ">=");
    TestLogicOp(x, x, x >= x, ">=");
    TestLogicOp(x , 1, x  >= 1, ">=");

    std::cout << "\nChecking Logic Operator <=" << std::endl;
    x = Rational(2, 3);
    TestLogicOp(x, y, x <= y, "<=");
    TestLogicOp(y, x, y <= x, "<=");
    TestLogicOp(y, y, y <= y, "<=");
    TestLogicOp(x , 1, x  <= 1, "<=");

    std::cout << "\nChecking Logic Operator !=" << std::endl;
    x = Rational(2, 3);
    TestLogicOp(x, y, x != y, "!=");
    TestLogicOp(y, y, y != y, "!=");
    TestLogicOp(Rational(4,2), 2, Rational(2, 1) != 2, "!=");

    std::cout << "\nChecking Logic Operator ==" << std::endl;
    x = Rational(2, 3);
    TestLogicOp(x, y, x == y, "==");
    TestLogicOp(y, y, y == y, "==");
    TestLogicOp(Rational(4, 2), 2, Rational(2, 1) == 2, "==");
     
    std::cout << "\nChecking Dividing by 0 " << std::endl;
    try {      
        x = Rational(2, 3);
        std::cout << x << " / " << 0 << " -> ";
        std::cout<< x / 0;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        x = Rational(2, 3);
        std::cout << x << " / " << Rational(0, 5) << " -> ";
        std::cout << x / Rational(0, 5);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try { 
        x = Rational(2, 3);
        std::cout << x << " /= " << Rational(0,3) << " -> ";
        x /= Rational(0,3);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        x = Rational(2, 3);
        std::cout << x << " /= " << 0 << " -> ";
        x /= 0;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    testInput("5/0");

    std::cout << "\nChecking Input " << std::endl;
    std::cout << "Incorrect format:" << std::endl;
    testInput("k/3");
    testInput("5/k");
    testInput("5/k");
    testInput("k/k");
    testInput("5|7");
    testInput("5/7kk");
    testInput("5");
    testInput("kk5/7");
    testInput("5/-7");
    std::cout << "Correct reading:" << std::endl;
    testInput("5/8");
    testInput("3/7");
    std::cout << "Correct reducing and special situations:" << std::endl;
    testInput("0/9");
    testInput("8/10");
    testInput("25/5");
}