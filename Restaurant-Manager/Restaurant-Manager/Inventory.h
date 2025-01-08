#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_NAME_LENGTH 50
#define MAX_INVENTORY_ITEMS 100

// Структура за склада
struct InventoryItem {
    char name[MAX_NAME_LENGTH];
    int quantity;               
};

int loadInventory(const char* filename, InventoryItem inventory[], int maxItems);

void saveInventory(const char* filename, InventoryItem inventory[], int itemCount);

bool checkInventory(const InventoryItem inventory[], int itemCount, const char* productName, int requiredQuantity);

bool deductFromInventory(InventoryItem inventory[], int itemCount, const char* productName, int quantity);

bool addToInventory(InventoryItem inventory[], int& itemCount, const char* productName, int quantity);

void displayMinimalInventory(const InventoryItem inventory[], int itemCount, int minimalQuantity);

void displayInventory(const InventoryItem inventory[], int itemCount);

#endif 
