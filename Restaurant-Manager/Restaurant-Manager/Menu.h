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
* Header: Handles menu management
*
*/

#pragma once
#include "Recipe.h"
#include "Constants.h"

struct MenuItem {
    int id;                    
    char name[MAX_NAME_LENGTH];
    double price;              
};

int loadMenu(const char* filename, MenuItem menu[], int maxMenuItems);

void saveMenu(const char* filename, MenuItem menu[], int menuCount);

bool addMenuItem(MenuItem menu[], int& menuCount, int nextMenuId, Recipe recipes[], int& recipeCount,
    const char* itemName, double price, int numIngredients,
    char ingredientNames[][MAX_NAME_LENGTH], int ingredientQuantities[]);

bool deleteMenuItem(MenuItem menu[], int& menuCount, int idToDelete, Recipe recipes[], int& recipeCount);

void displayMenu(MenuItem menu[], int menuCount);