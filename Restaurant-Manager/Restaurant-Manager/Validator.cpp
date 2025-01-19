/**
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Emil Neshkov
* @idnumber 0MI0600506
* @compiler VC
*
* Header: Input validation functions
*
*/

#include "Validator.h"

#include <iostream>
#include <string>

using namespace std;

void validatePositiveInt(int& value, const char* prompt) {
    cout << prompt;
    cin >> value;

    while (cin.fail() || value <= 0) {
        cout << "Invalid input. " << prompt;
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> value;
    }
    cin.ignore(10000, '\n');
}

void validatePositiveDouble(double& value, const char* prompt) {
    cout << prompt;
    cin >> value;

    while (cin.fail() || value <= 0.0) {
        cout << "Invalid input. " << prompt;
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> value;
    }
    cin.ignore(10000, '\n');
}

void validateMenuOption(int& option) {
    cout << "Select an option: ";
    cin >> option;

    while (cin.fail() || option < MIN_OPTION || option > MAX_OPTION) {
        cout << "Invalid option. Please enter a number between " << MIN_OPTION << " and " << MAX_OPTION << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> option;
    }
    cin.ignore(10000, '\n');
}

void validateStringInput(char* input, int maxLength, const char* prompt) {
    cout << prompt;
    cin.getline(input, maxLength);

    while (strlen(input) == 0) {
        cout << "Invalid input. " << prompt;
        cin.getline(input, maxLength);
    }
}