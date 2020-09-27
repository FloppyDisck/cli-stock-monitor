#ifndef MANAGER_HPP
#define MANAGER_HPP
#include <vector>
#include <string>
#include <ncurses.h>

#include "Stock.hpp"

#include "alpaca/client.h"
#include "alpaca/config.h"

#define RED_TEXT 1
#define GREEN_TEXT 2
#define GRAY_TEXT 3

class Manager{
    public:
        Manager(std::vector<std::string>* stock_names, uint max_sample_size = 1000U, std::string time_frame = "1D");
        void update();
        void close();
        std::vector<Stock*>* getStocks();
    private:
        std::vector<Stock*> stonks = {};
        std::vector<std::string>* stonk_names;
        alpaca::Environment env;
};
#endif