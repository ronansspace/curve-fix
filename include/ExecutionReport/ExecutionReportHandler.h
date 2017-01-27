#include <string>
#include <map>
#include <fstream>

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"
#include "quickfix/fix44/ExecutionReport.h"

class ExecutionReportHandler
{
public:

    ExecutionReportHandler(){};

    void toFile(const FIX44::ExecutionReport& execReport, const std::string & fileName) const;
    void toDB(const FIX44::ExecutionReport& execReport) const;
    void toConsole(const FIX44::ExecutionReport& execReport) const;

    std::string getAccount(const FIX44::ExecutionReport& execReport) const;
    std::string getAvgPx(const FIX44::ExecutionReport& execReport) const;
    std::string getClOrdID(const FIX44::ExecutionReport& execReport) const;
    std::string getCumQty(const FIX44::ExecutionReport& execReport) const;
    std::string getCurrency(const FIX44::ExecutionReport& execReport) const;
    std::string getExecID(const FIX44::ExecutionReport& execReport) const;
    std::string getLastPx(const FIX44::ExecutionReport& execReport) const;
    std::string getLastQty(const FIX44::ExecutionReport& execReport) const;
    std::string getOrderID(const FIX44::ExecutionReport& execReport) const;
    std::string getOrderQty(const FIX44::ExecutionReport& execReport) const;
    std::string getOrdStatus(const FIX44::ExecutionReport& execReport) const;
    std::string getOrdType(const FIX44::ExecutionReport& execReport) const;
    std::string getPrice(const FIX44::ExecutionReport& execReport) const;
    std::string getSide(const FIX44::ExecutionReport& execReport) const;
    std::string getTimeInForce(const FIX44::ExecutionReport& execReport) const;
    std::string getTransactTime(const FIX44::ExecutionReport& execReport) const;
    std::string getSettlDate(const FIX44::ExecutionReport& execReport) const;
    std::string getListID(const FIX44::ExecutionReport& execReport) const;
    std::string getTradeDate(const FIX44::ExecutionReport& execReport) const;
    std::string getExecType(const FIX44::ExecutionReport& execReport) const;
    std::string getLeavesQty(const FIX44::ExecutionReport& execReport) const;
    std::string getEffectiveTime(const FIX44::ExecutionReport& execReport) const;
    std::string getNoContraBrokers(const FIX44::ExecutionReport& execReport) const;
    std::string getSecondaryExecID(const FIX44::ExecutionReport& execReport) const;

};

