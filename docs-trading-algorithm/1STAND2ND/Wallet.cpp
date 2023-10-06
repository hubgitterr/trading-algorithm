#include "Wallet.h"
#include <iostream>
#include "CSVReader.h"

Wallet::Wallet()
{


}

void Wallet::insertCurrency(std::string type, double amount) // insertCurrency ## adds a currency to the wallet or increases the balance if it is already there
{
    double balance;
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (currencies.count(type) == 0) // not there yet
    {
        balance = 0;
    }
    else { // is there 
        balance = currencies[type];
    }
    balance += amount; 
    currencies[type] = balance; 
}

bool Wallet::removeCurrency(std::string type, double amount) // removeCurrency ## removes a currency from the wallet or decreases the balance if it is already there
{
    if (amount < 0)
    {
        return false; 
    }
    if (currencies.count(type) == 0) // not there yet
    {
        
        return false;
    }
    else { // is there - do  we have enough
        if (containsCurrency(type, amount))// we have enough
        {
            
            currencies[type] -= amount;
            return true;
        } 
        else // they have it but not enough.
            return false; 
    }
}

bool Wallet::containsCurrency(std::string type, double amount) // containsCurrency ## checks if the wallet contains a currency and if the amount is greater than or equal to the amount sent
{
    if (currencies.count(type) == 0) // not there yet
        return false;
    else 
        return currencies[type] >= amount;
    
}

std::string Wallet::toString() // toString ## returns a string representation of the wallet in the format "currency : amount\n" for each currency in the wallet
{
    std::string s;
    for (std::pair<std::string,double> pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
    // return "whazzuuuuppppp";
}

bool Wallet::canFulfillOrder(OrderBookEntry order) // canFulfillOrder ## checks if the wallet contains the currency and amount needed to fulfill an order (ask or bid)
{
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    // ask
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }
    // bid
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }


    return false; 
}
      

void Wallet::processSale(OrderBookEntry& sale) // processSale ## updates the wallet based on a sale (ask or bid) that has been fulfilled 
{
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    // ask
    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;

    }
    // bid
    if (sale.orderType == OrderBookType::bidsale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}
std::ostream& operator<<(std::ostream& os,  Wallet& wallet) // operator<< ## overloads the << operator to print a wallet to the console 
{
    os << wallet.toString();
    return os;
}

