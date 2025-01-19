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
* Header: Handles date tracking and incrementation
*
*/

#include "DateManager.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void loadCurrentDate(char* date, const char* filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "No date file found. Initializing to 2025-01-01.\n";

        strcpy_s(date, MAX_DATE_LENGTH, "2025-01-01");
        saveCurrentDate(date, filename); 

        return;
    }


    file.getline(date, MAX_DATE_LENGTH);


    if (strlen(date) != 10) {
        cout << "Invalid date format in file. Resetting to 2025-01-01.\n";

        strcpy_s(date, MAX_DATE_LENGTH, "2025-01-01");
        saveCurrentDate(date, filename);
    }

    file.close();
}

void saveCurrentDate(const char* date, const char* filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error saving date to file: " << filename << endl;

        return;
    }
    file << date;
    file.close();
}

void incrementDate(char* date) {
    int year, month, day;

    year = (date[0] - '0') * 1000 + (date[1] - '0') * 100 + (date[2] - '0') * 10 + (date[3] - '0');
    month = (date[5] - '0') * 10 + (date[6] - '0');
    day = (date[8] - '0') * 10 + (date[9] - '0');

    day++;

    bool monthOverflow = false;
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31) {
        monthOverflow = true;
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        monthOverflow = true;
    }
    else if (month == 2) { 
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) {
            monthOverflow = true;
        }
    }

    if (monthOverflow) {
        day = 1;
        month++;

        if (month > 12) {
            month = 1;
            year++;
        }
    }

    date[0] = (year / 1000) + '0';
    date[1] = ((year / 100) % 10) + '0';
    date[2] = ((year / 10) % 10) + '0';
    date[3] = (year % 10) + '0';

    date[4] = '-';

    date[5] = (month / 10) + '0';
    date[6] = (month % 10) + '0';

    date[7] = '-';

    date[8] = (day / 10) + '0';
    date[9] = (day % 10) + '0';

    date[10] = '\0';
}