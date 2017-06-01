//
// Created by Pushp Kumar on 29/05/2017.
//


#include "Trade.h"
#include <sys/time.h>

const char* TRADE_TYPE_NAMES[] {"TRADE_UNKNOWN", "TRADE_BUY", "TRADE_SELL"};

Trade::Trade(unsigned long long int _timestamp, TRADE_TYPE _eTradeType, int _iShare, double _dPrice)
        : timestamp(_timestamp), eTradeType(_eTradeType), iNoOfShare(_iShare), dPrice(_dPrice)
{

}

Trade::Trade(TRADE_TYPE _eTradeType, int _iShare, double _dPrice) : eTradeType(_eTradeType), iNoOfShare(_iShare), dPrice(_dPrice)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    timestamp = tp.tv_sec * 1000 * 1000 + tp.tv_usec ;
}

unsigned long long int Trade::getTimestamp() const {
    return timestamp;
}

void Trade::setTimestamp(unsigned long long int timestamp) {
    Trade::timestamp = timestamp;
}

int Trade::getNoOfShare() const {
    return iNoOfShare;
}

void Trade::setNoOfShare(int iNoOfShare) {
    Trade::iNoOfShare = iNoOfShare;
}

double Trade::getPrice() const {
    return dPrice;
}

void Trade::setPrice(double dPrice) {
    Trade::dPrice = dPrice;
}

TRADE_TYPE Trade::getTradeType() const {
    return eTradeType;
}

void Trade::setTradeType(TRADE_TYPE eTradeType) {
    Trade::eTradeType = eTradeType;
}

std::ostream &operator<<(std::ostream &os, const Trade &trade) {
    char tmbuf[64];
    struct tm *nowtm;

    time_t nowtime = trade.timestamp / 1000000;
    nowtm = localtime(&nowtime);

    strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);


    os << "timestamp: " << tmbuf << " (Micro sec:" << (trade.timestamp % 1000000) << ") iNoOfShare: " << trade.iNoOfShare << " dPrice: " << trade.dPrice
       << " eTradeType: " << TRADE_TYPE_NAMES[trade.eTradeType];

    return os;
}

bool Trade::operator<(const Trade &rhs) const {
    return timestamp < rhs.timestamp;
}

bool Trade::operator>(const Trade &rhs) const {
    return rhs < *this;
}

bool Trade::operator<=(const Trade &rhs) const {
    return !(rhs < *this);
}

bool Trade::operator>=(const Trade &rhs) const {
    return !(*this < rhs);
}

bool Trade::isValid(unsigned long long validFrom) {
    return timestamp >= validFrom;
}

