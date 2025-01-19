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