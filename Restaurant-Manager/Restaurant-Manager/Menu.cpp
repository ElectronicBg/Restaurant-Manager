#include "Menu.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int loadMenu(const char* filename, MenuItem menu[], int maxMenuItems) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Menu file \"" << filename << "\" not found. Creating a new file.\n";

        ofstream newFile(filename);
        newFile.close();

        return 0;
    }

    int count = 0;

    while (file >> menu[count].id) {
        file.ignore();
        file.getline(menu[count].name, MAX_NAME_LENGTH, ',');
        file >> menu[count].price;
        file.ignore();
        count++;

        if (count >= maxMenuItems) 
            break;
    }

    file.close();

    return count;
}

void saveMenu(const char* filename, MenuItem menu[], int menuCount) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file " << filename << " to save the menu.\n";

        return;
    }
    for (int i = 0; i < menuCount; i++) {
        file << menu[i].id << "," << menu[i].name << "," << menu[i].price << "\n";
    }

    file.close();
}

bool addMenuItem(MenuItem menu[], int& menuCount, int nextMenuId, Recipe recipes[], int& recipeCount,
    const char* itemName, double price, int numIngredients,
    char ingredientNames[][MAX_NAME_LENGTH], int ingredientQuantities[]) {

    if (menuCount >= MAX_MENU_ITEMS) {
        cout << "The menu is full. Cannot add a new item.\n";

        return false;
    }

    MenuItem newItem;
    Recipe newRecipe;

    newItem.id = nextMenuId;
    strcpy_s(newItem.name, MAX_NAME_LENGTH, itemName);
    newItem.price = price;

    strcpy_s(newRecipe.itemName, MAX_NAME_LENGTH, itemName);
    newRecipe.numIngredients = numIngredients;

    for (int i = 0; i < numIngredients; i++) {
        strcpy_s(newRecipe.ingredientNames[i], MAX_NAME_LENGTH, ingredientNames[i]);
        newRecipe.ingredientQuantities[i] = ingredientQuantities[i];
    }

    menu[menuCount++] = newItem;
    recipes[recipeCount++] = newRecipe;

    saveMenu("menu.txt", menu, menuCount);
    saveRecipes("recipes.txt", recipes, recipeCount);

    cout << "The new item \"" << newItem.name << "\" was successfully added to the menu.\n";

    return true;
}

bool deleteMenuItem(MenuItem menu[], int& menuCount, int idToDelete, Recipe recipes[], int& recipeCount) {
    if (menuCount == 0) {
        cout << "The menu is empty. No items to delete.\n";

        return false;
    }

    int index = -1;

    for (int i = 0; i < menuCount; i++) {
        if (menu[i].id == idToDelete) {
            index = i;

            break;
        }
    }

    if (index == -1) {
        cout << "Menu item with ID " << idToDelete << " not found.\n";

        return false;
    }

    cout << "Deleting menu item: " << menu[index].name << "\n";

    char itemName[MAX_NAME_LENGTH];
    strcpy_s(itemName, MAX_NAME_LENGTH, menu[index].name);


    for (int i = index; i < menuCount - 1; i++) {
        menu[i] = menu[i + 1];
    }
    menuCount--; 

    deleteRecipe(recipes, recipeCount, itemName);

    saveMenu("menu.txt", menu, menuCount);

    cout << "Menu item with ID " << idToDelete << " and its corresponding recipe were successfully deleted.\n";

    return true;
}

void displayMenu(MenuItem menu[], int menuCount) {
    cout << "\nMenu:\n";
    cout << "ID\tName\t\tPrice\n";

    for (int i = 0; i < menuCount; i++) {
        cout << menu[i].id << "\t" << menu[i].name << "\t\t" << menu[i].price << " lv.\n";
    }
    cout << "\n";
}

