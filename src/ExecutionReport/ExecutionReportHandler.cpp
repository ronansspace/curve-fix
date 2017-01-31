#include "ExecutionReport/ExecutionReportHandler.h"

using namespace std;

map<string, string> ExecutionReportHandler::toMap(const FIX44::ExecutionReport& execReport) const {

    map<string, string> fields;

    fields.insert(pair<string, string>("Account", getAccountStr(execReport)));
    fields.insert(pair<string, string>("AvgPx", getAvgPxStr(execReport)));
    fields.insert(pair<string, string>("ClOrdID", getClOrdIDStr(execReport)));
    fields.insert(pair<string, string>("CumQty", getCumQtyStr(execReport)));
    fields.insert(pair<string, string>("Currency", getCurrencyStr(execReport)));
    fields.insert(pair<string, string>("ExecID", getExecIDStr(execReport)));
    fields.insert(pair<string, string>("LastPx", getLastPxStr(execReport)));
    fields.insert(pair<string, string>("LastQty", getLastQtyStr(execReport)));
    fields.insert(pair<string, string>("OrderID", getOrderIDStr(execReport)));
    fields.insert(pair<string, string>("OrderQty", getOrderQtyStr(execReport)));
    fields.insert(pair<string, string>("OrdStatus", getOrdStatusStr(execReport)));
    fields.insert(pair<string, string>("OrdType", getOrdTypeStr(execReport)));
    fields.insert(pair<string, string>("Price", getPriceStr(execReport)));
    fields.insert(pair<string, string>("Side", getSideStr(execReport)));
    fields.insert(pair<string, string>("TimeInForce", getTimeInForceStr(execReport)));
    fields.insert(pair<string, string>("TransactTime", getTransactTimeStr(execReport)));
    fields.insert(pair<string, string>("SettlDate", getSettlDateStr(execReport)));
    fields.insert(pair<string, string>("ListID", getListIDStr(execReport)));
    fields.insert(pair<string, string>("TradeDate", getTradeDateStr(execReport)));
    fields.insert(pair<string, string>("ExecType", getExecTypeStr(execReport)));
    fields.insert(pair<string, string>("LeavesQty", getLeavesQtyStr(execReport)));
    fields.insert(pair<string, string>("EffectiveTime", getEffectiveTimeStr(execReport)));
    fields.insert(pair<string, string>("NoContraBrokers", getNoContraBrokersStr(execReport)));
    fields.insert(pair<string, string>("SecondaryExecID", getSecondaryExecIDStr(execReport)));
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

        pstmt->setString(1, getAccountStr(execReport));
        pstmt->setDouble(2, getAvgPx(execReport));
        pstmt->setString(3, getClOrdIDStr(execReport));
        pstmt->setDouble(4, getCumQty(execReport));
        pstmt->setString(5, getCurrencyStr(execReport));
        pstmt->setString(6, getExecIDStr(execReport));
        pstmt->setDouble(7, getLastPx(execReport));
        pstmt->setDouble(8, getLastQty(execReport));
        pstmt->setString(9, getOrderIDStr(execReport));
        pstmt->setDouble(10, getOrderQty(execReport));
        pstmt->setString(11, getOrdStatusStr(execReport));
        pstmt->setString(12, getOrdTypeStr(execReport));
        pstmt->setDouble(13, getPrice(execReport));
        pstmt->setString(14, getSideStr(execReport));
        pstmt->setString(15, getTimeInForceStr(execReport));
        pstmt->setString(16, getTransactTimeStr(execReport));
        pstmt->setString(17, getSettlDateStr(execReport));
        pstmt->setString(18, getListIDStr(execReport));
        pstmt->setString(19, getTradeDateStr(execReport));
        pstmt->setString(20, getExecTypeStr(execReport));
        pstmt->setDouble(21, getLeavesQty(execReport));
        pstmt->setString(22, getEffectiveTimeStr(execReport));
        pstmt->setString(23, getNoContraBrokersStr(execReport));
        pstmt->setString(24, getSecondaryExecIDStr(execReport));
        pstmt->setString(25, "TraderTools");

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

string ExecutionReportHandler::getAccountStr(const FIX44::ExecutionReport& execReport) const {
    FIX::Account account;
    return execReport.get(account);
}

string ExecutionReportHandler::getAvgPxStr(const FIX44::ExecutionReport& execReport) const {
    FIX::AvgPx avgPx;
    return execReport.get(avgPx).getString();
}

string ExecutionReportHandler::getClOrdIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::ClOrdID clOrdID;
    return execReport.get(clOrdID);
}

