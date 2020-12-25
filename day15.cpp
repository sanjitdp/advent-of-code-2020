#include <iostream>
#include <vector>

const long long NUM_INPUTS = 6;

struct element {
    long long num = 0;
    long long pos = 0;
};

int main() {
    // declarations
    std::vector<long long> starting_numbers(NUM_INPUTS);
    std::vector<element> sequence;

    // take input
    for (long long i = 0; i < NUM_INPUTS - 1; i++) {
        std::cin >> starting_numbers.at(i);
        std::cin.ignore(1);
    }
    std::cin >> starting_numbers.at(NUM_INPUTS - 1);

    // solution
    for (long long i = 0; i < NUM_INPUTS; i++) {
        element e;
        e.num = starting_numbers.at(i);
        e.pos = i;
        sequence.push_back(e);
    }

    long long previous_num = sequence.at(NUM_INPUTS - 1).num;
    for (long long i = NUM_INPUTS; i < 30000000; i++) {
        long long prev_pos = -1;
        long long found = 0;
        for (int j = 0; j < sequence.size(); j++) {
            element &elem = sequence.at(j);
            if (elem.pos != (i - 1) && elem.num == previous_num) {
                prev_pos = (i - 1) - elem.pos;
                found = j;
                break;
            }
        }

        if (prev_pos > 0) {
            sequence.at(found).num = prev_pos;
            sequence.at(found).pos = i;
            previous_num = sequence.at(found).num;
        } else {
            element temp;
            temp.num = 0;
            temp.pos = i;
            previous_num = temp.num;
            sequence.push_back(temp);
        }

        std::cout << i << " " << previous_num << std::endl;
    }

    return 0;
}
