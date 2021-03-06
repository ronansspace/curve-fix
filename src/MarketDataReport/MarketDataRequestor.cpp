#include "MarketDataReport/MarketDataRequestor.h"

using namespace std;


void MarketDataRequestor::send(const FIX::SessionID& sessionID) const {

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

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT pair from ccy_pair"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        res->afterLast();

        while (res->previous()) {
            string iCcyPair = res->getString("pair");
            iCcyPair.insert(3, "/");
            cout << "Requesting " + iCcyPair << endl;

            string requestID = "Request" + iCcyPair;
            FIX::MDReqID mdReqID( requestID );
            FIX::SubscriptionRequestType subType( FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES );
            FIX::MarketDepth marketDepth( 0 );
            FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup;
            FIX::MDEntryType mdEntryType( FIX::MDEntryType_BID );
            marketDataEntryGroup.set( mdEntryType );
            FIX44::MarketDataRequest::NoRelatedSym symbolGroup;
            symbolGroup.set( FIX::Symbol(iCcyPair) );
            FIX44::MarketDataRequest message( mdReqID, subType, marketDepth);
            message.setField(FIX::MDUpdateType(0));
            message.addGroup( marketDataEntryGroup );
            message.addGroup( symbolGroup );
            FIX::Session::sendToTarget(message, sessionID);
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

