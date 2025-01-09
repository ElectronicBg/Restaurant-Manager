#include "Menu.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int loadMenu(const char* filename, MenuItem menu[], int maxMenuItems) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file " << filename << " for menu.\n";
        return 0;
    }
    int count = 0;
    while (file >> menu[count].id) {
        file.ignore();
        file.getline(menu[count].name, MAX_NAME_LENGTH, ',');
        file >> menu[count].price;
        file.ignore();
        count++;
        if (count >= maxMenuItems) break;
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

bool addMenuItem(MenuItem menu[], int& menuCount, int& nextMenuId, Recipe recipes[], int& recipeCount) {
    if (menuCount >= MAX_MENU_ITEMS) {
        cout << "The menu is full. Cannot add a new item.\n";
        return false;
    }

    MenuItem newItem;
    Recipe newRecipe;

    cout << "Enter the name of the new item: ";
    cin.getline(newItem.name, MAX_NAME_LENGTH);
    cout << "Enter the price of the item: ";
    cin >> newItem.price;
    cin.ignore(10000, '\n');

    newItem.id = nextMenuId++;

    strcpy_s(newRecipe.itemName, newItem.name);
    cout << "Enter the number of ingredients for the item: ";
    cin >> newRecipe.numIngredients;
    cin.ignore(10000, '\n');

    if (newRecipe.numIngredients > MAX_RECIPE_INGREDIENTS) {
        cout << "Too many ingredients. Maximum: " << MAX_RECIPE_INGREDIENTS << "\n";
        return false;
    }

    for (int i = 0; i < newRecipe.numIngredients; i++) {
        cout << "Enter the name of ingredient " << i + 1 << ": ";
        cin.getline(newRecipe.ingredientNames[i], MAX_NAME_LENGTH);
        cout << "Enter the quantity for ingredient " << i + 1 << ": ";
        cin >> newRecipe.ingredientQuantities[i];
        cin.ignore(10000, '\n');
    }


    menu[menuCount++] = newItem;


    recipes[recipeCount++] = newRecipe;

    cout << "The new item \"" << newItem.name << "\" was successfully added to the menu.\n";
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

