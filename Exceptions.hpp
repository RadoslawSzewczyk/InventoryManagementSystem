#pragma once
#include <stdexcept>
#include <string>

class InventoryException : public std::runtime_error {
public:
    explicit InventoryException(const std::string& msg) : std::runtime_error(msg) {}
};

class ItemNotFoundException : public InventoryException {
public:
    explicit ItemNotFoundException(const std::string& msg) : InventoryException(msg) {}
};

class DuplicateItemException : public InventoryException {
public:
    explicit DuplicateItemException(const std::string& msg) : InventoryException(msg) {}
};

class InvalidValueException : public InventoryException {
public:
    explicit InvalidValueException(const std::string& msg) : InventoryException(msg) {}
};
