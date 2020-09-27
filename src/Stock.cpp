#include "Stock.hpp"

Stock::Stock(std::string symbol) {
    name = symbol;
}

Stock::Stock(std::string symbol, double average_low, double average_high) {
    name = symbol;
    low = average_low;
    high = average_high;
}

std::string Stock::getSymbol() {
    return name;
}

bool Stock::buy() {
    if (current_price <= low) {
        return true;
    }
    return false;
}

bool Stock::sell() {
    if (current_price >= high) {
        return true;
    }
    return false;
}

double Stock::price() { return current_price; }

double Stock::getLow() { return low; }

double Stock::getHigh() { return high; }

double Stock::getPrice() { return current_price; }

double Stock::getLastPrice() { return last_price; }

void Stock::setLow(double new_low) { low = new_low; }

void Stock::setHigh(double new_high) { high = new_high; }

void Stock::setPrice(double price) { last_price = current_price; current_price = price;}