string ExecutionReportHandler::getCumQtyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::CumQty cumQty;
    return execReport.get(cumQty).getString();
}

string ExecutionReportHandler::getCurrencyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::Currency currency;
    return execReport.get(currency);
}

string ExecutionReportHandler::getExecIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::ExecID execID;
    return execReport.get(execID);
}

string ExecutionReportHandler::getLastPxStr(const FIX44::ExecutionReport& execReport) const {
    FIX::LastPx lastPx;
    return execReport.get(lastPx).getString();
}

string ExecutionReportHandler::getLastQtyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::LastQty lastQty;
    return execReport.get(lastQty).getString();
}

string ExecutionReportHandler::getOrderIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::OrderID orderID;
    return execReport.get(orderID);
}

string ExecutionReportHandler::getOrderQtyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::OrderQty orderQty;
    return execReport.get(orderQty).getString();
}

string ExecutionReportHandler::getOrdStatusStr(const FIX44::ExecutionReport& execReport) const {
    FIX::OrdStatus ordStatus;

    string ret = "Error";

    switch (execReport.get(ordStatus).getValue()) {
        case '0': ret = "New"; break;
        case '1': ret = "Partially filled"; break;
        case '2': ret = "Filled"; break;
        case '3': ret = "Done for day"; break;
        case '4': ret = "Canceled"; break;
        case '5': ret = "Replaced"; break;
        case '6': ret = "Pending Cancel"; break;
        case '7': ret = "Stopped"; break;
        case '8': ret = "Rejected"; break;
        case '9': ret = "Suspended"; break;
        case 'A': ret = "Pending New"; break;
        case 'B': ret = "Calculated"; break;
        case 'C': ret = "Expired"; break;
        case 'D': ret = "Accepted for bidding"; break;
        case 'E': ret = "Pending Replace"; break;
        default: ret = "Error";
    }

    return ret;

}

string ExecutionReportHandler::getOrdTypeStr(const FIX44::ExecutionReport& execReport) const {
    FIX::OrdType ordType;

    string ret = "Error";

    switch (execReport.get(ordType).getValue()) {
        case '1': ret = "Market"; break;
        case '2': ret = "Limit"; break;
        case '3': ret = "Stop"; break;
        case '4': ret = "Stop limit"; break;
        case '5': ret = "Market on close"; break;
        case '6': ret = "With or without"; break;
        case '7': ret = "Limit or better"; break;
        case '8': ret = "Limit with or without"; break;
        case '9': ret = "On basis"; break;
        case 'A': ret = "On close"; break;
        case 'B': ret = "Limit on close"; break;
        case 'C': ret = "Forex - Market"; break;
        case 'D': ret = "Previously quoted"; break;
        case 'E': ret = "Previously indicated"; break;
        case 'F': ret = "Forex - Limit"; break;
        case 'G': ret = "Forex - Swap"; break;
        case 'H': ret = "Forex - Previously Quoted"; break;
        case 'I': ret = "Funari"; break;
        case 'J': ret = "Market If Touched"; break;
        case 'K': ret = "Market with Leftover as Limit"; break;
        case 'L': ret = "Previous Fund Valuation Point"; break;
        case 'M': ret = "Next Fund Valuation Point"; break;
        case 'P': ret = "Pegged"; break;
        default: ret = "Error";
    }

    return ret;

}

string ExecutionReportHandler::getPriceStr(const FIX44::ExecutionReport& execReport) const {
    FIX::Price price;
    return execReport.get(price).getString();
}

string ExecutionReportHandler::getSideStr(const FIX44::ExecutionReport& execReport) const {
    FIX::Side side;

    string ret = "Error";

    switch (execReport.get(side).getValue()) {
        case '1': ret = "Buy"; break;
        case '2': ret = "Sell"; break;
        case '3': ret = "Buy minus"; break;
        case '4': ret = "Sell plus"; break;
        case '5': ret = "Sell short"; break;
        case '6': ret = "Sell short exempt"; break;
        case '7': ret = "Undisclosed"; break;
        case '8': ret = "Cross"; break;
        case '9': ret = "Cross short"; break;
        case 'A': ret = "Cross short exempt"; break;
        case 'B': ret = "As Defined"; break;
        case 'C': ret = "Opposite"; break;
        case 'D': ret = "Subscribe"; break;
        case 'E': ret = "Redeem"; break;
        case 'F': ret = "Lend"; break;
        case 'G': ret = "Borrow"; break;
    }

    return ret;

}

