#include <iostream>
#include <string>
#include <vector>



int main() {
    std::string line;
    std::string entry;
    const std::vector<std::string> expected_fields =    {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    std::vector<bool> fields_exist =                    {false, false, false, false, false, false, false};
    int count = 0;

    bool accurate;
    std::string color;
    for (int a = 0; a < 300; a++) {
        for (int b = 0 ; b < 300 ; b++) {
            if (std::cin.peek() == '\n') {
                std::cin.ignore(1);
                if (std::cin.peek() == '\n') {
                    break;
                }
            }
            std::cin >> entry;
            for (int i = 0; i < 7; i++) {
                if (entry.length() >= 3 && expected_fields.at(i) == entry.substr(0, 3)) {
                    switch (i) {
                        case 0:
                            if (stol(entry.substr(4)) >= 1920 && stol(entry.substr(4)) <= 2002) {
                                fields_exist.at(i) = true;
                            }
                            break;
                        case 1:
                            if (stol(entry.substr(4)) >= 2010 && stol(entry.substr(4)) <= 2020) {
                                fields_exist.at(i) = true;
                            }
                            break;
                        case 2:
                            if (stol(entry.substr(4)) >= 2020 && stol(entry.substr(4)) <= 2030) {
                                fields_exist.at(i) = true;
                            }
                            break;
                        case 3:
                            if (entry.substr(entry.length() - 2) == "cm") {
                                if (stol(entry.substr(4, entry.length() - 6)) >= 150 &&
                                    stol(entry.substr(4, entry.length() - 6)) <= 193) {
                                    fields_exist.at(i) = true;
                                }
                            } else if (entry.substr(entry.length() - 2) == "in") {
                                if (stol(entry.substr(4, entry.length() - 6)) >= 59 &&
                                    stol(entry.substr(4, entry.length() - 6)) <= 76) {
                                    fields_exist.at(i) = true;
                                }
                            }
                            break;
//                        pid:087499704 hgt:150cm ecl:grn iyr:2012 eyr:2030 byr:1980 hcl:#623a2f
                        case 4:
                            color = entry.substr(4);
                            accurate = true;
                            if (color.at(0) != '#') {
                                accurate = false;
                            }
                            for (int j = 1; j < color.length(); j++) {
                                if (!isdigit(color.at(j)) && (color.at(j) - 'a' < 0 || color.at(j) - 'a' > 5)) {
                                    accurate = false;
                                }
                            }
                            if (accurate) {
                                fields_exist.at(i) = true;
                            }
                            break;
                        case 5:
                            if (entry.substr(4) == "amb" || entry.substr(4) == "blu" || entry.substr(4) == "brn" || entry.substr(4) == "gry" || entry.substr(4) == "grn" || entry.substr(4) == "hzl" || entry.substr(4) == "oth") {
                                fields_exist.at(i) = true;
                            }
                            break;
                        case 6:
                            accurate = true;
                            if (entry.length() != 13) {
                                accurate = false;
                                break;
                            }
                            for (int j = 4; j < 13; j++) {
                                if (!isdigit(entry.at(j))) {
                                    accurate = false;
                                }
                            }
                            if (accurate) {
                                fields_exist.at(i) = true;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        std::cin.ignore(1);

        int temp = 0;
        for (int i = 0; i < 7; i++) {
            if (fields_exist.at(i)) {
                temp++;
            }
            fields_exist.at(i) = false;
        }
        if (temp == 7) {
            count++;
        }
    }
}
