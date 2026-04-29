#include <iostream>
#include <string.h>
using namespace std;

const int MAX_PRODUCTS = 100;
const int MAX_BILL_ITEMS = 50;

class Product {
public:
    int productId;
    char productName[50];
    float price;
    int quantity;
    int isActive;
    
    Product() {
        productId = 0;
        strcpy(productName, "");
        price = 0.0;
        quantity = 0;
        isActive = 0;
    }
    
    void setData(int id, char name[], float p, int qty) {
        productId = id;
        strcpy(productName, name);
        price = p;
        quantity = qty;
        isActive = 1;
    }
    
    void display() {
        cout << productId << "\t\t" 
             << productName << "\t\t" 
             << price << "\t\t" 
             << quantity << endl;
    }
};

class BillItem {
public:
    int productId;
    char productName[50];
    float price;
    int quantity;
    float total;
    
    BillItem() {
        productId = 0;
        strcpy(productName, "");
        price = 0.0;
        quantity = 0;
        total = 0.0;
    }
    
    void setData(int id, char name[], float p, int qty) {
        productId = id;
        strcpy(productName, name);
        price = p;
        quantity = qty;
        total = price * quantity;
    }
    
    void display() {
        cout << productId << "\t\t" 
             << productName << "\t\t" 
             << price << "\t\t" 
             << quantity << "\t\t" 
             << total << endl;
    }
};

class Inventory {
private:
    Product products[MAX_PRODUCTS];
    int productCount;
    
public:
    Inventory() {
        productCount = 0;
    }
    
    void addProduct() {
        if (productCount >= MAX_PRODUCTS) {
            cout << "\nInventory is full!\n";
            return;
        }
        
        int id, qty;
        char name[50];
        float price;
        
        cout << "\n--- Add New Product ---\n";
        cout << "Enter Product ID: ";
        cin >> id;
        
        if (findProduct(id) != -1) {
            cout << "Product ID already exists!\n";
            return;
        }
        
        cout << "Enter Product Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> qty;
        
        products[productCount].setData(id, name, price, qty);
        productCount++;
        cout << "Product added successfully!\n";
    }
    
    void displayAllProducts() {
        if (productCount == 0) {
            cout << "\nNo products in inventory!\n";
            return;
        }
        
        cout << "\n--- Current Inventory ---\n";
        cout << "ID\t\tName\t\t\tPrice\t\tStock\n";
        cout << "-------------------------------------------------------\n";
        
        for (int i = 0; i < productCount; i++) {
            if (products[i].isActive == 1) {
                products[i].display();
            }
        }
    }
    
    int findProduct(int id) {
        for (int i = 0; i < productCount; i++) {
            if (products[i].productId == id && products[i].isActive == 1) {
                return i;
            }
        }
        return -1;
    }
    
    int getProductById(int id, Product& prod) {
        int index = findProduct(id);
        if (index != -1) {
            prod = products[index];
            return 1;
        }
        return 0;
    }
    
    int checkStock(int id, int qty) {
        int index = findProduct(id);
        if (index != -1 && products[index].quantity >= qty) {
            return 1;
        }
        return 0;
    }
    
    void updateStock(int id, int qty) {
        int index = findProduct(id);
        if (index != -1) {
            products[index].quantity -= qty;
        }
    }
    
    void updateProduct() {
        int id;
        cout << "\nEnter Product ID to update: ";
        cin >> id;
        
        int index = findProduct(id);
        if (index == -1) {
            cout << "Product not found!\n";
            return;
        }
        
        cout << "\nCurrent Details:\n";
        products[index].display();
        
        int newQty;
        float newPrice;
        cout << "\nEnter new quantity: ";
        cin >> newQty;
        cout << "Enter new price: ";
        cin >> newPrice;
        
        products[index].quantity = newQty;
        products[index].price = newPrice;
        
        cout << "Product updated successfully!\n";
    }
    
    void deleteProduct() {
        int id;
        cout << "\nEnter Product ID to delete: ";
        cin >> id;
        
        int index = findProduct(id);
        if (index == -1) {
            cout << "Product not found!\n";
            return;
        }
        
        products[index].isActive = 0;
        cout << "Product deleted successfully!\n";
    }
};

class Bill {
private:
    BillItem items[MAX_BILL_ITEMS];
    int itemCount;
    int billNumber;
    char billStatus[20];
    float totalAmount;
    
public:
    Bill() {
        itemCount = 0;
        billNumber = 1000;
        strcpy(billStatus, "unpaid");
        totalAmount = 0.0;
    }
    
    void setBillNumber(int num) {
        billNumber = num;
    }
    
    void addItem(int id, char name[], float price, int qty) {
        if (itemCount >= MAX_BILL_ITEMS) {
            cout << "\nBill is full!\n";
            return;
        }
        
        items[itemCount].setData(id, name, price, qty);
        totalAmount += items[itemCount].total;
        itemCount++;
    }
    
