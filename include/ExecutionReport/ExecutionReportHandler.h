#include <string>
#include <map>
#include <fstream>

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"
#include "quickfix/fix44/ExecutionReport.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class ExecutionReportHandler
{
public:

    ExecutionReportHandler(){};

    void toFile(const FIX44::ExecutionReport& execReport, const std::string & fileName) const;
    void toDB(const FIX44::ExecutionReport& execReport) const;
    void toConsole(const FIX44::ExecutionReport& execReport) const;
    std::map<std::string, std::string> toMap(const FIX44::ExecutionReport& execReport) const;

    std::string getAccountStr(const FIX44::ExecutionReport& execReport) const;
    std::string getAvgPxStr(const FIX44::ExecutionReport& execReport) const;
    std::string getClOrdIDStr(const FIX44::ExecutionReport& execReport) const;
    std::string getCumQtyStr(const FIX44::ExecutionReport& execReport) const;
    std::string getCurrencyStr(const FIX44::ExecutionReport& execReport) const;
    std::string getExecIDStr(const FIX44::ExecutionReport& execReport) const;
    std::string getLastPxStr(const FIX44::ExecutionReport& execReport) const;
    std::string getLastQtyStr(const FIX44::ExecutionReport& execReport) const;
    std::string getOrderIDStr(const FIX44::ExecutionReport& execReport) const;
    std::string getOrderQtyStr(const FIX44::ExecutionReport& execReport) const;
    std::string getOrdStatusStr(const FIX44::ExecutionReport& execReport) const;
    std::string getOrdTypeStr(const FIX44::ExecutionReport& execReport) const;
    std::string getPriceStr(const FIX44::ExecutionReport& execReport) const;
    std::string getSideStr(const FIX44::ExecutionReport& execReport) const;
    std::string getTimeInForceStr(const FIX44::ExecutionReport& execReport) const;
    std::string getTransactTimeStr(const FIX44::ExecutionReport& execReport) const;
    std::string getSettlDateStr(const FIX44::ExecutionReport& execReport) const;
    std::string getListIDStr(const FIX44::ExecutionReport& execReport) const;
    std::string getTradeDateStr(const FIX44::ExecutionReport& execReport) const;
    std::string getExecTypeStr(const FIX44::ExecutionReport& execReport) const;
    std::string getLeavesQtyStr(const FIX44::ExecutionReport& execReport) const;
    std::string getEffectiveTimeStr(const FIX44::ExecutionReport& execReport) const;
    std::string getNoContraBrokersStr(const FIX44::ExecutionReport& execReport) const;
    std::string getSecondaryExecIDStr(const FIX44::ExecutionReport& execReport) const;

    double getAvgPx(const FIX44::ExecutionReport& execReport) const;
    double getCumQty(const FIX44::ExecutionReport& execReport) const;
    double getLastPx(const FIX44::ExecutionReport& execReport) const;
    double getLastQty(const FIX44::ExecutionReport& execReport) const;
    double getLeavesQty(const FIX44::ExecutionReport& execReport) const;
    double getOrderQty(const FIX44::ExecutionReport& execReport) const;
    double getPrice(const FIX44::ExecutionReport& execReport) const;

};

