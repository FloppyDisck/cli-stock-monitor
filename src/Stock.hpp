#ifndef STOCK_HPP
#define STOCK_HPP
#include <string>
class Stock {
    public:
        Stock(std::string symbol);
        Stock(std::string symbol, double average_low, double average_high);
        std::string getSymbol();
        bool buy();
        bool sell();
        double price();
        double getLow();
        double getHigh();
        double getPrice();
        double getLastPrice();
        void setLow(double low);
        void setHigh(double high);
        void setPrice(double price);
    private:
        std::string name;
        double low;
        double high;
        double current_price = 0;
        double last_price;

};
#endif