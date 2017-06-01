
#include <iostream>
#include <fstream>
#include <map>
#include <random>
#include <sys/time.h>

#include "Stock.h"
#include <sys/time.h>
#include "StockMarketException.h"

#define NUMBER_OF_TRADES_FOR_A_STOCK_SAMPLE 1500
using namespace std;

double calcWeightedStockPrices(shared_ptr<Stock> &pStock);
void generateTrades(shared_ptr<Stock>);
void generateStocks(map<string, shared_ptr<Stock>>& stockData);
double calcGeometricMean(map<string, shared_ptr<Stock>>& stockData);



int main() {
    cout << "Stock Market initializing market data..." << endl;

    //map for each stock & Stock data structure will hold trade vector for this stock
    map<string, shared_ptr<Stock>> stockData;

    //Redirect Cout to a file so that can investigate output
    std::ofstream out("C:\\StockMarketOutput.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

     generateStocks(stockData);

    for_each(stockData.begin(), stockData.end(), [](pair<string, shared_ptr<Stock>> item){
        shared_ptr<Stock> stock = item.second;

        ProcessTrades(stock, [stock](Trade trade) {
            try {
                cout << "STOCK:" << stock->getSymbol() << " " << trade << endl;

                cout << "\t Dividend:" << stock->calcDividend(trade.getPrice()) << endl;

                cout << "\t PE Ratio:" << stock->calcPERatio(trade.getPrice()) << endl;

            }
            catch(StockMarketException &e)
            {
                cout <<  e.what() << " Stock:" << stock->getSymbol() << endl;

            }
        });
    });


    struct timeval tp;
    gettimeofday(&tp, NULL);
    unsigned long long int last15minute = tp.tv_sec * 1000 *1000 + tp.tv_usec - (15*1*60*1000*1000);
   // unsigned long long int last30Milisecond = tp.tv_sec * 1000 * 1000 + tp.tv_usec - 30000;

    for_each(stockData.begin(), stockData.end(), [last15minute](pair<string, shared_ptr<Stock>> item){
        try{
            cout << "Weighted Stock Price for " << item.first << ":" << item.second->calcWeightedStockPrices(last15minute) << endl;
            }
        catch(StockMarketException &e)
        {
            cout <<  e.what() << " Stock:" << item.first << endl;

        }
    });

    cout << "Geometric Mean of Index is : " << calcGeometricMean(stockData) << endl;

    std::cout.rdbuf(coutbuf);
    cout << "About to leave Main Check Log in   C:\\StockMarketOutput.txt."<<endl;
    return 0;
}


void generateTrades(shared_ptr<Stock> stock)
{
    shared_ptr<vector<Trade>> t = stock->getTrades();

    while(t->size() < NUMBER_OF_TRADES_FOR_A_STOCK_SAMPLE)
    {
        struct timeval tp;
        gettimeofday(&tp, NULL);

        //random number between 1-100
        int random100 = tp.tv_usec % 99+1;

        TRADE_TYPE  eTradeType = TRADE_UNKNOWN;
        (random100 % 2) ? eTradeType = TRADE_BUY : eTradeType = TRADE_SELL;

        double price = stock->getParValue() + (stock->getParValue() * (random100 % 10)) / 100.0;
        int share = random100;

        t->push_back(Trade(eTradeType, share, price));
    }

    //Calls friend <<operator function of Stock which will call  <<of trades
    cout << *stock << endl;
}

/*for each stock it will create 1500 record of trades(arbitrary value) using define value NUMBER_OF_TRADES_FOR_A_STOCK_SAMPLE
 * in real world scenario this will feed from some third party software
 */
void generateStocks(map<string, shared_ptr<Stock>>& stockData)
{
    stockData["TEA"] = make_shared<Stock>("TEA",STOCK_TYPE_COMMON,0,0,100);
    stockData["POP"] = make_shared<Stock>("POP",STOCK_TYPE_COMMON,8,0,100);
    stockData["ALE"] = make_shared<Stock>("ALE",STOCK_TYPE_COMMON,23,0,60);
    stockData["GIN"] = make_shared<Stock>("GIN",STOCK_TYPE_PREFERRED,8,2,100);
    stockData["JOE"] = make_shared<Stock>("JOE",STOCK_TYPE_COMMON,13,0,250);

    for(pair<string, shared_ptr<Stock>> st : stockData)
    {
        generateTrades(st.second);
    };
}

double calcGeometricMean(map<string, shared_ptr<Stock>>& stockData)
{
    //map<string, shared_ptr<Stock>>::iterator it;
    double ProductOfAllIndexSharePrices = 1.0;
    for(pair<string, shared_ptr<Stock>> st : stockData)
    {
        shared_ptr<vector<Trade>> t = st.second->getTrades();
        ProductOfAllIndexSharePrices *= t->back().getPrice();
    };
    double power = 1.0/stockData.size();

    double GeometricMean = pow(ProductOfAllIndexSharePrices , power);

    return GeometricMean;
}
