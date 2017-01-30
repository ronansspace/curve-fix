#include "ExecutionReport/ExecutionReportHandler.h"

using namespace std;

map<string, string> ExecutionReportHandler::toMap(const FIX44::ExecutionReport& execReport) const {

    map<string, string> fields;

    fields.insert(pair<string, string>("Account", getAccount(execReport)));
    fields.insert(pair<string, string>("AvgPx", getAvgPx(execReport)));
    fields.insert(pair<string, string>("ClOrdID", getClOrdID(execReport)));
    fields.insert(pair<string, string>("CumQty", getCumQty(execReport)));
    fields.insert(pair<string, string>("Currency", getCurrency(execReport)));
    fields.insert(pair<string, string>("ExecID", getExecID(execReport)));
    fields.insert(pair<string, string>("LastPx", getLastPx(execReport)));
    fields.insert(pair<string, string>("LastQty", getLastQty(execReport)));
    fields.insert(pair<string, string>("OrderID", getOrderID(execReport)));
    fields.insert(pair<string, string>("OrderQty", getOrderQty(execReport)));
    fields.insert(pair<string, string>("OrdStatus", getOrdStatus(execReport)));
    fields.insert(pair<string, string>("OrdType", getOrdType(execReport)));
    fields.insert(pair<string, string>("Price", getPrice(execReport)));
    fields.insert(pair<string, string>("Side", getSide(execReport)));
    fields.insert(pair<string, string>("TimeInForce", getTimeInForce(execReport)));
    fields.insert(pair<string, string>("TransactTime", getTransactTime(execReport)));
    fields.insert(pair<string, string>("SettlDate", getSettlDate(execReport)));
    fields.insert(pair<string, string>("ListID", getListID(execReport)));
    fields.insert(pair<string, string>("TradeDate", getTradeDate(execReport)));
    fields.insert(pair<string, string>("ExecType", getExecType(execReport)));
    fields.insert(pair<string, string>("LeavesQty", getLeavesQty(execReport)));
    fields.insert(pair<string, string>("EffectiveTime", getEffectiveTime(execReport)));
    fields.insert(pair<string, string>("NoContraBrokers", getNoContraBrokers(execReport)));
    fields.insert(pair<string, string>("SecondaryExecID", getSecondaryExecID(execReport)));
    fields.insert(pair<string, string>("SourceSystem", "TraderTools"));

    return fields;

}

void ExecutionReportHandler::toFile(const FIX44::ExecutionReport& execReport, const string & fileName) const {

    map<string, string> fields = toMap(execReport);

    ofstream ofile;
    ofile.open(fileName.c_str());

    if(ofile) {
        for (map<string, string>::const_iterator it = fields.begin(); it != fields.end(); ++it) {
            ofile << it->first << "|" << it->second;
            ofile << "\n";
        }
    }

}

