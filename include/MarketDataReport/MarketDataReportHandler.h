#include <string>
#include <map>
#include <fstream>

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"
#include "quickfix/fix44/MarketDataSnapshotFullRefresh.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class MarketDataReportHandler
{
public:

    MarketDataReportHandler(){};

    void toFile(const FIX44::MarketDataSnapshotFullRefresh& mktReport, const std::string & fileName) const;
    void toDB(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const;
    void toConsole(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const;
    std::map<std::string, std::string> toMap(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const;

    std::string getSendingTimeStr(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const;
    std::string getCcyPairStr(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const;
    std::string getRateStr(const FIX44::MarketDataSnapshotFullRefresh& execReport) const;
    std::string getTradingDateStr(const FIX44::MarketDataSnapshotFullRefresh& execReport) const;
    double getRate(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const;

};

