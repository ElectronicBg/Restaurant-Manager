#pragma once

#include "Menu.h"
#include "Orders.h"
#include "Turnover.h"
#include "Inventory.h"

void runUI();

void waiterMenu(MenuItem menu[], int menuCount, Order orders[], int& orderCount, int& nextOrderId,
	Recipe recipes[], int& recipeCount, InventoryItem inventory[], int& inventoryCount,
	DailyTurnover turnovers[], int& turnoverCount, const char* currentDate);

void managerMenu(MenuItem menu[], int& menuCount, Order orders[], int& orderCount, int& nextOrderId,
	Recipe recipes[], int& recipeCount, InventoryItem inventory[], int& inventoryCount,
	DailyTurnover turnovers[], int& turnoverCount, char* currentDate);

void displayAllOptions(const char* userType);
