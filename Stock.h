//
// Created by Pushp Kumar on 29/05/2017.
//

#ifndef STOCKMARKET_STOCK_H
#define STOCKMARKET_STOCK_H

#include <string>
#include <vector>
#include <ostream>
#include <memory>
#include <algorithm>

#include "Trade.h"

enum STOCK_TYPE{STOCK_TYPE_UNKNOWN, STOCK_TYPE_COMMON, STOCK_TYPE_PREFERRED};


class Stock {
private:
    STOCK_TYPE eStockType = STOCK_TYPE_UNKNOWN;
    std::string strSymbol = "";
    double dLastDividend = 0.0;
    double dFixedDividend = 0.0;
    double dParValue =0.0;

    std::shared_ptr<std::vector<Trade>> trades = std::make_shared<std::vector<Trade>>(); //must be sorted by ascending timestamp
public:
    STOCK_TYPE getStockType() const;
    const std::string &getSymbol() const;


    double getLastDividend() const;
    void setLastDividend(double dLastDividend);

    double getFixedDividend() const;
    void setFixedDividend(double dFixedDividend);

    double getParValue() const;
    void setParValue(double dParValue);

    Stock();

    Stock(const Stock&);

    Stock(const std::string& _strSymbol, const STOCK_TYPE _eStockType, const double _dLastDividend, const double _dFixedDividend, const double _dParValue);

    virtual ~Stock();

    double calcDividend(double price);

    double calcPERatio(double price);

    double calcWeightedStockPrices(unsigned long long int lastXXMilisecond);

    const std::shared_ptr<std::vector<Trade>> &getTrades() const { return trades; }
    std::shared_ptr<std::vector<Trade>> getTrades() { return trades; }


    friend std::ostream &operator<<(std::ostream &os, const Stock &stock);
    void operator = (const Stock& st);

    template<typename FuncType>
    friend void ProcessTrades(std::shared_ptr<Stock> stock, FuncType f);
};

template<typename FuncType>
void ProcessTrades(std::shared_ptr<Stock> stock, FuncType f)
{
    std::shared_ptr<std::vector<Trade>> trades = stock->getTrades();
    std::for_each(trades->begin(), trades->end(), f);

}

#endif //STOCKMARKET_STOCK_H
