#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>


class CSVReader // CSVReader ## reads a csv file and returns a vector of OrderBookEntry objects
{
    public:
        CSVReader(); 

        static std::vector<OrderBookEntry> readCSV(std::string csvFile); 
        static std::vector<std::string> tokenise(std::string csvLine, char separator);
        
        static OrderBookEntry stringsToOBE(std::string price, 
                                            std::string amount, 
                                            std::string timestamp, 
                                            std::string product, 
                                            OrderBookType OrderBookType);

    private:
        // static std::vector<std::string> tokenise(std::string csvLine, char separator);
        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
     
};