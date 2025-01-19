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
* Header: Handles inventory operations
*
*/

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

