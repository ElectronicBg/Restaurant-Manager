#include "Recipe.h"
#include "Inventory.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int loadRecipes(const char* filename, Recipe recipes[], int maxRecipes) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Recipe file \"" << filename << "\" not found. Creating a new file.\n";
        ofstream newFile(filename);
        newFile.close();
        return 0;
    }
    int count = 0;
    while (file.getline(recipes[count].itemName, MAX_NAME_LENGTH, ':')) {
        file >> recipes[count].numIngredients;
        file.ignore();
        for (int i = 0; i < recipes[count].numIngredients; i++) {
            file.getline(recipes[count].ingredientNames[i], MAX_NAME_LENGTH, ',');
            file >> recipes[count].ingredientQuantities[i];
            file.ignore();
        }
        count++;
        if (count >= maxRecipes) break;
    }
    file.close();
    return count;
}

bool canPrepareItem(const Recipe& recipe, int quantity, InventoryItem inventory[], int inventoryCount) {
    for (int i = 0; i < recipe.numIngredients; i++) {
        bool found = false;
        for (int j = 0; j < inventoryCount; j++) {
            if (strcmp(recipe.ingredientNames[i], inventory[j].name) == 0) {
                if (inventory[j].quantity < recipe.ingredientQuantities[i] * quantity) {
                    cout << "Insufficient stock for: " << inventory[j].name << "\n";
                    return false;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "The product " << recipe.ingredientNames[i] << " is missing from inventory.\n";
            return false;
        }
    }
    return true;
}

void deductIngredients(const Recipe& recipe, int quantity, InventoryItem inventory[], int inventoryCount) {
    for (int i = 0; i < recipe.numIngredients; i++) {
        for (int j = 0; j < inventoryCount; j++) {
            if (strcmp(recipe.ingredientNames[i], inventory[j].name) == 0) {
                inventory[j].quantity -= recipe.ingredientQuantities[i] * quantity;
                break;
            }
        }
    }
    saveInventory("inventory.txt", inventory, inventoryCount);
}

bool deleteRecipe(Recipe recipes[], int& recipeCount, const char* itemName) {
    if (recipeCount == 0) {
        cout << "No recipes to delete.\n";
        return false;
    }

    int index = -1;

    for (int i = 0; i < recipeCount; i++) {
        if (strcmp(recipes[i].itemName, itemName) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Recipe for \"" << itemName << "\" not found.\n";
        return false;
    }

    cout << "Deleting recipe for: " << itemName << "\n";

    for (int i = index; i < recipeCount - 1; i++) {
        recipes[i] = recipes[i + 1];
    }
    recipeCount--;

    saveRecipes("recipes.txt", recipes, recipeCount);

    cout << "Recipe for \"" << itemName << "\" was successfully deleted.\n";
    return true;
}

void saveRecipes(const char* filename, Recipe recipes[], int recipeCount) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file " << filename << " to save recipes.\n";
        return;
    }
    for (int i = 0; i < recipeCount; i++) {
        file << recipes[i].itemName << ":" << recipes[i].numIngredients << "\n";
        for (int j = 0; j < recipes[i].numIngredients; j++) {
            file << recipes[i].ingredientNames[j] << "," << recipes[i].ingredientQuantities[j] << "\n";
        }
    }
    file.close();
}
