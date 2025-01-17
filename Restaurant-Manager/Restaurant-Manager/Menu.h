#ifndef MENU_H
#define MENU_H

#include "Recipe.h"
#include "Globals.h"

struct MenuItem {
    int id;                    
    char name[MAX_NAME_LENGTH];
    double price;              
};

int loadMenu(const char* filename, MenuItem menu[], int maxMenuItems);

void saveMenu(const char* filename, MenuItem menu[], int menuCount);

bool addMenuItem(MenuItem menu[], int& menuCount, int& nextMenuId, Recipe recipes[], int& recipeCount);

void displayMenu(MenuItem menu[], int menuCount);

#endif 