string ExecutionReportHandler::getTimeInForceStr(const FIX44::ExecutionReport& execReport) const {
    FIX::TimeInForce timeInForce;
    return execReport.get(timeInForce).getString();
}

string ExecutionReportHandler::getTransactTimeStr(const FIX44::ExecutionReport& execReport) const {
    FIX::TransactTime transactTime;
    return execReport.get(transactTime).getString();
}

string ExecutionReportHandler::getSettlDateStr(const FIX44::ExecutionReport& execReport) const {
    FIX::SettlDate settlDate;
    return execReport.get(settlDate);
}

string ExecutionReportHandler::getListIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::ListID listID;
    return execReport.get(listID);
}

string ExecutionReportHandler::getTradeDateStr(const FIX44::ExecutionReport& execReport) const {
    FIX::TradeDate tradeDate;
    return execReport.get(tradeDate);
}

string ExecutionReportHandler::getExecTypeStr(const FIX44::ExecutionReport& execReport) const {
    FIX::ExecType execType;

    string execTypeStr = "Error";

    switch (execReport.get(execType).getValue()) {
        case '0': execTypeStr = "New"; break;
        case '1': execTypeStr = "Partial fill"; break;
        case '2': execTypeStr = "Fill"; break;
        case '3': execTypeStr = "Done for day"; break;
        case '4': execTypeStr = "Canceled"; break;
        case '5': execTypeStr = "Replace"; break;
        case '6': execTypeStr = "Pending Cancel"; break;
        case '7': execTypeStr = "Stopped"; break;
        case '8': execTypeStr = "Rejected"; break;
        case '9': execTypeStr = "Suspended"; break;
        case 'A': execTypeStr = "Pending New"; break;
        case 'B': execTypeStr = "Calculated"; break;
        case 'C': execTypeStr = "Expired"; break;
        case 'D': execTypeStr = "Restated"; break;
        case 'E': execTypeStr = "Pending Replace"; break;
        case 'F': execTypeStr = "Trade"; break;
        case 'G': execTypeStr = "Trade Correct"; break;
        case 'H': execTypeStr = "Trade Cancel"; break;
        case 'I': execTypeStr = "Order Status"; break;
        default: execTypeStr = "Error";
    }

    return execTypeStr;

}

string ExecutionReportHandler::getLeavesQtyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::LeavesQty leavesQty;
    return execReport.get(leavesQty).getString();
}

string ExecutionReportHandler::getEffectiveTimeStr(const FIX44::ExecutionReport& execReport) const {
    FIX::EffectiveTime effectiveTime;
    return execReport.get(effectiveTime).getString();
}

string ExecutionReportHandler::getNoContraBrokersStr(const FIX44::ExecutionReport& execReport) const {
    FIX::NoContraBrokers noContraBrokers;
    return execReport.get(noContraBrokers).getString();
}

string ExecutionReportHandler::getSecondaryExecIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::SecondaryExecID secondaryExecID;
    return execReport.get(secondaryExecID);
}

double ExecutionReportHandler::getAvgPx(const FIX44::ExecutionReport& execReport) const {
    FIX::AvgPx avgPx;
    return execReport.get(avgPx).getValue();
}

double ExecutionReportHandler::getCumQty(const FIX44::ExecutionReport& execReport) const {
    FIX::CumQty cumQty;
    return execReport.get(cumQty).getValue();
}

double ExecutionReportHandler::getLastPx(const FIX44::ExecutionReport& execReport) const {
    FIX::LastPx lastPx;
    return execReport.get(lastPx).getValue();
}

double ExecutionReportHandler::getLastQty(const FIX44::ExecutionReport& execReport) const {
    FIX::LastQty lastQty;
    return execReport.get(lastQty).getValue();
}

double ExecutionReportHandler::getPrice(const FIX44::ExecutionReport& execReport) const {
    FIX::Price price;
    return execReport.get(price).getValue();
}

double ExecutionReportHandler::getLeavesQty(const FIX44::ExecutionReport& execReport) const {
    FIX::LeavesQty leavesQty;
    return execReport.get(leavesQty).getValue();
}

double ExecutionReportHandler::getOrderQty(const FIX44::ExecutionReport& execReport) const {
    FIX::OrderQty orderQty;
    return execReport.get(orderQty).getValue();
}



