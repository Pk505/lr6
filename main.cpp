#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "header.h"

struct school {
    std::string city;
    unsigned int number;
    std::string specialization;
    unsigned int student_number;
};

int main(int argc, char *argv[]) {
    std::string mode_1 = argv[1];
    std::string mode_2 = argv[2];
    std::string file_name = argv[3];
    if (mode_1 == "write") {
        std::ofstream file;
        unsigned int amount = 0;
        std::cout << "Enter the number of schools: " << std::endl;
        std::cin >> amount;
        std::vector<school> school_base(amount);
        for (int i = 0; i < amount; i++) {
            std::cout << "Enter the city of school # " << i << std::endl;
            std::cin.ignore();
            std::getline(std::cin, school_base[i].city);
            std::cout << "Enter the number of school # " << i << std::endl;
            std::cin >> school_base[i].number;
            std::cout << "Enter the specialization of school # " << i << std::endl;
            std::cin.ignore();
            std::getline(std::cin, school_base[i].specialization);
            std::cout << "Enter the number of students in school # " << i << std::endl;
            std::cin >> school_base[i].student_number;
        }
        if (mode_2 == "text") {
            file.open(file_name, std::ios::app);
            for (school const &element: school_base) {
                file << element.city << ' '
                     << element.number << ' '
                     << element.specialization << ' '
                     << element.student_number << std::endl;
            }
        } else if (mode_2 == "binary") {
            file.open(file_name, std::ios::binary | std::ios::app);
            for (school const &element: school_base) {
                unsigned int city_length = element.city.size();
                file.write((char *) &city_length, sizeof city_length);
                for (char const &letter: element.city)
                    file.write((char *) &letter, sizeof letter);
                file.write((char *) &element.number, sizeof element.number);
                unsigned int specialization_length = element.specialization.size();
                file.write((char *) &specialization_length, sizeof specialization_length);
                for (char const &letter: element.specialization)
                    file.write((char *) &letter, sizeof letter);
                file.write((char *) &element.student_number, sizeof element.student_number);
            }
        }
        file.close();
    } else if (mode_1 == "read") {
        std::ifstream file;
        if (mode_2 == "text") {
            file.open(file_name);
            std::vector<school> school_base;
            while (true) {
                school new_school;
                file >> new_school.city;
                file >> new_school.number;
                file >> new_school.specialization;
                file >> new_school.student_number;
                if (!file)
                    break;
                school_base.push_back(new_school);
            }
            for (school const &element: school_base) {
                std::cout << element.city << ' '
                          << element.number << ' '
                          << element.specialization << ' '
                          << element.student_number << std::endl;
            }
        } else if (mode_2 == "binary") {
            file.open(file_name, std::ios::binary);
            std::vector<school> school_base;
            while (true) {
                school new_school;
                std::string new_school_city;
                unsigned int city_length = 0;
                file.read((char *) &city_length, sizeof city_length);
                char letter;
                for (int i = 0; i < city_length; i++) {
                    file.read((char *) &letter, sizeof letter);
                    new_school_city.push_back(letter);
                }
                new_school.city = new_school_city;
                file.read((char *) &new_school.number, sizeof new_school.number);
                unsigned int specialization_length = 0;
                std::string new_school_specialization;
                file.read((char *) &specialization_length, sizeof specialization_length);
                for (int i = 0; i < specialization_length; i++) {
                    file.read((char *) &letter, sizeof letter);
                    new_school_specialization.push_back(letter);
                }
                new_school.specialization = new_school_specialization;
                file.read((char *) &new_school.student_number, sizeof new_school.student_number);
                if (!file)
                    break;
                school_base.push_back(new_school);
            }
            for (school const &element: school_base) {
                std::cout << element.city << ' '
                          << element.number << ' '
                          << element.specialization << ' '
                          << element.student_number << std::endl;
            }
        }
        file.close();

    } else if (mode_1 == "clear") {
        std::ofstream file;
        if (mode_2 == "text") {
            file.open(file_name);
        } else if (mode_2 == "binary") {
            file.open(file_name, std::ios::binary);
        }
        std::cout << "file was cleared" << std::endl;
        file.close();
    }

    return 0;
}
