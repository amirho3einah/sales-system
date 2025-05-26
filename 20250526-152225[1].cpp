#include <iostream>
#include <string>
#include <ctime>
using namespace std;

const int MAX_SIZE = 100;

// Base Person class
class Person {
protected:
    string firstName;
    string lastName;
    string nationalID;
    int birthYear;
    string gender;

public:
    Person(string fname, string lname, string nid, int byear, string g)
        : firstName(fname), lastName(lname), nationalID(nid), birthYear(byear), gender(g) {}

    virtual void showInfo() {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "National ID: " << nationalID << endl;
        cout << "Birth Year: " << birthYear << endl;
        cout << "Gender: " << gender << endl;
    }

    string getNationalID() { return nationalID; }
};

// Customer class derived from Person
class Customer : public Person {
private:
    string customerID;
    string province;
    string city;

public:
    Customer(string fname, string lname, string nid, int byear, string g, 
             string cid, string prov, string c)
        : Person(fname, lname, nid, byear, g), customerID(cid), province(prov), city(c) {}

    void showInfo() override {
        Person::showInfo();
        cout << "Customer ID: " << customerID << endl;
        cout << "Location: " << city << ", " << province << endl;
    }

    string getCustomerID() { return customerID; }
};

// Product class
class Product {
private:
    string productID;
    string name;
    float price;
    string brand;
    float weight;

public:
    Product(string pid, string n, float p, string b, float w) 
        : productID(pid), name(n), price(p), brand(b), weight(w) {
        if (price <= 0 || weight <= 0) {
            throw invalid_argument("Price and weight must be positive!");
        }
    }

    void showInfo() {
        cout << "Product ID: " << productID << endl;
        cout << "Name: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Brand: " << brand << endl;
        cout << "Weight: " << weight << endl;
    }

    string getProductID() { return productID; }
    float getPrice() { return price; }
};

// Dealer class
class Dealer {
private:
    string dealerID;
    string name;
    int establishmentYear;
    string economicCode;
    string ownerFirstName;
    string ownerLastName;
    string province;
    string city;

public:
    Dealer(string did, string n, int eyear, string ecode, 
           string ofname, string olname, string prov, string c)
        : dealerID(did), name(n), establishmentYear(eyear), economicCode(ecode),
          ownerFirstName(ofname), ownerLastName(olname), province(prov), city(c) {}

    void showInfo() {
        cout << "Dealer ID: " << dealerID << endl;
        cout << "Name: " << name << endl;
        cout << "Established: " << establishmentYear << endl;
        cout << "Economic Code: " << economicCode << endl;
        cout << "Owner: " << ownerFirstName << " " << ownerLastName << endl;
        cout << "Location: " << city << ", " << province << endl;
    }

    string getDealerID() { return dealerID; }
};

// Purchase class
class Purchase {
private:
    Customer* customer;
    Product* product;
    Dealer* dealer;
    int quantity;
    string purchaseDate;

public:
    Purchase(Customer* c, Product* p, Dealer* d, int q, string date)
        : customer(c), product(p), dealer(d), quantity(q), purchaseDate(date) {
        if (quantity <= 0) {
            throw invalid_argument("Quantity must be positive!");
        }
    }

    void showInfo() {
        cout << "Purchase Details:" << endl;
        cout << "Date: " << purchaseDate << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "----- Customer -----" << endl;
        customer->showInfo();
        cout << "----- Product -----" << endl;
        product->showInfo();
        cout << "----- Dealer -----" << endl;
        dealer->showInfo();
    }

    Customer* getCustomer() { return customer; }
    Product* getProduct() { return product; }
    Dealer* getDealer() { return dealer; }
    int getQuantity() { return quantity; }
    string getDate() { return purchaseDate; }
};

// Global arrays to store data
Customer* customers[MAX_SIZE];
Product* products[MAX_SIZE];
Dealer* dealers[MAX_SIZE];
Purchase* purchases[MAX_SIZE];

int customerCount = 0;
int productCount = 0;
int dealerCount = 0;
int purchaseCount = 0;

// Function prototypes
void showMainMenu();
void addProduct();
void removeProduct();
void addCustomer();
void removeCustomer();
void addDealer();
void removeDealer();
void recordPurchase();
void totalPurchaseByCustomer();
void customersByProduct();
void productsByDealer();
void salesCountByProduct();
void productsByCustomer();
void dealerSalesReport();

// Helper functions
bool isCustomerExists(string nationalID);
bool isProductExists(string productID);
bool isDealerExists(string dealerID);
string getCurrentDate();

