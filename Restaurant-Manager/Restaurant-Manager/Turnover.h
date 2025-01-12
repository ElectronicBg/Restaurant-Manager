#ifndef TURNOVER_H
#define TURNOVER_H


#define MAX_TURNOVERS 365
#define MAX_DATE_LENGTH 11

struct DailyTurnover {
    char date[MAX_DATE_LENGTH];
    double turnover;
};


int loadTurnover(const char* filename, DailyTurnover turnovers[], int maxTurnovers);

void saveTurnover(const char* filename, DailyTurnover turnovers[], int turnoverCount);

void displayDailyTurnover(DailyTurnover turnovers[], int turnoverCount, const char* date);

double getTurnoverForPeriod(DailyTurnover turnovers[], int turnoverCount, const char* startDate, const char* endDate);

double resetDailyTurnover(DailyTurnover turnovers[], int& turnoverCount, const char* date);

void generateDailyReport(DailyTurnover turnovers[], int& turnoverCount, const char* date);

void displayTurnoverFromDate(DailyTurnover turnovers[], int turnoverCount, const char* startDate);

#endif


