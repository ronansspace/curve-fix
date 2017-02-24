#include "ExecutionReport/ExecutionReportHandler.h"

using namespace std;

map<string, string> ExecutionReportHandler::toMap(const FIX44::ExecutionReport& execReport) const {

    map<string, string> fields;

    fields.insert(pair<string, string>("Account", getAccountStr(execReport)));
    fields.insert(pair<string, string>("Symbol", getSymbolStr(execReport)));
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
    fields.insert(pair<string, string>("PartyID", getPartyIDStr(execReport)));
    fields.insert(pair<string, string>("ContraBroker", getContraBrokerStr(execReport)));
    fields.insert(pair<string, string>("SourceSystem", this->sourceSystem));

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
        sql::Driver *driver = get_driver_instance();

        ifstream infile("/root/.mysql_password");
        string sLine;
        if (infile.good())
        {

            getline(infile, sLine);
        }

        infile.close();

        unique_ptr<sql::Connection> con(driver->connect("tcp://localhost", "root", sLine));
        con->setSchema("cmarkets");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXExecutionReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

        pstmt->setString(1, getAccountStr(execReport));
        pstmt->setString(2, getSymbolStr(execReport));
        pstmt->setDouble(3, getAvgPx(execReport));
        pstmt->setString(4, getClOrdIDStr(execReport));
        pstmt->setDouble(5, getCumQty(execReport));
        pstmt->setString(6, getCurrencyStr(execReport));
        pstmt->setString(7, getExecIDStr(execReport));
        pstmt->setDouble(8, getLastPx(execReport));
        pstmt->setDouble(9, getLastQty(execReport));
        pstmt->setString(10, getOrderIDStr(execReport));
        pstmt->setDouble(11, getOrderQty(execReport));
        pstmt->setString(12, getOrdStatusStr(execReport));
        pstmt->setString(13, getOrdTypeStr(execReport));
        pstmt->setDouble(14, getPrice(execReport));
        pstmt->setString(15, getSideStr(execReport));
        pstmt->setString(16, getTimeInForceStr(execReport));
        pstmt->setString(17, getTransactTimeStr(execReport));
        pstmt->setString(18, getSettlDateStr(execReport));
        pstmt->setString(19, getListIDStr(execReport));
        pstmt->setString(20, getTradeDateStr(execReport));
        pstmt->setString(21, getExecTypeStr(execReport));
        pstmt->setDouble(22, getLeavesQty(execReport));
        pstmt->setString(23, getEffectiveTimeStr(execReport));
        pstmt->setString(24, getNoContraBrokersStr(execReport));
        pstmt->setString(25, getSecondaryExecIDStr(execReport));
        pstmt->setString(26, getPartyIDStr(execReport));
        pstmt->setString(27, getContraBrokerStr(execReport));
        pstmt->setString(28, this->sourceSystem);

        pstmt->executeUpdate();


        unique_ptr<sql::PreparedStatement> pstmt1(con->prepareStatement("SELECT * from FIXOrderReport WHERE OrderID=?"));
        pstmt1->setString(1, getOrderIDStr(execReport));
        unique_ptr<sql::ResultSet> res(pstmt1->executeQuery());

       if(res->rowsCount() == 0) {
           unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXOrderReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

           pstmt->setString(1, getAccountStr(execReport));
           pstmt->setString(2, getSymbolStr(execReport));
           pstmt->setDouble(3, getAvgPx(execReport));
           pstmt->setString(4, getClOrdIDStr(execReport));
           pstmt->setDouble(5, getCumQty(execReport));
           pstmt->setString(6, getCurrencyStr(execReport));
           pstmt->setString(7, getExecIDStr(execReport));
           pstmt->setDouble(8, getLastPx(execReport));
           pstmt->setDouble(9, getLastQty(execReport));
           pstmt->setString(10, getOrderIDStr(execReport));
           pstmt->setDouble(11, getOrderQty(execReport));
           pstmt->setString(12, getOrdStatusStr(execReport));
           pstmt->setString(13, getOrdTypeStr(execReport));
           pstmt->setDouble(14, getPrice(execReport));
           pstmt->setString(15, getSideStr(execReport));
           pstmt->setString(16, getTimeInForceStr(execReport));
           pstmt->setString(17, getTransactTimeStr(execReport));
           pstmt->setString(18, getSettlDateStr(execReport));
           pstmt->setString(19, getListIDStr(execReport));
           pstmt->setString(20, getTradeDateStr(execReport));
           pstmt->setString(21, getExecTypeStr(execReport));
           pstmt->setDouble(22, getLeavesQty(execReport));
           pstmt->setString(23, getEffectiveTimeStr(execReport));
           pstmt->setString(24, getNoContraBrokersStr(execReport));
           pstmt->setString(25, getSecondaryExecIDStr(execReport));
           pstmt->setString(26, getPartyIDStr(execReport));
           pstmt->setString(27, getContraBrokerStr(execReport));
           pstmt->setString(28, this->sourceSystem);
           pstmt->setBoolean(29, 0);

           pstmt->executeUpdate();
       } else {
           unique_ptr<sql::PreparedStatement> pstmt1(con->prepareStatement("SELECT * from FIXOrderReport WHERE OrderID=? AND Account=?"));
           pstmt1->setString(1, getOrderIDStr(execReport));
           pstmt1->setString(2, getAccountStr(execReport));
           unique_ptr<sql::ResultSet> res(pstmt1->executeQuery());

           if(res->rowsCount() == 0) {
               unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXOrderReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

               pstmt->setString(1, getAccountStr(execReport));
               pstmt->setString(2, getSymbolStr(execReport));
               pstmt->setDouble(3, getAvgPx(execReport));
               pstmt->setString(4, getClOrdIDStr(execReport));
               pstmt->setDouble(5, getCumQty(execReport));
               pstmt->setString(6, getCurrencyStr(execReport));
               pstmt->setString(7, getExecIDStr(execReport));
               pstmt->setDouble(8, getLastPx(execReport));
               pstmt->setDouble(9, getLastQty(execReport));
               pstmt->setString(10, getOrderIDStr(execReport));
               pstmt->setDouble(11, getOrderQty(execReport));
               pstmt->setString(12, getOrdStatusStr(execReport));
               pstmt->setString(13, getOrdTypeStr(execReport));
               pstmt->setDouble(14, getPrice(execReport));
               pstmt->setString(15, getSideStr(execReport) == "Buy" ? "Sell" : "Buy");
               pstmt->setString(16, getTimeInForceStr(execReport));
               pstmt->setString(17, getTransactTimeStr(execReport));
               pstmt->setString(18, getSettlDateStr(execReport));
               pstmt->setString(19, getListIDStr(execReport));
               pstmt->setString(20, getTradeDateStr(execReport));
               pstmt->setString(21, getExecTypeStr(execReport));
               pstmt->setDouble(22, getLeavesQty(execReport));
               pstmt->setString(23, getEffectiveTimeStr(execReport));
               pstmt->setString(24, getNoContraBrokersStr(execReport));
               pstmt->setString(25, getSecondaryExecIDStr(execReport));
               pstmt->setString(26, getPartyIDStr(execReport));
               pstmt->setString(27, getContraBrokerStr(execReport));
               pstmt->setString(28, this->sourceSystem);
               pstmt->setBoolean(29, 1);

               pstmt->executeUpdate();
           } else {
               unique_ptr<sql::PreparedStatement> pstmt1(con->prepareStatement("SELECT * from FIXOrderReport WHERE OrderID=? AND Account=? AND ClientOrder=true"));
               pstmt1->setString(1, getOrderIDStr(execReport));
               pstmt1->setString(2, getAccountStr(execReport));
               unique_ptr<sql::ResultSet> res(pstmt1->executeQuery());

               if(res->rowsCount() == 0) {
                   unique_ptr<sql::Statement> stmt(con->createStatement());
                   stmt->execute("DELETE FROM FIXOrderReport WHERE OrderID='" +getOrderIDStr(execReport) + "' AND Account='" + getAccountStr(execReport) + "'");

                   unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXOrderReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

                   pstmt->setString(1, getAccountStr(execReport));
                   pstmt->setString(2, getSymbolStr(execReport));
                   pstmt->setDouble(3, getAvgPx(execReport));
                   pstmt->setString(4, getClOrdIDStr(execReport));
                   pstmt->setDouble(5, getCumQty(execReport));
                   pstmt->setString(6, getCurrencyStr(execReport));
                   pstmt->setString(7, getExecIDStr(execReport));
                   pstmt->setDouble(8, getLastPx(execReport));
                   pstmt->setDouble(9, getLastQty(execReport));
                   pstmt->setString(10, getOrderIDStr(execReport));
                   pstmt->setDouble(11, getOrderQty(execReport));
                   pstmt->setString(12, getOrdStatusStr(execReport));
                   pstmt->setString(13, getOrdTypeStr(execReport));
                   pstmt->setDouble(14, getPrice(execReport));
                   pstmt->setString(15, getSideStr(execReport));
                   pstmt->setString(16, getTimeInForceStr(execReport));
                   pstmt->setString(17, getTransactTimeStr(execReport));
                   pstmt->setString(18, getSettlDateStr(execReport));
                   pstmt->setString(19, getListIDStr(execReport));
                   pstmt->setString(20, getTradeDateStr(execReport));
                   pstmt->setString(21, getExecTypeStr(execReport));
                   pstmt->setDouble(22, getLeavesQty(execReport));
                   pstmt->setString(23, getEffectiveTimeStr(execReport));
                   pstmt->setString(24, getNoContraBrokersStr(execReport));
                   pstmt->setString(25, getSecondaryExecIDStr(execReport));
                   pstmt->setString(26, getPartyIDStr(execReport));
                   pstmt->setString(27, getContraBrokerStr(execReport));
                   pstmt->setString(28, this->sourceSystem);
                   pstmt->setBoolean(29, 0);

                   pstmt->executeUpdate();

               } else {
                   unique_ptr<sql::Statement> stmt(con->createStatement());
                   stmt->execute("DELETE FROM FIXOrderReport WHERE OrderID='" +getOrderIDStr(execReport) + "' AND Account='" + getAccountStr(execReport) + "'");

                   unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXOrderReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));

                   pstmt->setString(1, getAccountStr(execReport));
                   pstmt->setString(2, getSymbolStr(execReport));
                   pstmt->setDouble(3, getAvgPx(execReport));
                   pstmt->setString(4, getClOrdIDStr(execReport));
                   pstmt->setDouble(5, getCumQty(execReport));
                   pstmt->setString(6, getCurrencyStr(execReport));
                   pstmt->setString(7, getExecIDStr(execReport));
                   pstmt->setDouble(8, getLastPx(execReport));
                   pstmt->setDouble(9, getLastQty(execReport));
                   pstmt->setString(10, getOrderIDStr(execReport));
                   pstmt->setDouble(11, getOrderQty(execReport));
                   pstmt->setString(12, getOrdStatusStr(execReport));
                   pstmt->setString(13, getOrdTypeStr(execReport));
                   pstmt->setDouble(14, getPrice(execReport));
                   pstmt->setString(15, getSideStr(execReport) == "Buy" ? "Sell" : "Buy");
                   pstmt->setString(16, getTimeInForceStr(execReport));
                   pstmt->setString(17, getTransactTimeStr(execReport));
                   pstmt->setString(18, getSettlDateStr(execReport));
                   pstmt->setString(19, getListIDStr(execReport));
                   pstmt->setString(20, getTradeDateStr(execReport));
                   pstmt->setString(21, getExecTypeStr(execReport));
                   pstmt->setDouble(22, getLeavesQty(execReport));
                   pstmt->setString(23, getEffectiveTimeStr(execReport));
                   pstmt->setString(24, getNoContraBrokersStr(execReport));
                   pstmt->setString(25, getSecondaryExecIDStr(execReport));
                   pstmt->setString(26, getPartyIDStr(execReport));
                   pstmt->setString(27, getContraBrokerStr(execReport));
                   pstmt->setString(28, this->sourceSystem);
                   pstmt->setBoolean(29, 1);

                   pstmt->executeUpdate();
               }
           }
       }
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
    return execReport.getIfSet(account) ? execReport.get(account).getString() : "";
}

