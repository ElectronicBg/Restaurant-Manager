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
* Header: Manages order processing
*
*/

#pragma once

#include "Menu.h"
#include "Recipe.h" 
#include "Inventory.h"
#include "Constants.h"

struct Order {
    int orderId;
    char date[MAX_DATE_LENGTH];
    char itemName[MAX_NAME_LENGTH];
    int quantity;
    double totalPrice;
};

int loadOrders(const char* filename, Order orders[], int maxOrders);

void saveOrders(const char* filename, Order orders[], int orderCount);

bool addOrder(Order orders[], int& orderCount, int& nextOrderId, const char* date,
    const char* itemName, int quantity, MenuItem menu[], int menuCount,
    Recipe recipes[], int recipeCount, InventoryItem inventory[], int inventoryCount);

bool cancelOrder(Order orders[], int& orderCount, int orderId, const char* currentDate);

void displayOrders(const Order orders[], int orderCount);

void displaySortedOrders(const Order orders[], int orderCount);

int countOrdersForItemToday(const Order orders[], int orderCount, const char* currentDate, const char* itemName);
