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

        unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("DELETE FROM ccyrate WHERE ccypair='" +ccyPair + "'");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO ccyrate(ccypair,rate) VALUES (?,?)"));

        pstmt->setString(1, ccyPair);
        pstmt->setDouble(2, getRate(mktReport));

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

void MarketDataReportHandler::toConsole(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {
    cout << mktReport.toString() << endl;
}

string MarketDataReportHandler::getCcyPairStr(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {
    FIX::Symbol symbol;
    return mktReport.getIfSet(symbol) ? mktReport.get(symbol).getString() : "";
}

string MarketDataReportHandler::getRateStr(const FIX44::MarketDataSnapshotFullRefresh& mktReport) const {
    FIX::NoMDEntries noMDEntries;
    if( !mktReport.get(noMDEntries).getValue() )
        return "1";

    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
    FIX::MDEntryPx mdEntryPx;

    mktReport.getGroup(1, group);
    return group.getIfSet(mdEntryPx) ? group.get(mdEntryPx).getString() : "1";
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