int main() {
    int choice;
    do {
        showMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: addCustomer(); break;
            case 4: removeCustomer(); break;
            case 5: addDealer(); break;
            case 6: removeDealer(); break;
            case 7: recordPurchase(); break;
            case 8: totalPurchaseByCustomer(); break;
            case 9: customersByProduct(); break;
            case 10: productsByDealer(); break;
            case 11: salesCountByProduct(); break;
            case 12: productsByCustomer(); break;
            case 13: dealerSalesReport(); break;
            case 14: cout << "Exiting program..." << endl; break;
            default: cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 14);

    // Clean up memory
    for (int i = 0; i < customerCount; i++) delete customers[i];
    for (int i = 0; i < productCount; i++) delete products[i];
    for (int i = 0; i < dealerCount; i++) delete dealers[i];
    for (int i = 0; i < purchaseCount; i++) delete purchases[i];

    return 0;
}

void showMainMenu() {
    cout << "\n===== Store Management System =====" << endl;
    cout << "1. Add a Product" << endl;
    cout << "2. Remove a Product" << endl;
    cout << "3. Add a Customer" << endl;
    cout << "4. Remove a Customer" << endl;
    cout << "5. Add a Dealer" << endl;
    cout << "6. Remove a Dealer" << endl;
    cout << "7. Record a Purchase" << endl;
    cout << "8. Total purchase amount for a customer" << endl;
    cout << "9. Customers who purchased a product" << endl;
    cout << "10. Products sold by a dealer" << endl;
    cout << "11. Number of units sold for a product" << endl;
    cout << "12. Products purchased by a customer" << endl;
    cout << "13. Sales report for all dealers" << endl;
    cout << "14. Exit" << endl;
}

void addProduct() {
    if (productCount >= MAX_SIZE) {
        cout << "Error: Maximum number of products reached!" << endl;
        return;
    }

    string pid, name, brand;
    float price, weight;

    cout << "\n===== Add New Product =====" << endl;
    cout << "Enter Product ID: ";
    getline(cin, pid);
    
    if (isProductExists(pid)) {
        cout << "Error: Product with this ID already exists!" << endl;
        return;
    }

    cout << "Enter Product Name: ";
    getline(cin, name);
    
    cout << "Enter Price: ";
    cin >> price;
    
    cout << "Enter Brand: ";
    cin.ignore();
    getline(cin, brand);
    
    cout << "Enter Weight: ";
    cin >> weight;

    try {
        products[productCount++] = new Product(pid, name, price, brand, weight);
        cout << "Product added successfully!" << endl;
    } catch (invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void removeProduct() {
    string pid;
    cout << "\n===== Remove Product =====" << endl;
    cout << "Enter Product ID to remove: ";
    getline(cin, pid);

    // Find product
    int index = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i]->getProductID() == pid) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Error: Product not found!" << endl;
        return;
    }

    // Remove associated purchases first
    for (int i = 0; i < purchaseCount; ) {
        if (purchases[i]->getProduct()->getProductID() == pid) {
            delete purchases[i];
            // Shift remaining elements
            for (int j = i; j < purchaseCount - 1; j++) {
                purchases[j] = purchases[j + 1];
            }
            purchaseCount--;
        } else {
            i++;
        }
    }

    // Remove the product
    delete products[index];
    for (int i = index; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }
    productCount--;

    cout << "Product and all associated purchases removed successfully!" << endl;
}

void addCustomer() {
    if (customerCount >= MAX_SIZE) {
        cout << "Error: Maximum number of customers reached!" << endl;
        return;
    }

    string fname, lname, nid, gender, cid, prov, city;
    int byear;

    cout << "\n===== Add New Customer =====" << endl;
    cout << "Enter National ID: ";
    getline(cin, nid);
    
    if (isCustomerExists(nid)) {
        cout << "Error: Customer with this National ID already exists!" << endl;
        return;
    }

    cout << "Enter First Name: ";
    getline(cin, fname);
    
    cout << "Enter Last Name: ";
    getline(cin, lname);
    
    cout << "Enter Birth Year: ";
    cin >> byear;
    
    cout << "Enter Gender: ";
    cin.ignore();
    getline(cin, gender);
    
    cout << "Enter Customer ID: ";
    getline(cin, cid);
    
    cout << "Enter Province: ";
    getline(cin, prov);
    
    cout << "Enter City: ";
    getline(cin, city);

    customers[customerCount++] = new Customer(fname, lname, nid, byear, gender, cid, prov, city);
    cout << "Customer added successfully!" << endl;
}

