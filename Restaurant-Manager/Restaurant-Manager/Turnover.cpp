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
* Header: Manages daily turnover reports
*
*/

#include "Turnover.h"

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int loadTurnover(const char* filename, DailyTurnover turnovers[], int maxTurnovers) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Turnover file \"" << filename << "\" not found. Creating a new file.\n";

        ofstream newFile(filename);
        newFile.close();

        return 0;
    }

    int count = 0;

    while (file.getline(turnovers[count].date, MAX_DATE_LENGTH, ',') && file >> turnovers[count].turnover) {
        file.ignore();
        count++;
        if (count >= maxTurnovers) 
            break;
    }

    file.close();

    return count;
}

void saveTurnover(const char* filename, DailyTurnover turnovers[], int turnoverCount) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Unable to open file " << filename << " for saving turnover.\n";

        return;
    }
    for (int i = 0; i < turnoverCount; i++) {
        file << turnovers[i].date << "," << turnovers[i].turnover << "\n";
    }
    file.close();
}

void displayDailyTurnover(Order orders[], int orderCount, const char* date) {
    double totalTurnover = 0.0;

    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].date, date) == 0) {
            totalTurnover += orders[i].totalPrice;
        }
    }

    cout << "Turnover for " << date << ": " << totalTurnover << " BGN\n";
}

double getTurnoverForPeriod(DailyTurnover turnovers[], int turnoverCount, const char* startDate, const char* endDate) {
    double total = 0.0;

    for (int i = 0; i < turnoverCount; i++) {
        if (strcmp(turnovers[i].date, startDate) >= 0 && strcmp(turnovers[i].date, endDate) <= 0) {
            total += turnovers[i].turnover;
        }
    }
    return total;
}

double resetDailyTurnover(DailyTurnover turnovers[], int& turnoverCount, const char* date) {
    for (int i = 0; i < turnoverCount; i++) {
        if (strcmp(turnovers[i].date, date) == 0) {
            double dailyTurnover = turnovers[i].turnover;

            turnovers[i].turnover = 0.0; 

            return dailyTurnover;
        }
    }
    cout << "No turnover found for date: " << date << "\n";

    return 0.0;
}

double generateDailyReport(DailyTurnover turnovers[], int& turnoverCount, char* currentDate,
    Order orders[], int orderCount, const char* filename) {
    double dailyTurnover = 0.0;

    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].date, currentDate) == 0) {
            dailyTurnover += orders[i].totalPrice;
        }
    }

    bool found = false;
    for (int i = 0; i < turnoverCount; i++) {
        if (strcmp(turnovers[i].date, currentDate) == 0) {
            turnovers[i].turnover = dailyTurnover;
            found = true;

            break;
        }
    }

    if (!found && turnoverCount < MAX_TURNOVERS) {
        strcpy_s(turnovers[turnoverCount].date, MAX_DATE_LENGTH, currentDate);
        turnovers[turnoverCount].turnover = dailyTurnover;
        turnoverCount++;
    }

    saveTurnover(filename, turnovers, turnoverCount);

    if (dailyTurnover > 0.0) {
        cout << "Daily report for " << currentDate << ": " << dailyTurnover << " BGN\n";
    }
    else {
        cout << "No orders found for " << currentDate << ".\n";
    }

    incrementDate(currentDate);

    saveCurrentDate(currentDate, "current_date.txt");

    cout << "New working date set to: " << currentDate << endl;

    return dailyTurnover;
}

void displayTurnoverFromDate(DailyTurnover turnovers[], int turnoverCount, const char* startDate) {
    double total = getTurnoverForPeriod(turnovers, turnoverCount, startDate, "9999-12-31");
    cout << "Total turnover from " << startDate << " to today: " << total << " BGN\n";

    cout << "\nTurnover details:\n";
    for (int i = 0; i < turnoverCount; i++) {
        if (strcmp(turnovers[i].date, startDate) >= 0) {
            cout << turnovers[i].date << ": " << turnovers[i].turnover << " BGN\n";
        }
    }
}
