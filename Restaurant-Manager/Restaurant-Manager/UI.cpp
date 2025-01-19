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
* Header: Manages user interface interactions
*
*/

#include "UI.h"

#include <iostream>
#include <string>

using namespace std;

void runUI() {

	MenuItem menu[MAX_MENU_ITEMS];
	Recipe recipes[MAX_MENU_ITEMS];
	InventoryItem inventory[MAX_INVENTORY_ITEMS];
	Order orders[MAX_ORDERS];
	DailyTurnover turnovers[MAX_TURNOVERS];

	int menuCount = 0, recipeCount = 0, inventoryCount = 0, orderCount = 0, turnoverCount = 0;
	int nextOrderId = 1;

	char currentDate[MAX_DATE_LENGTH];
	loadCurrentDate(currentDate, "current_date.txt");

	menuCount = loadMenu("menu.txt", menu, MAX_MENU_ITEMS);
	recipeCount = loadRecipes("recipes.txt", recipes, MAX_MENU_ITEMS);
	inventoryCount = loadInventory("inventory.txt", inventory, MAX_INVENTORY_ITEMS);
	orderCount = loadOrders("orders.txt", orders, MAX_ORDERS);
	turnoverCount = loadTurnover("turnover.txt", turnovers, MAX_TURNOVERS);

	cout << "Starting the system with date: " << currentDate << endl;

	int userType = 0;
	while (true) {
		cout << "\n--- Restaurant Management System ---\n";
		cout << "1. Waiter\n";
		cout << "2. Manager\n";
		cout << "0. Exit\n";
		cout << "Select your role: ";
		cin >> userType;
		cin.ignore(10000, '\n');

		if (userType == 0) {
			cout << "Exiting the system. Goodbye!\n";
			break;
		}
		else if (userType == 1) {
			waiterMenu(menu, menuCount, orders, orderCount, nextOrderId, recipes, recipeCount,
				inventory, inventoryCount, turnovers, turnoverCount, currentDate);
		}
		else if (userType == 2) {
			managerMenu(menu, menuCount, orders, orderCount, nextOrderId, recipes, recipeCount,
				inventory, inventoryCount, turnovers, turnoverCount, currentDate);
		}
		else {
			cout << "Invalid option. Please try again.\n";
		}
	}

	saveMenu("menu.txt", menu, menuCount);
	saveRecipes("recipes.txt", recipes, recipeCount);
	saveInventory("inventory.txt", inventory, inventoryCount);
	saveOrders("orders.txt", orders, orderCount);
	saveTurnover("turnover.txt", turnovers, turnoverCount);
}

void waiterMenu(MenuItem menu[], int menuCount, Order orders[], int& orderCount, int& nextOrderId,
	Recipe recipes[], int& recipeCount, InventoryItem inventory[], int& inventoryCount,
	DailyTurnover turnovers[], int& turnoverCount, const char* currentDate) {
	int option;

	while (true) {
		cout << "\n--- Waiter Menu ---\n";
		displayAllOptions("Waiter");

		validateMenuOption(option);

		if (option == 0) break;

		switch (option) {
		case 1:
			displayMenu(menu, menuCount);
			break;
		case 2: {
			char itemName[MAX_NAME_LENGTH];
			int quantity;

			validateStringInput(itemName, MAX_NAME_LENGTH, "Enter item name: ");
			validatePositiveInt(quantity, "Enter quantity: ");

			if (addOrder(orders, orderCount, nextOrderId, currentDate, itemName, quantity,
				menu, menuCount, recipes, recipeCount, inventory, inventoryCount)) {
				cout << "Order added successfully.\n";
				saveOrders("orders.txt", orders, orderCount);
			}
			else {
				cout << "Failed to add order.\n";
			}
			break;
		}
		case 3:
			int orderId;
			validatePositiveInt(orderId, "Enter the ID of the order you want to cancel: ");

			if (!cancelOrder(orders, orderCount, orderId, currentDate)) {
				cout << "Failed to cancel the order.\n";
			}
			break;
		case 4:
			displayOrders(orders, orderCount);
			break;
		case 5:
			displaySortedOrders(orders, orderCount);
			break;
		case 6:
			displayDailyTurnover(orders, orderCount, currentDate);
			break;
		case 7:
			displayAllOptions("Waiter");
			break;
		default:
			cout << "Invalid option. Please try again.\n";
		}
	}
}