void removeCustomer() {
    string nid;
    cout << "\n===== Remove Customer =====" << endl;
    cout << "Enter National ID to remove: ";
    getline(cin, nid);

    // Find customer
    int index = -1;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->getNationalID() == nid) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Error: Customer not found!" << endl;
        return;
    }

    // Remove associated purchases first
    for (int i = 0; i < purchaseCount; ) {
        if (purchases[i]->getCustomer()->getNationalID() == nid) {
            delete purchases[i];
            // Shift remaining elements
            for (int j = i; j < purchaseCount - 1; j++) {
                purchases[j] = purchases[j + 1];
            }
            purchaseCount--;
        } else {
            i++;
        }
    }

    // Remove the customer
    delete customers[index];
    for (int i = index; i < customerCount - 1; i++) {
        customers[i] = customers[i + 1];
    }
    customerCount--;

    cout << "Customer and all associated purchases removed successfully!" << endl;
}

void addDealer() {
    if (dealerCount >= MAX_SIZE) {
        cout << "Error: Maximum number of dealers reached!" << endl;
        return;
    }

    string did, name, ecode, ofname, olname, prov, city;
    int eyear;

    cout << "\n===== Add New Dealer =====" << endl;
    cout << "Enter Dealer ID: ";
    getline(cin, did);
    
    if (isDealerExists(did)) {
        cout << "Error: Dealer with this ID already exists!" << endl;
        return;
    }

    cout << "Enter Dealer Name: ";
    getline(cin, name);
    
    cout << "Enter Establishment Year: ";
    cin >> eyear;
    
    cout << "Enter Economic Code: ";
    cin.ignore();
    getline(cin, ecode);
    
    cout << "Enter Owner First Name: ";
    getline(cin, ofname);
    
    cout << "Enter Owner Last Name: ";
    getline(cin, olname);
    
    cout << "Enter Province: ";
    getline(cin, prov);
    
    cout << "Enter City: ";
    getline(cin, city);

    dealers[dealerCount++] = new Dealer(did, name, eyear, ecode, ofname, olname, prov, city);
    cout << "Dealer added successfully!" << endl;
}

void removeDealer() {
    string did;
    cout << "\n===== Remove Dealer =====" << endl;
    cout << "Enter Dealer ID to remove: ";
    getline(cin, did);

    // Find dealer
    int index = -1;
    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->getDealerID() == did) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Error: Dealer not found!" << endl;
        return;
    }

    // Remove associated purchases first
    for (int i = 0; i < purchaseCount; ) {
        if (purchases[i]->getDealer()->getDealerID() == did) {
            delete purchases[i];
            // Shift remaining elements
            for (int j = i; j < purchaseCount - 1; j++) {
                purchases[j] = purchases[j + 1];
            }
            purchaseCount--;
        } else {
            i++;
        }
    }

    // Remove the dealer
    delete dealers[index];
    for (int i = index; i < dealerCount - 1; i++) {
        dealers[i] = dealers[i + 1];
    }
    dealerCount--;

    cout << "Dealer and all associated purchases removed successfully!" << endl;
}

void recordPurchase() {
    if (purchaseCount >= MAX_SIZE) {
        cout << "Error: Maximum number of purchases reached!" << endl;
        return;
    }

    string nid, pid, did;
    int quantity;
    string date;

    cout << "\n===== Record New Purchase =====" << endl;
    cout << "Enter Customer National ID: ";
    getline(cin, nid);
    
    cout << "Enter Product ID: ";
    getline(cin, pid);
    
    cout << "Enter Dealer ID: ";
    getline(cin, did);
    
    cout << "Enter Quantity: ";
    cin >> quantity;
    
    cout << "Enter Purchase Date (YYYY/MM/DD or 'today' for current date): ";
    cin.ignore();
    getline(cin, date);

    if (date == "today") {
        date = getCurrentDate();
    }

    // Find customer, product, and dealer
    Customer* customer = nullptr;
    Product* product = nullptr;
    Dealer* dealer = nullptr;

    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->getNationalID() == nid) {
            customer = customers[i];
            break;
        }
    }

    for (int i = 0; i < productCount; i++) {
        if (products[i]->getProductID() == pid) {
            product = products[i];
            break;
        }
    }

    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->getDealerID() == did) {
            dealer = dealers[i];
            break;
        }
    }

    if (customer == nullptr || product == nullptr || dealer == nullptr) {
        cout << "Error: Customer, Product, or Dealer not found!" << endl;
        return;
    }

    try {
        purchases[purchaseCount++] = new Purchase(customer, product, dealer, quantity, date);
        cout << "Purchase recorded successfully!" << endl;
    } catch (invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void totalPurchaseByCustomer() {
    string nid;
    cout << "\n===== Total Purchase Amount by Customer =====" << endl;
    cout << "Enter Customer National ID: ";
    getline(cin, nid);

    float total = 0;
    bool found = false;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->getCustomer()->getNationalID() == nid) {
            total += purchases[i]->getProduct()->getPrice() * purchases[i]->getQuantity();
            found = true;
        }
    }

    if (found) {
        cout << "Total purchase amount for customer: " << total << endl;
    } else {
        cout << "No purchases found for this customer!" << endl;
    }
}

