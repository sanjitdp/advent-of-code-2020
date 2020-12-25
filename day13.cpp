#include <iostream>
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

std::vector<cpp_int> take_input();

struct linear_combination {
    cpp_int quotient = 0;
    cpp_int x = 0;
    cpp_int y = 0;
};

void euclidean_gcd(cpp_int a, cpp_int b, std::vector<linear_combination> &combinations);

cpp_int
solve_congruence_system(cpp_int a, cpp_int m, cpp_int b, cpp_int n);

int main() {
    std::vector<cpp_int> input = take_input();

    cpp_int x = 0;
    cpp_int product = 1;
    std::cout << input.size() << std::endl;

    for (int i = 0; i < input.size(); i++) {
        std::cout << i << std::endl;
        cpp_int &m = input.at(i);
        x = solve_congruence_system(x, product, m - i, m);
        product *= m;
        while (x > product) {
            x -= product;
        }
        while (x < 0) {
            x += product;
        }
        std::cout << x % 17 << std::endl;
    }

    std::cout << x << std::endl;

//    100 - 6 * 15 = 10
//    15 - 1 * (100 - 6 * 15) = 5
//    15 + 6 * 15
    return 0;
}

void euclidean_gcd(cpp_int a, cpp_int b, std::vector<linear_combination> &combinations) {
    if (b % a == 0) {
        return;
    } else {
        linear_combination temp;
        temp.quotient = b / a;
        if (combinations.empty()) {
            temp.x = -temp.quotient;
            temp.y = 1;
        } else if (combinations.size() == 1) {
            temp.x = 1 + combinations.at(0).quotient * temp.quotient;
            temp.y = -temp.quotient;
        } else {
            temp.x = combinations.at(combinations.size() - 2).x -
                     temp.quotient * (combinations.at(combinations.size() - 1).x);
            temp.y = combinations.at(combinations.size() - 2).y -
                     temp.quotient * (combinations.at(combinations.size() - 1).y);
        }
        combinations.push_back(temp);
        euclidean_gcd(b % a, a, combinations);
        return;
    }
}

cpp_int solve_congruence_system(cpp_int a, cpp_int m, cpp_int b, cpp_int n) {

    std::vector<linear_combination> combinations;
    euclidean_gcd(m, n, combinations);

    cpp_int s = 0;
    cpp_int t = 0;
    if (!combinations.empty()) {
        s = combinations.at(combinations.size() - 1).x;
        t = combinations.at(combinations.size() - 1).y;
    }

    cpp_int x = b;
    while (x > m * n) {
        x -= m * n;
    }
    x *= m;
    while (x > m * n) {
        x -= m * n;
    }
    x *= s;
    while (x > m * n) {
        x -= m * n;
    }

    cpp_int y = a;
    while (y > m * n) {
        y -= m * n;
    }
    y *= n;
    while (y > m * n) {
        y -= m * n;
    }
    y *= t;
    y -= (y - m * n) / (m * n) * (m * n);
    while (y > m * n) {
        y -= m * n;
    }

    cpp_int z = x + y;
    while (z < 0) {
        z += m * n;
    }

    return x + y;
}

std::vector<cpp_int> take_input() {
    std::string line;
    std::string number;
    std::vector<cpp_int> numbers;
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, line);

    for (char c : line) {
        if (c != ',') {
            number.append(1, c);
        } else {
            if (number == "x") {
                numbers.push_back(1);
            } else {
                numbers.push_back(stoi(number));
            }
            number = "";
        }
    }

    if (number == "x") {
        numbers.push_back(1);
    } else {
        numbers.push_back(stoi(number));
    }

    return numbers;
}

// 5 = 1 * 3 + 2
// 3 = 1 * 2 + 1
// 2 = 1 * 1 + 1
// 1 = 1 * 1