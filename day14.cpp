#include <iostream>
#include <string>
#include <vector>
#include <cmath>

std::string to_binary(long long a) {
    std::string s(36, '0');
    while (a > 0) {
        long long i = 1;
        while (i * 2 <= a) {
            i *= 2;
        }
        a -= i;
        s.at((s.size() - 1) - log2(static_cast<double>(i))) = '1';
    }
    return s;
}

std::vector<std::string> combo_x(std::string s) {
    int value_x = -1;
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == 'X') {
            value_x = i;
            break;
        }
    }

    std::vector<std::string> combos;
    if (value_x >= 0) {
        s.at(value_x) = '1';
        for (const std::string &combo : combo_x(s)) {
            combos.push_back(combo);
        }
        s.at(value_x) = '0';
        for (const std::string &combo : combo_x(s)) {
            combos.push_back(combo);
        }
    } else {
        combos.push_back(s);
    }

    return combos;
}

long long to_decimal(const std::string &s) {
    long long a = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == '1') {
            a += static_cast<long long>(pow(2, (s.size() - 1) - i));
        }
    }
    return a;
}

std::string apply_mask(std::string s, const std::string &mask) {
    for (int i = 0; i < mask.size(); i++) {
        if (mask.at(i) != '0') {
            s.at(i) = mask.at(i);
        }
    }

    return s;
}

const int NUMBER_OF_LINES = 551; // 551 lines of input

struct address {
    long long num = 0;
    long long pos = 0;
};

int main() {
    std::vector<address> mem;
    std::string next;
    std::string mask;
    for (int i = 0; i < NUMBER_OF_LINES; i++) {
        std::cout << i << std::endl;
        std::cin >> next;
        if (next == "mask") {
            std::cin.ignore(3);
            std::cin >> next;
            mask = next;
            continue;
        } else {
            std::string temp_s = apply_mask(to_binary(stoll(next.substr(4, next.size() - 5))), mask);
            std::vector<std::string> temp = combo_x(temp_s);
            std::cin.ignore(3);
            std::cin >> next;
            for (const std::string &s : temp) {
                address temp_a;
                temp_a.num = stoll(next);
                temp_a.pos = to_decimal(s);
                mem.push_back(temp_a);
            }
        }
    }


    unsigned long long sum = 0;
    std::vector<long long> seen;
    for (int i = mem.size() - 1; i >= 0; i--) {
        if (mem.at(i).num >= 0 && std::find(seen.begin(), seen.end(), mem.at(i).pos) == seen.end()) {
            sum += mem.at(i).num;
            seen.push_back(mem.at(i).pos);
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
