#include "MarketDataReport/MarketDataRequestor.h"

using namespace std;


void MarketDataRequestor::send(const FIX::SessionID& sessionID) const {

    sql::Driver *driver = get_driver_instance();

    unique_ptr<sql::Connection> con(driver->connect("tcp://localhost", "root", "bc43f15f516460e8966700a05761371e0235799a6d86ffd7"));
    con->setSchema("cmarkets");

    unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT ccypair from ccyrate"));
    unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

    res->afterLast();

    while (res->previous()) {
        string iCcyPair = res->getString("ccypair");
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

}

