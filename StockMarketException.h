//
// Created by Pushp Kumar on 29/05/2017.
//

#ifndef STOCKMARKET_STOCKMARKETEXCEPTION_H
#define STOCKMARKET_STOCKMARKETEXCEPTION_H

#include <exception>
#include <string>

class StockMarketException : public std::exception
{
private:
    std::string strWhat;

    StockMarketException() {};
public:
    StockMarketException(const char* exception);

    virtual ~StockMarketException();

    const char *what() ;

};

#endif //STOCKMARKET_STOCKMARKETEXCEPTION_H
