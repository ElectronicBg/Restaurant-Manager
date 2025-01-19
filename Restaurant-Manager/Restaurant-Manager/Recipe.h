#pragma once

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