void managerMenu(MenuItem menu[], int& menuCount, Order orders[], int& orderCount, int& nextOrderId,
	Recipe recipes[], int& recipeCount, InventoryItem inventory[], int& inventoryCount,
	DailyTurnover turnovers[], int& turnoverCount, char* currentDate) {
	int option;

	while (true) {
		cout << "\n--- Manager Menu ---\n";
		displayAllOptions("Manager");

		validateMenuOption(option);

		if (option == 0) break;

		switch (option) {
		case 1:
			displayMenu(menu, menuCount);
			break;

		case 2: {
			char itemName[MAX_NAME_LENGTH];
			int quantity;

			validateStringInput(itemName, MAX_NAME_LENGTH, "Enter item name: ");
			validatePositiveInt(quantity, "Enter quantity: ");

			if (addOrder(orders, orderCount, nextOrderId, currentDate, itemName, quantity,
				menu, menuCount, recipes, recipeCount, inventory, inventoryCount)) {
				cout << "Order added successfully.\n";
				saveOrders("orders.txt", orders, orderCount);
			}
			else {
				cout << "Failed to add order.\n";
			}
			break;
		}

		case 3: {
			int orderId;
			validatePositiveInt(orderId, "Enter the ID of the order you want to cancel: ");

			if (!cancelOrder(orders, orderCount, orderId, currentDate)) {
				cout << "Failed to cancel the order.\n";
			}
			break;
		}

		case 4:
			displayOrders(orders, orderCount);
			break;

		case 5:
			displaySortedOrders(orders, orderCount);
			break;

		case 6: {
			char itemName[MAX_NAME_LENGTH];
			validateStringInput(itemName, MAX_NAME_LENGTH, "Enter the name of the product: ");

			int count = countOrdersForItemToday(orders, orderCount, currentDate, itemName);
			cout << "The product \"" << itemName << "\" has been ordered " << count << " times today.\n";
			break;
		}

		case 7:
			displayInventory(inventory, inventoryCount);
			break;

		case 8: {
			char productName[MAX_NAME_LENGTH];
			int quantity;
			validateStringInput(productName, MAX_NAME_LENGTH, "Enter product name: ");
			validatePositiveInt(quantity, "Enter quantity: ");

			if (addToInventory(inventory, inventoryCount, productName, quantity)) {
				cout << "Product \"" << productName << "\" added to inventory.\n";
				saveInventory("inventory.txt", inventory, inventoryCount);
			}
			else {
				cout << "Failed to add product \"" << productName << "\" to inventory.\n";
			}
			break;
		}

		case 9: {
			char productName[MAX_NAME_LENGTH];
			validateStringInput(productName, MAX_NAME_LENGTH, "Enter the name of the product to remove: ");

			if (!removeFromInventory(inventory, inventoryCount, productName)) {
				cout << "Failed to remove the product.\n";
			}
			break;
		}

		case 10:
			displayDailyTurnover(orders, orderCount, currentDate);
			break;

		case 11:
			generateDailyReport(turnovers, turnoverCount, currentDate, orders, orderCount, "turnover.txt");
			break;

		case 12: {
			char startDate[MAX_DATE_LENGTH];
			validateStringInput(startDate, MAX_DATE_LENGTH, "Enter start date (YYYY-MM-DD): ");
			displayTurnoverFromDate(turnovers, turnoverCount, startDate);
			break;
		}

		case 13: {
			char itemName[MAX_NAME_LENGTH];
			double price;
			int numIngredients;
			char ingredientNames[MAX_RECIPE_INGREDIENTS][MAX_NAME_LENGTH];
			int ingredientQuantities[MAX_RECIPE_INGREDIENTS];

			validateStringInput(itemName, MAX_NAME_LENGTH, "Enter the name of the new item: ");
			validatePositiveDouble(price, "Enter the price of the item: ");
			validatePositiveInt(numIngredients, "Enter the number of ingredients for the item: ");

			if (numIngredients > MAX_RECIPE_INGREDIENTS) {
				cout << "Too many ingredients. Maximum: " << MAX_RECIPE_INGREDIENTS << "\n";
				break;
			}

			for (int i = 0; i < numIngredients; i++) {
				validateStringInput(ingredientNames[i], MAX_NAME_LENGTH, ("Enter the name of ingredient " + to_string(i + 1) + ": ").c_str());
				validatePositiveInt(ingredientQuantities[i], ("Enter the quantity for ingredient " + to_string(i + 1) + ": ").c_str());
			}

			int nextMenuId = (menuCount > 0) ? menu[menuCount - 1].id + 1 : 1;

			addMenuItem(menu, menuCount, nextMenuId, recipes, recipeCount, itemName, price, numIngredients, ingredientNames, ingredientQuantities);

			break;
		}
		case 14: {
			int idToDelete;
			validatePositiveInt(idToDelete, "Enter the ID of the menu item to delete: ");

			if (!deleteMenuItem(menu, menuCount, idToDelete, recipes, recipeCount)) {
				cout << "Failed to delete menu item.\n";
			}
			break;
		}
		default:
			cout << "Invalid option. Please try again.\n";
		}
	}
}

void displayAllOptions(const char* userType) {
	if (strcmp(userType, "Waiter") == 0) {
		cout << "1. View menu\n";
		cout << "2. Place an order\n";
		cout << "3. Cancel an order\n";
		cout << "4. View past orders\n";
		cout << "5. View past orders sorted alphabetically\n";
		cout << "6. View daily turnover\n";
		cout << "0. Exit to main menu\n";
	}
	else if (strcmp(userType, "Manager") == 0) {
		cout << "1. View menu\n";
		cout << "2. Place an order\n";
		cout << "3. Cancel an order\n";
		cout << "4. View past orders\n";
		cout << "5. View past orders sorted alphabetically\n";
		cout << "6. View past orders for a specific product\n";
		cout << "7. View inventory levels\n";
		cout << "8. Add products to inventory\n";
		cout << "9. Remove item from inventory\n";
		cout << "10. View daily turnover\n";
		cout << "11. Generate daily report (reset turnover)\n";
		cout << "12. View turnover from a specific date\n";
		cout << "13. Add a new menu item\n";
		cout << "14. Remove a menu item\n";
		cout << "0. Exit to main menu\n";
	}
}
