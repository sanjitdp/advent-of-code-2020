#include <iostream>
#include <string>
#include <vector>

int binary_partition_col(int min, int max, const std::string& input) {
    for (char c : input.substr(7, 3)) {
        switch (c) {
            case 'L':
                max = (max + min) / 2;
                break;
            case 'R':
                min = (max + min) / 2 + 1;
                break;
            default:
                break;
        }
    }
    return max;
}

int binary_partition_row(int min, int max, const std::string& input) {
    for (char c : input.substr(0, 7)) {
        switch (c) {
            case 'F':
                max = (max + min) / 2;
                break;
            case 'B':
                min = (max + min) / 2 + 1;
                break;
            default:
                break;
        }
    }
    return max;
}

int main() {
    int seat_ID;
    std::string ticket;
    std::vector<int> boarding_passes(875, 0);

    for (int i = 0; i < 826; i++) {
        std::cin >> ticket;
        seat_ID = binary_partition_row(0, 127, ticket) * 8 + binary_partition_col(0, 7, ticket);
        if (seat_ID >= 0 && seat_ID <= 874)
            boarding_passes.at(seat_ID) = 1;
    }

    for (int i = 0; i < 874; i++) {
        if (boarding_passes.at(i) == 0) {
            std::cout << i << std::endl;
        }
    }

    return 0;
}