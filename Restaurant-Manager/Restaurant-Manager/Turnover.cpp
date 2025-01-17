#include "Turnover.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Orders.h"

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
        if (count >= maxTurnovers) break;
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

double generateDailyReport(DailyTurnover turnovers[], int& turnoverCount, const char* date,
    Order orders[], int orderCount) {
    double dailyTurnover = 0.0;

    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].date, date) == 0) {
            dailyTurnover += orders[i].totalPrice;
        }
    }

    bool found = false;
    for (int i = 0; i < turnoverCount; i++) {
        if (strcmp(turnovers[i].date, date) == 0) {
            turnovers[i].turnover = dailyTurnover;
            found = true;
            break;
        }
    }

    if (!found) {
        strcpy_s(turnovers[turnoverCount].date, date);
        turnovers[turnoverCount].turnover = dailyTurnover;
        turnoverCount++;
    }

    if (dailyTurnover > 0.0) {
        std::cout << "Daily report for " << date << ": " << dailyTurnover << " BGN\n";
    }
    else {
        std::cout << "No orders found for " << date << ".\n";
    }

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