string ExecutionReportHandler::getSymbolStr(const FIX44::ExecutionReport& execReport) const {
    FIX::Symbol symbol;
    return execReport.getIfSet(symbol) ? execReport.get(symbol).getString() : "";
}

string ExecutionReportHandler::getAvgPxStr(const FIX44::ExecutionReport& execReport) const {
    FIX::AvgPx avgPx;
    return execReport.getIfSet(avgPx) ? execReport.get(avgPx).getString() : "";
}

string ExecutionReportHandler::getClOrdIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::ClOrdID clOrdID;
    return execReport.getIfSet(clOrdID) ? execReport.get(clOrdID).getString() : "";
}

string ExecutionReportHandler::getCumQtyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::CumQty cumQty;
    return execReport.getIfSet(cumQty) ? execReport.get(cumQty).getString() : "";
}

string ExecutionReportHandler::getCurrencyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::Currency currency;
    return execReport.getIfSet(currency) ? execReport.get(currency).getString() : "";
}

string ExecutionReportHandler::getExecIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::ExecID execID;
    return execReport.getIfSet(execID) ? execReport.get(execID).getString() : "";
}

string ExecutionReportHandler::getLastPxStr(const FIX44::ExecutionReport& execReport) const {
    FIX::LastPx lastPx;
    return execReport.getIfSet(lastPx) ? execReport.get(lastPx).getString() : "";
}

