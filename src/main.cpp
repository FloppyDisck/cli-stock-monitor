#include "Manager.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include <iostream>

int main(int argc, char* argv[]) {
    std::vector<std::string> stonks_names = {};

    // Read file with stocks and init each one
    std::string s;
    std::ifstream file ("stocks.txt");

    if (file.is_open()) {

        while ( getline (file,s) ) {
            stonks_names.push_back(s);
        }

        file.close();
    }

    Manager manager(&stonks_names, 10U);

    auto temp = manager.getStocks();

    //First time run two times for updated numbers
    manager.update();
    while(true) {
        manager.update();
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::minutes(1));   
    }
}
