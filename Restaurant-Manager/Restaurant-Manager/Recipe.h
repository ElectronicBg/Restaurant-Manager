#ifndef RECIPE_H
#define RECIPE_H

#include "Globals.h"

struct Recipe {
    char itemName[MAX_NAME_LENGTH];
    int numIngredients;
    char ingredientNames[MAX_RECIPE_INGREDIENTS][MAX_NAME_LENGTH];
    int ingredientQuantities[MAX_RECIPE_INGREDIENTS];
};

int loadRecipes(const char* filename, Recipe recipes[], int maxRecipes);

bool canPrepareItem(const Recipe& recipe, int quantity, struct InventoryItem inventory[], int inventoryCount);

void deductIngredients(const Recipe& recipe, int quantity, struct InventoryItem inventory[], int inventoryCount);

void saveRecipes(const char* filename, Recipe recipes[], int recipeCount);

#endif