    void displayBill() {
        cout << "\n======================================================\n";
        cout << "                    INVOICE                    \n";
        cout << "======================================================\n";
        cout << "Bill Number: " << billNumber << endl;
        cout << "Status: " << billStatus << endl;
        cout << "------------------------------------------------------\n";
        
        cout << "ID\t\tProduct\t\t\tPrice\t\tQty\t\tTotal\n";
        cout << "------------------------------------------------------\n";
        
        for (int i = 0; i < itemCount; i++) {
            items[i].display();
        }
        
        cout << "------------------------------------------------------\n";
        cout << "\t\t\t\tGrand Total: Rs. " << totalAmount << endl;
        cout << "======================================================\n";
    }
    
    void markAsPaid() {
        strcpy(billStatus, "paid");
        cout << "\nBill marked as PAID!\n";
    }
    
    int isPaid() {
        if (strcmp(billStatus, "paid") == 0) {
            return 1;
        }
        return 0;
    }
    
    int getItemCount() {
        return itemCount;
    }
    
    void getItemAt(int index, BillItem& item) {
        if (index >= 0 && index < itemCount) {
            item = items[index];
        }
    }
    
    int isEmpty() {
        if (itemCount == 0) {
            return 1;
        }
        return 0;
    }
};

class BillingSystem {
private:
    Inventory inventory;
    Bill bills[10];
    int currentBillIndex;
    int billCounter;
    int hasActiveBill;
    
public:
    BillingSystem() {
        currentBillIndex = -1;
        billCounter = 1000;
        hasActiveBill = 0;
    }
    
    Inventory& getInventory() {
        return inventory;
    }
    
    void createNewBill() {
        if (hasActiveBill == 1 && bills[currentBillIndex].isPaid() == 0) {
            cout << "\nPlease complete the current bill first!\n";
            return;
        }
        
        currentBillIndex = (currentBillIndex + 1) % 10;
        bills[currentBillIndex] = Bill();
        billCounter++;
        bills[currentBillIndex].setBillNumber(billCounter);
        hasActiveBill = 1;
        cout << "\nNew bill created successfully! Bill #" << billCounter << "\n";
    }
    
    void addItemToBill() {
        if (hasActiveBill == 0) {
            cout << "\nPlease create a bill first!\n";
            return;
        }
        
        if (bills[currentBillIndex].isPaid() == 1) {
            cout << "\nCurrent bill is already paid. Create a new bill.\n";
            return;
        }
        
        int id, qty;
        cout << "\nEnter Product ID: ";
        cin >> id;
        
        Product product;
        if (inventory.getProductById(id, product) == 0) {
            cout << "Product not found in inventory!\n";
            return;
        }
        
        cout << "Product: " << product.productName << endl;
        cout << "Available Stock: " << product.quantity << endl;
        cout << "Price: Rs. " << product.price << endl;
        cout << "Enter Quantity: ";
        cin >> qty;
        
        if (inventory.checkStock(id, qty) == 0) {
            cout << "Insufficient stock!\n";
            return;
        }
        
        bills[currentBillIndex].addItem(id, product.productName, product.price, qty);
        cout << "Item added to bill successfully!\n";
    }
    
    void viewCurrentBill() {
        if (hasActiveBill == 0) {
            cout << "\nNo active bill!\n";
            return;
        }
        
        if (bills[currentBillIndex].isEmpty() == 1) {
            cout << "\nBill is empty!\n";
            return;
        }
        
        bills[currentBillIndex].displayBill();
    }
    
    void processBillPayment() {
        if (hasActiveBill == 0) {
            cout << "\nNo active bill to process!\n";
            return;
        }
        
        if (bills[currentBillIndex].isEmpty() == 1) {
            cout << "\nBill is empty! Add items first.\n";
            return;
        }
        
        if (bills[currentBillIndex].isPaid() == 1) {
            cout << "\nBill is already paid!\n";
            return;
        }
        
        char confirm;
        cout << "\nConfirm payment? (y/n): ";
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            bills[currentBillIndex].markAsPaid();
            
            int itemCount = bills[currentBillIndex].getItemCount();
            for (int i = 0; i < itemCount; i++) {
                BillItem item;
                bills[currentBillIndex].getItemAt(i, item);
                inventory.updateStock(item.productId, item.quantity);
            }
            
            cout << "Inventory updated successfully!\n";
            bills[currentBillIndex].displayBill();
        } else {
            cout << "Payment cancelled.\n";
        }
    }
};

void displayMenu() {
    cout << "\n========================================\n";
    cout << "   INVENTORY & BILLING SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Add Product to Inventory\n";
    cout << "2. Display All Products\n";
    cout << "3. Update Product Details\n";
    cout << "4. Delete Product\n";
    cout << "5. Create New Bill\n";
    cout << "6. Add Item to Bill\n";
    cout << "7. View Current Bill\n";
    cout << "8. Process Payment\n";
    cout << "9. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    BillingSystem billingSystem;
    
    int choice;
    
    while (1) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                billingSystem.getInventory().addProduct();
                break;
            case 2:
                billingSystem.getInventory().displayAllProducts();
                break;
            case 3:
                billingSystem.getInventory().updateProduct();
                break;
            case 4:
                billingSystem.getInventory().deleteProduct();
                break;
            case 5:
                billingSystem.createNewBill();
                break;
            case 6:
                billingSystem.addItemToBill();
                break;
            case 7:
                billingSystem.viewCurrentBill();
                break;
            case 8:
                billingSystem.processBillPayment();
                break;
            case 9:
                cout << "\nThank you for using the system!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }
    
    return 0;
}
