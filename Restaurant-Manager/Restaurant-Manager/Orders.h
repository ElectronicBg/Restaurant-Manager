#ifndef ORDERS_H
#define ORDERS_H

#include "Menu.h"
#include "Recipe.h" 
#include "Inventory.h"
#include "Globals.h"

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

void displayOrders(const Order orders[], int orderCount);

void displaySortedOrders(const Order orders[], int orderCount);

int countOrdersForItem(const Order orders[], int orderCount, const char* itemName);

#endif
