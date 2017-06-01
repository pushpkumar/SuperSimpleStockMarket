//
// Created by Pushp Kumar on 29/05/2017.
//

#include "StockMarketException.h"


StockMarketException::StockMarketException(const char* exception) {
    strWhat = exception;
}


StockMarketException::~StockMarketException() {

}

const char *StockMarketException::what() {
    return strWhat.c_str();
}
