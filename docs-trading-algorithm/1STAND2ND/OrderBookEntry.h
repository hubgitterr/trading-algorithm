#pragma once

#include <string>


enum class OrderBookType {bid, ask, unknown, asksale, bidsale}; // enum class OrderBookType ## enum class is a type that can only be one of a few values

class OrderBookEntry // class is a blueprint for an object 
{
    public:  // public means that the attributes and methods are accessible from outside the class  
        
        OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType, 
                        std::string username = "dataset");
        
        static OrderBookType stringToOrderBookType(std::string s);

        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2) // compareByTimestamp ## compares two OrderBookEntry objects by timestamp
        {
            return e1.timestamp < e2.timestamp;
        }  
        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
         static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }

        double price; 
        double amount; 
        std::string timestamp; 
        std::string product; 
        OrderBookType orderType; 
        std::string username;
};

struct Candlestick { // struct Candlestick ## a struct is a blueprint for a simple object that only contains attributes and no methods 
       double open;
       double close;
       double high;
       double low;
       std::string timestamp;
   };
