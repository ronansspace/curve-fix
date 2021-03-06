#include "MarketDataReport/MarketDataReportHandler.h"

using namespace std;

map<string, string> MarketDataReportHandler::toMap(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {

    map<string, string> fields;

    fields.insert(pair<string, string>("CcyPair", getCcyPairStr(mktReport)));
    fields.insert(pair<string, string>("Rate", getRateStr(mktReport)));

    return fields;

}

void MarketDataReportHandler::toFile(const FIX44::MarketDataSnapshotFullRefresh& mktReport, const string & fileName) const {

    map<string, string> fields = toMap(mktReport);

    ofstream ofile;
    ofile.open(fileName.c_str());

    if(ofile) {
        for (map<string, string>::const_iterator it = fields.begin(); it != fields.end(); ++it) {
            ofile << it->first << "|" << it->second;
            ofile << "\n";
        }
    }

}

void MarketDataReportHandler::toDB(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {

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

        string ccyPair = getCcyPairStr(mktReport);
        ccyPair.erase(remove(ccyPair.begin(), ccyPair.end(), '/'));

        unique_ptr<sql::PreparedStatement> pstmtchk(con->prepareStatement("SELECT * from ccyrate where ccypair=? and trade_date=?"));
        pstmtchk->setString(1, ccyPair);
        pstmtchk->setString(2, getSendingTimeStr(mktReport).substr(0,8));
        unique_ptr<sql::ResultSet> reschk(pstmtchk->executeQuery());

        if(reschk->rowsCount()) {
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE ccyrate SET rate=?, date=? WHERE ccypair=? and trade_date=?"));
            pstmt->setDouble(1, getRate(mktReport));
            pstmt->setString(2, getSendingTimeStr(mktReport));
            pstmt->setString(3, ccyPair);
            pstmt->setString(4, getSendingTimeStr(mktReport).substr(0, 8));
            pstmt->executeUpdate();
        }else {
            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO ccyrate (trade_date, ccypair, rate, date) VALUES (?,?,?,?)"));
            pstmt->setString(1, getSendingTimeStr(mktReport).substr(0, 8));
            pstmt->setString(2, ccyPair);
            pstmt->setDouble(3, getRate(mktReport));
            pstmt->setString(4, getSendingTimeStr(mktReport));
            pstmt->executeUpdate();
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

void MarketDataReportHandler::toConsole(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {
    cout << mktReport.toString() << endl;
}

string MarketDataReportHandler::getSendingTimeStr(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {
    FIX::SendingTime sendingTime;
    FIX44::Header header = mktReport.getHeader();
    return header.getIfSet(sendingTime) ? header.get(sendingTime).getString() : "";
}

string MarketDataReportHandler::getCcyPairStr(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {
    FIX::Symbol symbol;
    return mktReport.getIfSet(symbol) ? mktReport.get(symbol).getString() : "";
}

string MarketDataReportHandler::getRateStr(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {
    FIX::NoMDEntries noMDEntries;

    if(!mktReport.getIfSet(noMDEntries)) {
        return "";
    }

    if( !mktReport.get(noMDEntries).getValue() )
        return "1";

    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
    FIX::MDEntryPx mdEntryPx;

    mktReport.getGroup(1, group);
    return group.getIfSet(mdEntryPx) ? group.get(mdEntryPx).getString() : "1";
}

string MarketDataReportHandler::getTradingDateStr(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {
    FIX::NoMDEntries noMDEntries;

    if(!mktReport.getIfSet(noMDEntries)) {
        return "";
    }

    if( !mktReport.get(noMDEntries).getValue() )
        return "1";

    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
    FIX::MDEntryDate mdEntryDate;

    mktReport.getGroup(1, group);
    return group.getIfSet(mdEntryDate) ? group.get(mdEntryDate).getString() : "1";
}

double MarketDataReportHandler::getRate(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {
    FIX::NoMDEntries noMDEntries;
    if( !mktReport.get(noMDEntries).getValue() )
        return 1.;

    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
    FIX::MDEntryPx mdEntryPx;

    mktReport.getGroup(1, group);
    return group.getIfSet(mdEntryPx) ? group.get(mdEntryPx).getValue() : 1.;
}


