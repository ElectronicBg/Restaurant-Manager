#include "Orders.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int loadOrders(const char* filename, Order orders[], int maxOrders) {
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "Orders file \"" << filename << "\" not found. Creating a new file.\n";

		ofstream newFile(filename);
		newFile.close();

		return 0;
	}

	int count = 0;

	while (file >> orders[count].orderId) {
		file.ignore();
		file.getline(orders[count].date, MAX_DATE_LENGTH, ',');
		file.getline(orders[count].itemName, MAX_NAME_LENGTH, ',');
		file >> orders[count].quantity;
		file.ignore();
		file >> orders[count].totalPrice;
		file.ignore();
		count++;

		if (count >= maxOrders) 
			break;
	}

	file.close();

	return count;
}

void saveOrders(const char* filename, Order orders[], int orderCount) {
	ofstream file(filename);

	if (!file.is_open()) {
		cout << "Unable to open file " << filename << " for saving orders.\n";

		return;
	}
	for (int i = 0; i < orderCount; i++) {
		file << orders[i].orderId << ","
			<< orders[i].date << ","
			<< orders[i].itemName << ","
			<< orders[i].quantity << ","
			<< orders[i].totalPrice << "\n";
	}

	file.close();
}

bool addOrder(Order orders[], int& orderCount, int& nextOrderId, const char* date,
	const char* itemName, int quantity, MenuItem menu[], int menuCount,
	Recipe recipes[], int recipeCount, InventoryItem inventory[], int inventoryCount) {

	if (orderCount >= MAX_ORDERS) {
		cout << "Order list is full. Cannot add a new order.\n";

		return false;
	}

	if (orderCount > 0) {
		nextOrderId = orders[orderCount - 1].orderId + 1;
	}
	else {
		nextOrderId = 1;
	}

	int menuIndex = -1;

	for (int i = 0; i < menuCount; i++) {
		if (strcmp(menu[i].name, itemName) == 0) {
			menuIndex = i;

			break;
		}
	}
	if (menuIndex == -1) {
		cout << "Item \"" << itemName << "\" not found in the menu.\n";

		return false;
	}

	int recipeIndex = -1;
	for (int i = 0; i < recipeCount; i++) {
		if (strcmp(recipes[i].itemName, itemName) == 0) {
			recipeIndex = i;

			break;
		}
	}
	if (recipeIndex == -1) {
		cout << "Recipe for \"" << itemName << "\" not found.\n";

		return false;
	}

	if (!canPrepareItem(recipes[recipeIndex], quantity, inventory, inventoryCount)) {
		cout << "Insufficient stock to prepare \"" << itemName << "\".\n";

		return false;
	}

	deductIngredients(recipes[recipeIndex], quantity, inventory, inventoryCount);

	orders[orderCount].orderId = nextOrderId;
	strcpy_s(orders[orderCount].date, date);
	strcpy_s(orders[orderCount].itemName, itemName);
	orders[orderCount].quantity = quantity;
	orders[orderCount].totalPrice = menu[menuIndex].price * quantity;
	orderCount++;

	cout << "Order for \"" << itemName << "\" added successfully.\n";

	return true;
}

bool cancelOrder(Order orders[], int& orderCount, int orderId, const char* currentDate) {
	if (orderCount == 0) {
		cout << "No orders available to cancel.\n";

		return false;
	}

	int index = -1;

	for (int i = 0; i < orderCount; i++) {
		if (orders[i].orderId == orderId && strcmp(orders[i].date, currentDate) == 0) {
			index = i;

			break;
		}
	}

	if (index == -1) {
		cout << "Order with ID " << orderId << " was not found or is not from today.\n";

		return false;
	}

	cout << "Cancelling order with ID: " << orders[index].orderId << " (" << orders[index].itemName << ")\n";

	for (int i = index; i < orderCount - 1; i++) {
		orders[i] = orders[i + 1];
	}
	orderCount--;

	saveOrders("orders.txt", orders, orderCount);

	cout << "Order with ID " << orderId << " has been successfully canceled.\n";

	return true;
}

void displayOrders(const Order orders[], int orderCount) {
	cout << "\nOrders:\n";
	cout << "ID\tDate\t\tItem\t\tQuantity\tTotal Price\n";

	for (int i = 0; i < orderCount; i++) {
		cout << orders[i].orderId << "\t"
			<< orders[i].date << "\t"
			<< orders[i].itemName << "\t\t"
			<< orders[i].quantity << "\t\t"
			<< orders[i].totalPrice << " BGN\n";
	}
	cout << "\n";
}

void displaySortedOrders(const Order orders[], int orderCount) {
	Order sortedOrders[MAX_ORDERS];

	for (int i = 0; i < orderCount; i++) {
		sortedOrders[i] = orders[i];
	}

	for (int i = 0; i < orderCount - 1; i++) {
		for (int j = 0; j < orderCount - i - 1; j++) {
			if (strcmp(sortedOrders[j].itemName, sortedOrders[j + 1].itemName) > 0) {
				Order temp = sortedOrders[j];
				sortedOrders[j] = sortedOrders[j + 1];
				sortedOrders[j + 1] = temp;
			}
		}
	}

	displayOrders(sortedOrders, orderCount);
}

int countOrdersForItemToday(const Order orders[], int orderCount, const char* currentDate, const char* itemName) {
	int count = 0;

	for (int i = 0; i < orderCount; i++) {
		if (strcmp(orders[i].date, currentDate) == 0 && strcmp(orders[i].itemName, itemName) == 0) {
			count += orders[i].quantity;
		}
	}

	return count;
}


