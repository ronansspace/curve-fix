#include <string>
#include <map>
#include <fstream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class TraderToolsOrder
{
private:
    std::string account;
    std::string symbol;
    std::string clOrdID;
    std::string currency;
    std::string execID;
    std::string orderID;
    std::string ordStatus;
    std::string ordType;
    std::string side;
    std::string timeInForce;
    std::string transactTime;
    std::string settlDate;
    std::string listID;
    std::string tradeDate;
    std::string execType;
    std::string effectiveTime;
    std::string noContraBrokers;
    std::string secondaryExecID;
    std::string partyID;
    std::string contraBroker;
    std::string avgPxStr;

    double avgPx;
    double cumQty;
    double lastPx;
    double lastQty;
    double orderQty;
    double price;
    double leavesQty;

    std::unique_ptr<sql::PreparedStatement> buildFIXOrder(std::unique_ptr<sql::PreparedStatement> pstmt) const;
    std::unique_ptr<sql::PreparedStatement> buildFIXOrderReverse(std::unique_ptr<sql::PreparedStatement> pstmt) const;
    std::unique_ptr<sql::PreparedStatement> buildFIXContract(std::unique_ptr<sql::PreparedStatement> pstmtOrd) const;
    std::unique_ptr<sql::PreparedStatement> buildFIXContractReverse(std::unique_ptr<sql::PreparedStatement> pstmtOrd) const;

public:

    TraderToolsOrder(){};

    void processOrder() const;

    void setAccount(const std::string& i) {account = i;}
    void setSymbol(const std::string& i) {symbol = i;}
    void setClOrdID(const std::string& i) {clOrdID = i;}
    void setCurrency(const std::string& i) {currency= i;}
    void setExecID(const std::string& i) {execID= i;}
    void setOrderID(const std::string& i) {orderID= i;}
    void setOrdStatus(const std::string& i) {ordStatus= i;}
    void setOrdType(const std::string& i) {ordType= i;}
    void setSide(const std::string& i) {side= i;}
    void setTimeInForce(const std::string& i) {timeInForce= i;}
    void setTransactTime(const std::string& i) {transactTime= i;}
    void setSettlDate(const std::string& i) {settlDate= i;}
    void setListID(const std::string& i) {listID= i;}
    void setTradeDate(const std::string& i) {tradeDate= i;}
    void setExecType(const std::string& i) {execType= i;}
    void setEffectiveTime(const std::string& i) {effectiveTime= i;}
    void setNoContraBrokers(const std::string& i) {noContraBrokers= i;}
    void setSecondaryExecID(const std::string& i) {secondaryExecID= i;}
    void setPartyID(const std::string& i) {partyID= i;}
    void setContraBroker(const std::string& i) {contraBroker= i;}
    void setAvgPxStr(const std::string& i) {avgPxStr= i;}

    void setAvgPx(double i) {avgPx= i;}
    void setCumQty(double i) {cumQty= i;}
    void setLastPx(double i) {lastPx= i;}
    void setLastQty(double i) {lastQty= i;}
    void setOrderQty(double i) {orderQty= i;}
    void setPrice(double i) {price= i;}
    void setLeavesQty(double i) {leavesQty= i;}

};

