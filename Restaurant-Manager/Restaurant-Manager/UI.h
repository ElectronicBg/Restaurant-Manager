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
* Header: Manages user interface interactions
*
*/

#pragma once

#include "Menu.h"
#include "Orders.h"
#include "Turnover.h"
#include "Inventory.h"
#include "DateManager.h"
#include "Validator.h"

void runUI();

void waiterMenu(MenuItem menu[], int menuCount, Order orders[], int& orderCount, int& nextOrderId,
	Recipe recipes[], int& recipeCount, InventoryItem inventory[], int& inventoryCount,
	DailyTurnover turnovers[], int& turnoverCount, const char* currentDate);

void managerMenu(MenuItem menu[], int& menuCount, Order orders[], int& orderCount, int& nextOrderId,
	Recipe recipes[], int& recipeCount, InventoryItem inventory[], int& inventoryCount,
	DailyTurnover turnovers[], int& turnoverCount, char* currentDate);

void displayAllOptions(const char* userType);
