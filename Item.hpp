#pragma once
#include <string>
#include <optional>
#include <memory>
#include "Exceptions.hpp"

class Item
{
private:
    std::string itemID;
    std::string name;
    int quantity;
    double price;

public:
    Item(std::string id, std::string n, int q, double p);
    virtual ~Item() = default;

    std::string getID() const noexcept { return itemID; }
    std::string getName() const noexcept { return name; }
    int getQuantity() const noexcept { return quantity; }
    double getPrice() const noexcept { return price; }

    void setQuantity(int q);
    void setPrice(double p);

    virtual void display() const = 0;
    virtual std::string category() const = 0;
    virtual std::optional<std::string> findAttribute(const std::string& key) const = 0;
};

class Electronics : public Item
{
private:
    int warrantyMonths;
public:
    Electronics(std::string id, std::string n, int q, double p, int w);
    void display() const override;
    std::string category() const override { return "Electronics"; }
    std::optional<std::string> findAttribute(const std::string& key) const override;
};

class Grocery : public Item
{
private:
    std::string expirationDate;
public:
    Grocery(std::string id, std::string n, int q, double p, std::string exp);
    void display() const override;
    std::string category() const override { return "Grocery"; }
    std::optional<std::string> findAttribute(const std::string& key) const override;
};

std::shared_ptr<Item> makeElectronics(const std::string& id, const std::string& name, int qty, double price, int warrantyMonths);
std::shared_ptr<Item> makeGrocery(const std::string& id, const std::string& name, int qty, double price, const std::string& expDate);
