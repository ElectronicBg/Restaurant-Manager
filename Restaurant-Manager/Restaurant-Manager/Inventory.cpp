#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int loadInventory(const char* filename, InventoryItem inventory[], int maxItems) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Inventory file \"" << filename << "\" not found. Creating a new file.\n";
        ofstream newFile(filename);
        newFile.close();
        return 0;
    }
    int count = 0;
    while (file.getline(inventory[count].name, MAX_NAME_LENGTH, ',') && file >> inventory[count].quantity) {
        file.ignore();
        count++;
        if (count >= maxItems) break;
    }
    file.close();
    return count;
}

void saveInventory(const char* filename, InventoryItem inventory[], int itemCount) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file " << filename << " to save inventory.\n";
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        file << inventory[i].name << "," << inventory[i].quantity << "\n";
    }
    file.close();
}

bool checkInventory(const InventoryItem inventory[], int itemCount, const char* productName, int requiredQuantity) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i].name, productName) == 0) {
            return inventory[i].quantity >= requiredQuantity;
        }
    }
    return false;
}

bool deductFromInventory(InventoryItem inventory[], int itemCount, const char* productName, int quantity) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i].name, productName) == 0) {
            if (inventory[i].quantity >= quantity) {
                inventory[i].quantity -= quantity;
                return true;
            }
            else {
                cout << "Insufficient stock for " << productName << ".\n";
                return false;
            }
        }
    }
    cout << "The product " << productName << " was not found in the inventory.\n";
    return false;
}

bool addToInventory(InventoryItem inventory[], int& itemCount, const char* productName, int quantity) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i].name, productName) == 0) {
            inventory[i].quantity += quantity;
            return true;
        }
    }
    if (itemCount < MAX_INVENTORY_ITEMS) {
        strcpy_s(inventory[itemCount].name, productName);
        inventory[itemCount].quantity = quantity;
        itemCount++;
        return true;
    }
    cout << "The inventory is full. Cannot add a new product.\n";
    return false;
}

void displayMinimalInventory(const InventoryItem inventory[], int itemCount, int minimalQuantity) {
    cout << "\nProducts with quantity below " << minimalQuantity << ":\n";
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].quantity < minimalQuantity) {
            cout << inventory[i].name << ": " << inventory[i].quantity << "\n";
        }
    }
    cout << "\n";
}

void displayInventory(const InventoryItem inventory[], int itemCount) {
    cout << "\nInventory:\n";
    cout << "Product\t\tQuantity\n";
    for (int i = 0; i < itemCount; i++) {
        cout << inventory[i].name << "\t\t" << inventory[i].quantity << "\n";
    }
    cout << "\n";
}

