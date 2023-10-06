#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain // MerkelMain ## main class for the program
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);

        void printCandlestickPlot(); // printCandlestickPlot ## prints the candlestick plot

        // void computeCandlestickData(std::vector<OrderBookEntry>& entries, int timeframeSeconds);

        std::string currentTime; // currentTime ## the current time
        
        OrderBook orderBook{"20200601.csv"}; // orderBook ## the order book
        

        Wallet wallet; // wallet ## the wallet


};