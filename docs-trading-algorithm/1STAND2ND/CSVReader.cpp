#include "CSVReader.h"
#include <iostream>
#include <fstream>


CSVReader::CSVReader()  // CSVReader ## constructor
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename) // readCSV ## reads the csv file and returns a vector of OrderBookEntry objects
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        while(std::getline(csvFile, line))
        {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }catch(const std::exception& e)
            {
                std::cout << "CSVReader::readCSV bad data"  << std::endl;
            }
        }// end of while
    }    

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries"  << std::endl;
    return entries; 
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator) // tokenise ## takes a string and a separator and returns a vector of strings
{
   // string vector tokens ## stores the tokens
    std::vector<std::string> tokens; 
    signed int start, end; // int start, end ## used to delineate the position of the tokens
    std::string token;  // ## used to store the token
    start = csvLine.find_first_not_of(separator, 0); // start = csvLine. find_first_not_of (separator)
    do {
        end = csvLine.find_first_of(separator, start);  // end = next 'separator' after start
        if (start == csvLine.length() || start == end) // if start == csvLine. length or start == end ## nothing more to find
            break;
        if (end >= 0) // if end >= 0 ## found a separator
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token); // add found token to vector ## save the token
        start = end + 1; // start = end + 1 ## move past this token
    } while(end > 0); // while (end > 0) ## continue loop condition // while (end != std::string::npos); ## from video pop-up screen
        
    return tokens;
}


OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) // stringsToOBE ## takes a vector of strings and returns an OrderBookEntry object
{
    // OrderBookEntry obe{1, 1, "", "", OrderBookType::bid};

    double price, amount;

    if (tokens.size() != 5) // bad
    {
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    try {
         price = std::stod(tokens[3]);
         amount = std::stod(tokens[4]);
    }catch(const std::exception& e){
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4]<< std::endl; 
        throw;        
    }

    OrderBookEntry obe{price, 
                        amount, 
                        tokens[0],
                        tokens[1], 
                        OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe;
}
     
OrderBookEntry CSVReader::stringsToOBE(std::string priceString,  // stringsToOBE ## takes a vector of strings and returns an OrderBookEntry object
                                    std::string amountString, 
                                    std::string timestamp, 
                                    std::string product, 
                                    OrderBookType orderType)
{
    double price, amount;
    try {
         price = std::stod(priceString);
         amount = std::stod(amountString);
    }catch(const std::exception& e){
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString<< std::endl; 
        throw;        
    }
    OrderBookEntry obe{price, 
                    amount, 
                    timestamp,
                    product, 
                    orderType};
                
    return obe;
}