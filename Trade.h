//
// Created by Pushp Kumar on 29/05/2017.
//

#ifndef STOCKMARKET_TRADE_H
#define STOCKMARKET_TRADE_H


#include <ostream>

enum TRADE_TYPE{TRADE_UNKNOWN, TRADE_BUY, TRADE_SELL};

class Trade
  {
private :
    unsigned long long int timestamp = 0; //microsec since the Epoch 1970-01-01 00:00:00 +0000 (UTC).
    int iNoOfShare = 0.0;
    double dPrice = 0.0;
    TRADE_TYPE eTradeType = TRADE_UNKNOWN;
public:
    unsigned long long int getTimestamp() const;

    void setTimestamp(unsigned long long int timestamp);

    int getNoOfShare() const;

    void setNoOfShare(int dNoOfShare);

    double getPrice() const;

    void setPrice(double dPrice);

    TRADE_TYPE getTradeType() const;

    void setTradeType(TRADE_TYPE eTradeType);

    bool operator<(const Trade &rhs) const;

    bool operator>(const Trade &rhs) const;

    bool operator<=(const Trade &rhs) const;

    bool operator>=(const Trade &rhs) const;

private:

    Trade() {};
public:
    Trade(unsigned long long _timestamp, TRADE_TYPE _eTradeType, int _iShare, double _dPrice);

    Trade(TRADE_TYPE _eTradeType, int _iShare, double _dPrice);

    bool isValid(unsigned long long validFrom);

    friend std::ostream &operator<<(std::ostream &os, const Trade &trade);

};
#endif //STOCKMARKET_TRADE_H
