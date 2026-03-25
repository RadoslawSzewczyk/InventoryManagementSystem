#include "Inventory.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void Inventory::addItem(std::shared_ptr<Item> item) {
    for (const auto& i : items) {
        if (i->getID() == item->getID()) {
            throw DuplicateItemException("Item with ID '" + item->getID() + "' already exists in inventory.");
        }
    }
    items.push_back(std::move(item));
}

void Inventory::removeItem(const std::string& itemID) {
    auto it = std::remove_if(items.begin(), items.end(), 
        [&itemID](const std::shared_ptr<Item>& i) { return i->getID() == itemID; });
    
    if (it == items.end()) {
        throw ItemNotFoundException("Item with ID '" + itemID + "' not found.");
    }
    items.erase(it, items.end());
}

void Inventory::updateQuantity(const std::string& itemID, int quantity) {
    for (auto& i : items) {
        if (i->getID() == itemID) {
            i->setQuantity(quantity);
            return;
        }
    }
    throw ItemNotFoundException("Item with ID '" + itemID + "' not found.");
}

void Inventory::displayInventory() const {
    for (const auto& i : items) {
        i->display();
        std::cout << "-----------------------\n";
    }
}

void Inventory::readFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file) throw InventoryException("Could not open file for reading.");

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, cat, name, extra, qtyStr, priceStr;
        
        std::getline(ss, id, ',');
        std::getline(ss, cat, ',');
        std::getline(ss, name, ',');
        std::getline(ss, qtyStr, ',');
        std::getline(ss, priceStr, ',');
        std::getline(ss, extra, ',');

        try {
            int qty = std::stoi(qtyStr);
            double price = std::stod(priceStr);

            if (cat == "Electronics") {
                int warranty = std::stoi(extra);
                addItem(makeElectronics(id, name, qty, price, warranty));
            } else if (cat == "Grocery") {
                addItem(makeGrocery(id, name, qty, price, extra));
            }
        } catch (const std::exception&) {
        }
    }
}

void Inventory::writeToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file) throw InventoryException("Could not open file for writing.");

    for (const auto& i : items) {
        file << i->getID() << "," << i->category() << "," << i->getName() << ","
             << i->getQuantity() << "," << i->getPrice() << ",";
        
        if (i->category() == "Electronics") {
            file << i->findAttribute("warranty").value_or("0") << "\n";
        } else {
            file << i->findAttribute("expiration").value_or("") << "\n";
        }
    }
}