void ExecutionReportHandler::toDB(const FIX44::ExecutionReport& execReport) const {

    try {
        map<string, string> fields = toMap(execReport);

        sql::Driver *driver = get_driver_instance();

        unique_ptr<sql::Connection> con(driver->connect("tcp://localhost", "root", "bc43f15f516460e8966700a05761371e0235799a6d86ffd7"));
        con->setSchema("cmarkets");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXExecutionReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

        int dbCol = 1;
        for( auto it=fields.begin(); it!=fields.end(); ++it) {
            pstmt->setString(dbCol++, it->second);
        }

        pstmt->executeUpdate();

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

}

void ExecutionReportHandler::toConsole(const FIX44::ExecutionReport& execReport) const {
    cout << execReport.toString() << endl;
}

string ExecutionReportHandler::getAccount(const FIX44::ExecutionReport& execReport) const {
    FIX::Account account;
    return execReport.get(account);
}

string ExecutionReportHandler::getAvgPx(const FIX44::ExecutionReport& execReport) const {
    FIX::AvgPx avgPx;
    return execReport.get(avgPx).getString();
}

string ExecutionReportHandler::getClOrdID(const FIX44::ExecutionReport& execReport) const {
    FIX::ClOrdID clOrdID;
    return execReport.get(clOrdID);
}

string ExecutionReportHandler::getCumQty(const FIX44::ExecutionReport& execReport) const {
    FIX::CumQty cumQty;
    return execReport.get(cumQty).getString();
}

string ExecutionReportHandler::getCurrency(const FIX44::ExecutionReport& execReport) const {
    FIX::Currency currency;
    return execReport.get(currency);
}

string ExecutionReportHandler::getExecID(const FIX44::ExecutionReport& execReport) const {
    FIX::ExecID execID;
    return execReport.get(execID);
}

string ExecutionReportHandler::getLastPx(const FIX44::ExecutionReport& execReport) const {
    FIX::LastPx lastPx;
    return execReport.get(lastPx).getString();
}

string ExecutionReportHandler::getLastQty(const FIX44::ExecutionReport& execReport) const {
    FIX::LastQty lastQty;
    return execReport.get(lastQty).getString();
}

string ExecutionReportHandler::getOrderID(const FIX44::ExecutionReport& execReport) const {
    FIX::OrderID orderID;
    return execReport.get(orderID);
}

string ExecutionReportHandler::getOrderQty(const FIX44::ExecutionReport& execReport) const {
    FIX::OrderQty orderQty;
    return execReport.get(orderQty).getString();
}

string ExecutionReportHandler::getOrdStatus(const FIX44::ExecutionReport& execReport) const {
    FIX::OrdStatus ordStatus;
    return execReport.get(ordStatus).getString();
}

string ExecutionReportHandler::getOrdType(const FIX44::ExecutionReport& execReport) const {
    FIX::OrdType ordType;
    return execReport.get(ordType).getString();
}

string ExecutionReportHandler::getPrice(const FIX44::ExecutionReport& execReport) const {
    FIX::Price price;
    return execReport.get(price).getString();
}

string ExecutionReportHandler::getSide(const FIX44::ExecutionReport& execReport) const {
    FIX::Side side;
    return execReport.get(side).getString();
}

string ExecutionReportHandler::getTimeInForce(const FIX44::ExecutionReport& execReport) const {
    FIX::TimeInForce timeInForce;
    return execReport.get(timeInForce).getString();
}

string ExecutionReportHandler::getTransactTime(const FIX44::ExecutionReport& execReport) const {
    FIX::TransactTime transactTime;
    return execReport.get(transactTime).getString();
}

string ExecutionReportHandler::getSettlDate(const FIX44::ExecutionReport& execReport) const {
    FIX::SettlDate settlDate;
    return execReport.get(settlDate);
}

string ExecutionReportHandler::getListID(const FIX44::ExecutionReport& execReport) const {
    FIX::ListID listID;
    return execReport.get(listID);
}

string ExecutionReportHandler::getTradeDate(const FIX44::ExecutionReport& execReport) const {
    FIX::TradeDate tradeDate;
    return execReport.get(tradeDate);
}

string ExecutionReportHandler::getExecType(const FIX44::ExecutionReport& execReport) const {
    FIX::ExecType execType;
    return execReport.get(execType).getString();
}

string ExecutionReportHandler::getLeavesQty(const FIX44::ExecutionReport& execReport) const {
    FIX::LeavesQty leavesQty;
    return execReport.get(leavesQty).getString();
}

string ExecutionReportHandler::getEffectiveTime(const FIX44::ExecutionReport& execReport) const {
    FIX::EffectiveTime effectiveTime;
    return execReport.get(effectiveTime).getString();
}

string ExecutionReportHandler::getNoContraBrokers(const FIX44::ExecutionReport& execReport) const {
    FIX::NoContraBrokers noContraBrokers;
    return execReport.get(noContraBrokers).getString();
}

string ExecutionReportHandler::getSecondaryExecID(const FIX44::ExecutionReport& execReport) const {
    FIX::SecondaryExecID secondaryExecID;
    return execReport.get(secondaryExecID);
}