string ExecutionReportHandler::getLastQtyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::LastQty lastQty;
    return execReport.getIfSet(lastQty) ? execReport.get(lastQty).getString() : "";
}

string ExecutionReportHandler::getOrderIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::OrderID orderID;
    return execReport.getIfSet(orderID) ? execReport.get(orderID).getString() : "";
}

string ExecutionReportHandler::getOrderQtyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::OrderQty orderQty;
    return execReport.getIfSet(orderQty) ? execReport.get(orderQty).getString() : "";
}

string ExecutionReportHandler::getOrdStatusStr(const FIX44::ExecutionReport& execReport) const {
    FIX::OrdStatus ordStatus;

    string ret;

    if(!execReport.getIfSet(ordStatus)) {
        return "";
    }

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
        default: ret = "NoOrdStatus";
    }

    return ret;

}

string ExecutionReportHandler::getOrdTypeStr(const FIX44::ExecutionReport& execReport) const {
    FIX::OrdType ordType;

    string ret;

    if(!execReport.getIfSet(ordType)) {
        return "";
    }

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
        default: ret = "NoOrdType";
    }

    return ret;

}

string ExecutionReportHandler::getPriceStr(const FIX44::ExecutionReport& execReport) const {
    FIX::Price price;
    return execReport.getIfSet(price) ? execReport.get(price).getString() : "";
}

