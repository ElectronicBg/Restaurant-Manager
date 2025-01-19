#pragma once
#include "Constants.h"

struct InventoryItem {
    char name[MAX_NAME_LENGTH];
    int quantity;               
};

int loadInventory(const char* filename, InventoryItem inventory[], int maxItems);

void saveInventory(const char* filename, InventoryItem inventory[], int itemCount);

bool deductFromInventory(InventoryItem inventory[], int itemCount, const char* productName, int quantity);

bool addToInventory(InventoryItem inventory[], int& itemCount, const char* productName, int quantity);

bool removeFromInventory(InventoryItem inventory[], int& itemCount, const char* productName);

void displayInventory(const InventoryItem inventory[], int itemCount);

