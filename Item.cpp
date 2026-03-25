#include "Item.hpp"
#include <iostream>

Item::Item(std::string id, std::string n, int q, double p) : itemID(std::move(id)), name(std::move(n)) {
    setQuantity(q);
    setPrice(p);
}

void Item::setQuantity(int q) {
    if (q < 0) throw InvalidValueException("Quantity cannot be negative.");
    quantity = q;
}

void Item::setPrice(double p) {
    if (p < 0.0) throw InvalidValueException("Price cannot be negative.");
    price = p;
}

Electronics::Electronics(std::string id, std::string n, int q, double p, int w)
    : Item(std::move(id), std::move(n), q, p), warrantyMonths(w) {}

void Electronics::display() const {
    std::cout << "[Electronics] ID: " << getID() << " | Name: " << getName() << "\n"
              << "Qty: " << getQuantity() << " | Price: " << getPrice() 
              << " | Warranty: " << warrantyMonths << " months\n";
}

std::optional<std::string> Electronics::findAttribute(const std::string& key) const {
    if (key == "warranty") return std::to_string(warrantyMonths);
    return std::nullopt;
}

Grocery::Grocery(std::string id, std::string n, int q, double p, std::string exp)
    : Item(std::move(id), std::move(n), q, p), expirationDate(std::move(exp)) {}

void Grocery::display() const {
    std::cout << "[Grocery] ID: " << getID() << " | Name: " << getName() << "\n"
              << "Qty: " << getQuantity() << " | Price: " << getPrice() 
              << " | Expires: " << expirationDate << "\n";
}

std::optional<std::string> Grocery::findAttribute(const std::string& key) const {
    if (key == "expiration") return expirationDate;
    return std::nullopt;
}

std::shared_ptr<Item> makeElectronics(const std::string& id, const std::string& name, int qty, double price, int warrantyMonths) {
    return std::make_shared<Electronics>(id, name, qty, price, warrantyMonths);
}

std::shared_ptr<Item> makeGrocery(const std::string& id, const std::string& name, int qty, double price, const std::string& expDate) {
    return std::make_shared<Grocery>(id, name, qty, price, expDate);
}