string ExecutionReportHandler::getSideStr(const FIX44::ExecutionReport& execReport) const {
    FIX::Side side;

    string ret;

    if(!execReport.getIfSet(side)) {
        return "";
    }

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
        default: ret = "NoSide";
    }

    return ret;

}

string ExecutionReportHandler::getTimeInForceStr(const FIX44::ExecutionReport& execReport) const {
    FIX::TimeInForce timeInForce;

    if(!execReport.getIfSet(timeInForce)) {
        return "Day";
    }

    string retStr;

    switch (execReport.get(timeInForce).getValue()) {
        case '0': retStr = "Day"; break;
        case '1': retStr = "Good Till Cancel"; break;
        case '2': retStr = "At the Opening"; break;
        case '3': retStr = "Immediate or Cancel"; break;
        case '4': retStr = "Fill or Kill"; break;
        case '5': retStr = "Good Till Crossing"; break;
        case '6': retStr = "Good Till Date"; break;
        case '7': retStr = "At the Close"; break;
        default: retStr = "NoTimeInForce";
    }

    return retStr;

}

string ExecutionReportHandler::getTransactTimeStr(const FIX44::ExecutionReport& execReport) const {
    FIX::TransactTime transactTime;
    return execReport.getIfSet(transactTime) ? execReport.get(transactTime).getString() : "";
}

string ExecutionReportHandler::getSettlDateStr(const FIX44::ExecutionReport& execReport) const {
    FIX::SettlDate settlDate;
    return execReport.getIfSet(settlDate) ? execReport.get(settlDate).getString() : "";
}

string ExecutionReportHandler::getListIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::ListID listID;
    return execReport.getIfSet(listID) ? execReport.get(listID).getString() : "";
}

string ExecutionReportHandler::getTradeDateStr(const FIX44::ExecutionReport& execReport) const {
    FIX::TradeDate tradeDate;
    return execReport.getIfSet(tradeDate) ? execReport.get(tradeDate).getString() : "";
}

