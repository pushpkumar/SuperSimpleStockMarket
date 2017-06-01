//
// Created by Pushp Kumar on 29/05/2017.
//
#include<iostream>
#include "Stock.h"
#include "StockMarketException.h"

const char* STOCK_TYPE_NAMES[] {"STOCK_TYPE_UNKNOWN","STOCK_TYPE_COMMON","STOCK_TYPE_PREFERRED"};

Stock::Stock()
{
}


Stock::Stock(const std::string& _strSymbol, const STOCK_TYPE _eStockType, const double _dLastDividend, const double _dFixedDividend, const double _dParValue)
 : strSymbol(_strSymbol), eStockType(_eStockType), dLastDividend(_dLastDividend), dFixedDividend(_dFixedDividend), dParValue(_dParValue)
{
//Assumption if last dividend is Zero approximate this with a small value 0.01
//so that can avoid divide by zero exception
if(dLastDividend == 0.0)
    dLastDividend = 0.01;
}

Stock::~Stock()
{

}

STOCK_TYPE Stock::getStockType() const {
    return eStockType;
}

const std::string &Stock::getSymbol() const {
    return strSymbol;
}

double Stock::getLastDividend() const {
    return dLastDividend;
}

void Stock::setLastDividend(double dLastDividend) {
    Stock::dLastDividend = dLastDividend;
}

double Stock::getFixedDividend() const {
    return dFixedDividend;
}

void Stock::setFixedDividend(double dFixedDividend) {
    Stock::dFixedDividend = dFixedDividend;
}

double Stock::getParValue() const {
    return dParValue;
}

void Stock::setParValue(double dParValue) {
    Stock::dParValue = dParValue;
}

double Stock::calcDividend(double price)  {

    if (price == 0.0)
        throw StockMarketException("Division zero Error!");
    else if (price < 0.0)
        throw StockMarketException("Negative price!");

    double dDiv = 0.0;

    switch(eStockType)
    {

        case STOCK_TYPE_COMMON:
            dDiv = dLastDividend / price;
            break;

        case STOCK_TYPE_PREFERRED:
            dDiv = dFixedDividend * dParValue / price;
            break;
        case STOCK_TYPE_UNKNOWN:
            throw StockMarketException("Unknown Stock Type!");
            break;
    }

    return dDiv;
}

double Stock::calcPERatio(double price) {
    double dDiv = calcDividend(price);

    if (dDiv == 0.0)
        throw StockMarketException("Division zero Error!");

    return price / dDiv;
}

std::ostream &operator<<(std::ostream &os, const Stock &stock) {

    os << "eStockType: " << STOCK_TYPE_NAMES[stock.eStockType] << " strSymbol: " << stock.strSymbol << " dLastDividend: "
       << stock.dLastDividend << " dFixedDividend: " << stock.dFixedDividend << " dParValue: " << stock.dParValue << std::endl;

    for(Trade t : *stock.getTrades()
        )
        os << t << std::endl;
    return os;
}


double Stock::calcWeightedStockPrices(unsigned long long int lastXXMilisecond) {

    double TotalStockPrice(0.0), TotalQuantity(0.0);

    for(auto it = trades->rbegin(); it  != trades->rend(); ++it)
    {
        if (it->isValid(lastXXMilisecond))
        {
            TotalStockPrice += it->getPrice() * it->getNoOfShare();
            TotalQuantity += it->getNoOfShare();
        }
        else break;
    }

    if(TotalQuantity == 0.0)
        throw StockMarketException("Zero stock quantity");

    return TotalStockPrice / TotalQuantity;
}
