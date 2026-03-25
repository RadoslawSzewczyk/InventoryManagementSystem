#include "Inventory.hpp"
#include <iostream>
#include <string>

void printMenu()
{
    std::cout << "\n--- Inventory Menu ---\n";
    std::cout << "1. Add Electronics\n"; 
    std::cout << "2. Add Grocery\n";
    std::cout << "3. Remove Item\n";
    std::cout << "4. Update Quantity\n";
    std::cout << "5. Display Inventory\n";
    std::cout << "6. Read from File\n";
    std::cout << "7. Write to File\n";
    std::cout << "8. Find Most Expensive Item\n";
    std::cout << "9. Find Items Below Quantity Threshold\n";
    std::cout << "10. Sort by Price\n";
    std::cout << "11. Exit\n";
    std::cout << "Select an option: ";
}

int main()
{
    Inventory inv;
    
    Inventory tempInv;
    tempInv.addItem(makeElectronics("E_TEMP", "Temp", 1, 1.0, 1));
    inv = std::move(tempInv);
    inv.removeItem("E_TEMP");

    int choice;
    while (true) {
        printMenu();
        if (!(std::cin >> choice)) break;

        try {
            if (choice == 1) {
                std::string id, name; int qty, w; double price;
                std::cout << "ID, Name, Qty, Price, Warranty (Months): ";
                std::cin >> id >> name >> qty >> price >> w;
                inv.addItem(makeElectronics(id, name, qty, price, w));
            } else if (choice == 2) {
                std::string id, name, exp; int qty; double price;
                std::cout << "ID, Name, Qty, Price, Expiration: ";
                std::cin >> id >> name >> qty >> price >> exp;
                inv.addItem(makeGrocery(id, name, qty, price, exp));
            } else if (choice == 3) {
                std::string id;
                std::cout << "ID to remove: ";
                std::cin >> id;
                inv.removeItem(id);
                std::cout << "Item removed.\n";
            } else if (choice == 4) {
                std::string id; int qty;
                std::cout << "ID, New Quantity: ";
                std::cin >> id >> qty;
                inv.updateQuantity(id, qty);
                std::cout << "Quantity updated.\n";
            } else if (choice == 5) {
                inv.displayInventory();
            } else if (choice == 6) {
                std::string filename;
                std::cout << "Filename: "; std::cin >> filename;
                inv.readFromFile(filename);
            } else if (choice == 7) {
                std::string filename;
                std::cout << "Filename: "; std::cin >> filename;
                inv.writeToFile(filename);
            } else if (choice == 8) {
                if (inv.getItems().empty()) throw InventoryException("Inventory is empty.");
                auto maxIt = std::max_element(inv.getItems().begin(), inv.getItems().end(),
                    [](const std::shared_ptr<Item>& a, const std::shared_ptr<Item>& b) {
                        return a->getPrice() < b->getPrice();
                    });
                std::cout << "Most Expensive:\n";
                (*maxIt)->display();
            } else if (choice == 9) {
                int threshold;
                std::cout << "Threshold: "; std::cin >> threshold;
                auto filtered = filterItems(inv, [threshold](const std::shared_ptr<Item>& i) {
                    return i->getQuantity() < threshold;
                });
                for (const auto& item : filtered) item->display();
            } else if (choice == 10) {
                sortItems(inv, [](const std::shared_ptr<Item>& a, const std::shared_ptr<Item>& b) {
                    return a->getPrice() < b->getPrice();
                });
                std::cout << "Sorted by price.\n";
            } else if (choice == 11) {
                break;
            } else {
                std::cout << "Invalid choice.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}
