#ifndef TURNOVER_H
#define TURNOVER_H

#include "Orders.h"
#include "Globals.h"

struct DailyTurnover {
    char date[MAX_DATE_LENGTH];
    double turnover;
};


int loadTurnover(const char* filename, DailyTurnover turnovers[], int maxTurnovers);

void saveTurnover(const char* filename, DailyTurnover turnovers[], int turnoverCount);

void displayDailyTurnover(Order orders[], int orderCount, const char* date);

double getTurnoverForPeriod(DailyTurnover turnovers[], int turnoverCount, const char* startDate, const char* endDate);

double resetDailyTurnover(DailyTurnover turnovers[], int& turnoverCount, const char* date);

double generateDailyReport(DailyTurnover turnovers[], int& turnoverCount, char* currentDate,
    Order orders[], int orderCount, const char* filename);

void displayTurnoverFromDate(DailyTurnover turnovers[], int turnoverCount, const char* startDate);

#endif


