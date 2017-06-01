
#include <gtest/gtest.h>
#include <stock.h>
#include <StockMarketException.h>

using namespace std;


TEST(StockDividendTest, ZeroDividendCalcCommonStock)
{
    Stock s("TEA", STOCK_TYPE_COMMON, 0, 0, 100);

    double price = 23.56;
    double dDividend = s.calcDividend(price);
    EXPECT_DOUBLE_EQ(0.0, dDividend);
}

TEST(StockDividendTest, DividendCalcCommonStock)
{
    Stock s("TEA", STOCK_TYPE_COMMON, 46.0, 0, 100);


    double dDividend = s.calcDividend(23.0);
    EXPECT_DOUBLE_EQ(2.0, dDividend);
}


TEST(StockDividendTest, ZeroPriceDividendCalc)
{
    Stock s("TEA", STOCK_TYPE_COMMON, 46.0, 65, 100);

    EXPECT_THROW(s.calcDividend(0.0), StockMarketException);
}

TEST(StockDividendTest, DividendCalcPreferredStock)
{
    Stock s("GIN", STOCK_TYPE_PREFERRED, 8.0, 2, 100);

    double dDividend = s.calcDividend(8.0);
    EXPECT_DOUBLE_EQ(25.0, dDividend);

}


TEST(StockDividendTest, PERatioCalc)
{
    Stock s("GIN", STOCK_TYPE_PREFERRED, 8.0, 2, 100);

    double dRatio = s.calcPERatio(8.0);
    EXPECT_DOUBLE_EQ(8.0/25.0, dRatio);
}


TEST(StockDividendTest, PERatioCalcZeroDivision)
{
    Stock s("TEA", STOCK_TYPE_COMMON, 0, 0, 100);
    EXPECT_THROW(s.calcPERatio(8.0), StockMarketException);
}

