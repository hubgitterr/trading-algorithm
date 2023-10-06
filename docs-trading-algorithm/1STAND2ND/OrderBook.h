#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
    /** construct, reading a csv data file */
        OrderBook(std::string filename);
    /** return vector of all know products in the dataset*/
        std::vector<std::string> getKnownProducts();
    /** return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type, 
                                              std::string product, 
                                              std::string timestamp);

        /** returns the earliest time in the orderbook*/
        std::string getEarliestTime();
        /** returns the next time after the 
         * sent time in the orderbook  
         * If there is no next timestamp, wraps around to the start
         * */
        std::string getNextTime(std::string timestamp);

        void insertOrder(OrderBookEntry& order); // insertOrder ## inserts an order into the order book

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp); // matchAsksToBids ## matches asks to bids

        static double getHighPrice(std::vector<OrderBookEntry>& orders); // getHighPrice ## returns the highest price in a vector of orders
        static double getLowPrice(std::vector<OrderBookEntry>& orders); // getLowPrice ## returns the lowest price in a vector of orders

        std::vector<Candlestick> getCandlesticks() const; // getCandlesticks ## returns the candlesticks
    
    private:
        std::vector<OrderBookEntry> orders; // orders ## the orders in the order book
        std::vector<Candlestick> candlesticks; // Add this line

        void computeCandlesticks(); // computeCandlesticks ## computes the candlesticks


};
