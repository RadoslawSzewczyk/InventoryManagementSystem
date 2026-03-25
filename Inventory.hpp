#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Item.hpp"
#include "Exceptions.hpp"

class Inventory
{
private:
    std::vector<std::shared_ptr<Item>> items;

public:
    Inventory() = default;

    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;
    Inventory(Inventory&&) noexcept = default;
    Inventory& operator=(Inventory&&) noexcept = default;

    void addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& itemID);
    void updateQuantity(const std::string& itemID, int quantity);
    void displayInventory() const;

    void readFromFile(const std::string& filename);
    void writeToFile(const std::string& filename) const;

    const std::vector<std::shared_ptr<Item>>& getItems() const noexcept { return items; }
    std::vector<std::shared_ptr<Item>>& getItems() noexcept { return items; }
};

template<typename Predicate>
std::vector<std::shared_ptr<Item>> filterItems(const Inventory& inv, Predicate pred)
{
    std::vector<std::shared_ptr<Item>> result;
    std::copy_if(inv.getItems().begin(), inv.getItems().end(), std::back_inserter(result), pred);
    return result;
}

template<typename Key>
void sortItems(Inventory& inv, Key keyFn)
{
    std::sort(inv.getItems().begin(), inv.getItems().end(), keyFn);
}