string ExecutionReportHandler::getExecTypeStr(const FIX44::ExecutionReport& execReport) const {
    FIX::ExecType execType;

    string ret;

    if(!execReport.getIfSet(execType)) {
        return "";
    }

    switch (execReport.get(execType).getValue()) {
        case '0': ret = "New"; break;
        case '1': ret = "Partial fill"; break;
        case '2': ret = "Fill"; break;
        case '3': ret = "Done for day"; break;
        case '4': ret = "Canceled"; break;
        case '5': ret = "Replace"; break;
        case '6': ret = "Pending Cancel"; break;
        case '7': ret = "Stopped"; break;
        case '8': ret = "Rejected"; break;
        case '9': ret = "Suspended"; break;
        case 'A': ret = "Pending New"; break;
        case 'B': ret = "Calculated"; break;
        case 'C': ret = "Expired"; break;
        case 'D': ret = "Restated"; break;
        case 'E': ret = "Pending Replace"; break;
        case 'F': ret = "Trade"; break;
        case 'G': ret = "Trade Correct"; break;
        case 'H': ret = "Trade Cancel"; break;
        case 'I': ret = "Order Status"; break;
        default: ret = "NoExecType";
    }

    return ret;

}

string ExecutionReportHandler::getLeavesQtyStr(const FIX44::ExecutionReport& execReport) const {
    FIX::LeavesQty leavesQty;
    return execReport.getIfSet(leavesQty) ? execReport.get(leavesQty).getString() : "";
}

string ExecutionReportHandler::getEffectiveTimeStr(const FIX44::ExecutionReport& execReport) const {
    FIX::EffectiveTime effectiveTime;
    return execReport.getIfSet(effectiveTime) ? execReport.get(effectiveTime).getString() : "";
}

string ExecutionReportHandler::getNoContraBrokersStr(const FIX44::ExecutionReport& execReport) const {
    FIX::NoContraBrokers noContraBrokers;
    return execReport.getIfSet(noContraBrokers) ? execReport.get(noContraBrokers).getString() : "";
}

string ExecutionReportHandler::getSecondaryExecIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::SecondaryExecID secondaryExecID;
    return execReport.getIfSet(secondaryExecID) ? execReport.get(secondaryExecID).getString() : "";
}

string ExecutionReportHandler::getPartyIDStr(const FIX44::ExecutionReport& execReport) const {
    FIX::NoPartyIDs noPartyIDs;

    if(!execReport.getIfSet(noPartyIDs)) {
        return "";
    }

    if( !execReport.get(noPartyIDs).getValue() )
        return "";

    FIX44::ExecutionReport::NoPartyIDs group;
    FIX::PartyID partyID;

    execReport.getGroup(1, group);
    return group.getIfSet(partyID) ? group.get(partyID).getValue() : "";

}

string ExecutionReportHandler::getContraBrokerStr(const FIX44::ExecutionReport& execReport) const {
    FIX::NoContraBrokers noContraBrokers;

    if(!execReport.getIfSet(noContraBrokers)) {
        return "";
    }

    if( !execReport.get(noContraBrokers).getValue() )
        return "";

    FIX44::ExecutionReport::NoContraBrokers group;
    FIX::ContraBroker contraBroker;

    execReport.getGroup(1, group);
    return group.getIfSet(contraBroker) ? group.get(contraBroker).getValue() : "";

}

double ExecutionReportHandler::getAvgPx(const FIX44::ExecutionReport& execReport) const {
    FIX::AvgPx avgPx;
    return execReport.getIfSet(avgPx) ? execReport.get(avgPx).getValue() : 0.;
}

double ExecutionReportHandler::getCumQty(const FIX44::ExecutionReport& execReport) const {
    FIX::CumQty cumQty;
    return execReport.getIfSet(cumQty) ? execReport.get(cumQty).getValue() : 0.;
}

double ExecutionReportHandler::getLastPx(const FIX44::ExecutionReport& execReport) const {
    FIX::LastPx lastPx;
    return execReport.getIfSet(lastPx) ? execReport.get(lastPx).getValue() : 0.;
}

double ExecutionReportHandler::getLastQty(const FIX44::ExecutionReport& execReport) const {
    FIX::LastQty lastQty;
    return execReport.getIfSet(lastQty) ? execReport.get(lastQty).getValue() : 0.;
}

double ExecutionReportHandler::getPrice(const FIX44::ExecutionReport& execReport) const {
    FIX::Price price;
    return execReport.getIfSet(price) ? execReport.get(price).getValue() : 0.;
}

double ExecutionReportHandler::getLeavesQty(const FIX44::ExecutionReport& execReport) const {
    FIX::LeavesQty leavesQty;
    return execReport.getIfSet(leavesQty) ? execReport.get(leavesQty).getValue() : 0.;
}

double ExecutionReportHandler::getOrderQty(const FIX44::ExecutionReport& execReport) const {
    FIX::OrderQty orderQty;
    return execReport.getIfSet(orderQty) ? execReport.get(orderQty).getValue() : 0.;
}




