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
* Header: Manages recipe storage and processing
*
*/

#pragma once

#include "Inventory.h"
#include "Constants.h"

struct Recipe {
    char itemName[MAX_NAME_LENGTH];
    int numIngredients;
    char ingredientNames[MAX_RECIPE_INGREDIENTS][MAX_NAME_LENGTH];
    int ingredientQuantities[MAX_RECIPE_INGREDIENTS];
};

int loadRecipes(const char* filename, Recipe recipes[], int maxRecipes);

bool canPrepareItem(const Recipe& recipe, int quantity, struct InventoryItem inventory[], int inventoryCount);

void deductIngredients(const Recipe& recipe, int quantity, struct InventoryItem inventory[], int inventoryCount);

bool deleteRecipe(Recipe recipes[], int& recipeCount, const char* itemName);

void saveRecipes(const char* filename, Recipe recipes[], int recipeCount);
