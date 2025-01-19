# **Restaurant Manager**

A C++ console-based software for managing a restaurant's menu, inventory, orders, and daily turnover, made as a **Course project** for the *Introduction to Programming* Course at the **Faculty of Mathematics and Informatics**, part of **Sofia University "St. Kliment Ohridski"**.

The program supports two user roles: **Waiter** and **Manager**. All data (orders, menu, inventory, turnover) is stored in files.

---

## **👨‍🎓 Student Information**

- **Name:** Emil Neshkov  
- **Faculty ID:** 0MI0600506  
- **Undergraduate Program:** Software Engineering at FMI of Sofia University "St. Kliment Ohridski"  
- **Semester:** 1  

---

## **🚀 Features**

### **For Waiters**
- 📝 View the menu
- 🍽️ Place an order *(only if ingredients are available)*
- ❌ Cancel an order *(only for the current day)*
- 📜 View past orders
- 🔍 View sorted past orders *(alphabetically) and item frequency*
- 💰 View daily turnover

### **For Managers**
- 📝 View the menu
- 🍽️ Place an order *(only if ingredients are available)*
- ❌ Cancel an order *(only for the current day)*
- 📜 View past orders
- 🔍 View sorted past orders *(alphabetically) and item frequency*
- 🔎 View past orders for a specific product
- 📦 View inventory levels
- ➕ Add products to inventory
- ➖ Remove items from inventory
- 💰 View daily turnover
- 📊 Generate daily reports *(resets turnover)*
- 📆 View turnover from a specific date
- 🍕 Add a new menu item
- 🗑️ Remove a menu item

---

## **🛠️ Installation**

### **Clone the repository:**
```sh
git clone https://github.com/yourusername/restaurant-manager.git
cd restaurant-manager
```

### **Compile the program:**
```sh
g++ -o restaurant_manager main.cpp Menu.cpp Orders.cpp Inventory.cpp Turnover.cpp Validator.cpp DateManager.cpp UI.cpp -std=c++11
```

### **Run the program:**
```sh
./restaurant_manager
```

---

## **📂 Project Structure**
```
📦 restaurant-manager
 ┣ 📜 main.cpp         # Entry point of the program
 ┣ 📜 Menu.h/.cpp      # Handles menu management
 ┣ 📜 Orders.h/.cpp    # Manages order processing
 ┣ 📜 Inventory.h/.cpp # Handles inventory operations
 ┣ 📜 Turnover.h/.cpp  # Manages daily turnover reports
 ┣ 📜 Validator.h/.cpp # Input validation functions
 ┣ 📜 DateManager.h/.cpp # Handles date tracking and incrementation
 ┣ 📜 UI.h/.cpp        # Manages user interface interactions
 ┣ 📜 Constants.h      # Stores constant values for the program
 ┣ 📜 README.md        # Project documentation
 ┣ 📜 menu.txt         # Stores the menu items
 ┣ 📜 orders.txt       # Stores past orders
 ┣ 📜 inventory.txt    # Stores inventory data
 ┣ 📜 turnover.txt     # Stores daily turnover records
```

---

## **📝 Usage**
1. **Select a user role** *(Waiter or Manager)* upon program start.
2. **Follow on-screen options** to navigate the menu.
3. **Enter valid inputs** when prompted *(e.g., numeric values where required).* 
4. **Orders automatically update inventory** when placed.
5. **Managers can add, remove, and manage stock and menu items.**
6. **Daily reports reset turnover and increment the working date.**

---

## **📜 License**
This project is licensed under the **GNU General Public License GPLv3 or higher** - see the [LICENSE](LICENSE) file for details.

---

**⭐ If you like this project, consider giving it a star on GitHub!** 🚀