void customersByProduct() {
    string pid;
    cout << "\n===== Customers Who Purchased a Product =====" << endl;
    cout << "Enter Product ID: ";
    getline(cin, pid);

    bool found = false;
    cout << "Customers who purchased this product:" << endl;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->getProduct()->getProductID() == pid) {
            purchases[i]->getCustomer()->showInfo();
            cout << "---------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No customers found for this product!" << endl;
    }
}

void productsByDealer() {
    string did;
    cout << "\n===== Products Sold by a Dealer =====" << endl;
    cout << "Enter Dealer ID: ";
    getline(cin, did);

    bool found = false;
    cout << "Products sold by this dealer:" << endl;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->getDealer()->getDealerID() == did) {
            purchases[i]->getProduct()->showInfo();
            cout << "Quantity: " << purchases[i]->getQuantity() << endl;
            cout << "Date: " << purchases[i]->getDate() << endl;
            cout << "---------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No products found for this dealer!" << endl;
    }
}

void salesCountByProduct() {
    string pid;
    cout << "\n===== Number of Units Sold for a Product =====" << endl;
    cout << "Enter Product ID: ";
    getline(cin, pid);

    int total = 0;
    bool found = false;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->getProduct()->getProductID() == pid) {
            total += purchases[i]->getQuantity();
            found = true;
        }
    }

    if (found) {
        cout << "Total units sold for this product: " << total << endl;
    } else {
        cout << "No sales found for this product!" << endl;
    }
}

void productsByCustomer() {
    string nid;
    cout << "\n===== Products Purchased by a Customer =====" << endl;
    cout << "Enter Customer National ID: ";
    getline(cin, nid);

    bool found = false;
    cout << "Products purchased by this customer:" << endl;

    for (int i = 0; i < purchaseCount; i++) {
        if (purchases[i]->getCustomer()->getNationalID() == nid) {
            purchases[i]->getProduct()->showInfo();
            cout << "Quantity: " << purchases[i]->getQuantity() << endl;
            cout << "Date: " << purchases[i]->getDate() << endl;
            cout << "---------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No products found for this customer!" << endl;
    }
}

void dealerSalesReport() {
    cout << "\n===== Sales Report by Dealer =====" << endl;

    if (dealerCount == 0) {
        cout << "No dealers available!" << endl;
        return;
    }

    for (int i = 0; i < dealerCount; i++) {
        float totalSales = 0;
        for (int j = 0; j < purchaseCount; j++) {
            if (purchases[j]->getDealer()->getDealerID() == dealers[i]->getDealerID()) {
                totalSales += purchases[j]->getProduct()->getPrice() * purchases[j]->getQuantity();
            }
        }
        cout << "Dealer: " << dealers[i]->getDealerID() << " - " << dealers[i]->getDealerID() << endl;
        cout << "Total Sales: " << totalSales << endl;
        cout << "---------------------" << endl;
    }
}

// Helper function implementations
bool isCustomerExists(string nationalID) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->getNationalID() == nationalID) {
            return true;
        }
    }
    return false;
}

bool isProductExists(string productID) {
    for (int i = 0; i < productCount; i++) {
        if (products[i]->getProductID() == productID) {
            return true;
        }
    }
    return false;
}

bool isDealerExists(string dealerID) {
    for (int i = 0; i < dealerCount; i++) {
        if (dealers[i]->getDealerID() == dealerID) {
            return true;
        }
    }
    return false;
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(1900 + ltm->tm_year) + "/" + 
           to_string(1 + ltm->tm_mon) + "/" + 
           to_string(ltm->tm_mday);
}