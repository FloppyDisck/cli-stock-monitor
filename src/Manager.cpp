#include <iostream>
#include "Manager.hpp"
Manager::Manager(std::vector<std::string>* stock_names, uint max_sample_size, std::string time_frame) {

    // Parse the required environment variables using the supplied helper utility
    env = alpaca::Environment();
    if (auto status = env.parse(); !status.ok()) {
        std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
        // if something bad happens
    }

    // Instantiate an instance of the API client
    auto client = alpaca::Client(env);

    int n = 0;
    while (n < stock_names->size()) {
        // Max query size is 200, so we get as many as we can
        int m = (stock_names->size() - n > 200) ? 200 : stock_names->size() - n;

        // Slice from n to m
        std::vector<std::string> current(stock_names->begin() + n, stock_names->begin() + m);

        // Query the stocks
        auto bars_response = client.getBars(current, "", "", "", "", time_frame, max_sample_size);
        // Handle error
        if (auto status = bars_response.first; !status.ok()) { 
            return;
        }

        for (int i = 0; i < current.size(); i++) {
            //Handle the max min and other stuff
            auto bars = bars_response.second.bars.at(current.at(i));
            int total_values = bars.size();

            // Get average
            double average = 0;
            for (int j = 0; j < total_values; j++) {
                average += bars.at(j).open_price;
            }
            average = average / total_values;

            // Get average of both high values and low
            double average_high = 0, average_low = 0;
            int total_high = 0, total_low = 0;

            for (int j = 0; j < total_values; j++) {
                double p = bars.at(j).open_price;

                if (p > average) {
                    total_high++;
                    average_high += p;
                } else {
                    total_low++;
                    average_low += p;
                }
            }
            average_high = average_high / total_high;
            average_low = average_low / total_low;

            stonks.push_back(new Stock(current.at(i), average_low, average_high));
        }

        n = m + 1;
    }

    stonk_names = stock_names;

    //Start the screen
    initscr();
    clear();
    noecho();
    start_color();
    use_default_colors();
    init_pair(RED_TEXT, COLOR_RED, -1);
    init_pair(GREEN_TEXT, COLOR_GREEN, -1);
    init_pair(GRAY_TEXT, COLOR_WHITE, -1);

}

void Manager::update() {
    // Prints the information
    //Header
    clear();
    attron(COLOR_PAIR(GRAY_TEXT));
    mvprintw(0, 0, "Stock");
    mvprintw(0, 8, "Option");
    mvprintw(0, 16, "Price");
    mvprintw(0, 31, "Low");
    mvprintw(0, 46, "High");


    auto client = alpaca::Client(env);

    int n = 0;
    while (n < stonks.size()) {
        // Max query size is 200, so we get as many as we can
        int m = (stonks.size() - n > 200) ? 200 : stonks.size() - n;

        // Slice from n to m
        std::vector<std::string> current(stonk_names->begin() + n, stonk_names->begin() + m);

        // Query the stocks
        auto bars_response = client.getBars(current, "", "", "", "", "minute", 1U);
        // Handle error
        if (auto status = bars_response.first; !status.ok()) { 
            return;
        }

        for (int i = 0; i < current.size(); i++) {
            //Handle the max min and other stuff
            auto bars = bars_response.second.bars.at(current.at(i));

            // Its all being done linearly
            stonks.at(n+i)->setPrice(bars.at(0).open_price);

            //Handle writing here
            attron(COLOR_PAIR(GRAY_TEXT));
            mvprintw(n+i+1, 0, stonks.at(n+i)->getSymbol().c_str());
            mvprintw(n+i+1, 31, std::to_string(stonks.at(n+i)->getLow()).c_str());
            mvprintw(n+i+1, 46, std::to_string(stonks.at(n+i)->getHigh()).c_str());

            if (stonks.at(n+i)->buy()) {
                attron(COLOR_PAIR(GREEN_TEXT));
                mvprintw(n+i+1, 8, "BUY");
            }
            else if (stonks.at(n+i)->sell()) {
                attron(COLOR_PAIR(RED_TEXT));
                mvprintw(n+i+1, 8, "SELL");
            }
            else {
                attron(COLOR_PAIR(GRAY_TEXT));
                mvprintw(n+i+1, 8, "HOLD");
            }


            if (stonks.at(n+i)->getPrice() > stonks.at(n+i)->getLastPrice()) {
                attron(COLOR_PAIR(GREEN_TEXT));
            } else if (stonks.at(n+i)->getPrice() < stonks.at(n+i)->getLastPrice()) {
                attron(COLOR_PAIR(RED_TEXT));
            } else {
                attron(COLOR_PAIR(GRAY_TEXT));
            }
            mvprintw(n+i+1, 16, std::to_string(stonks.at(n+i)->getPrice()).c_str());  

        }
        refresh();

        n = m + 1;
    }
}

void Manager::close() {
    endwin();
}

std::vector<Stock*>* Manager::getStocks() { return &stonks; }