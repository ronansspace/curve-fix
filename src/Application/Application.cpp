#include "Application/Application.h"

using namespace std;

void Application::onLogon( const FIX::SessionID& sessionID )
{
    cout << endl << "We are logged on - " << sessionID << endl;
    this->isLoggedOn = true;

    //FIX::MDReqID mdReqID( "MARKETDATAID" );
    //FIX::SubscriptionRequestType subType( FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES );
    //FIX::MarketDepth marketDepth( 0 );

    //FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup;
    //FIX::MDEntryType mdEntryType( FIX::MDEntryType_BID );
    //marketDataEntryGroup.set( mdEntryType );

    //FIX44::MarketDataRequest::NoRelatedSym symbolGroup;
    //symbolGroup.set( FIX::Symbol("EUR/USD") );

    //FIX44::MarketDataRequest message( mdReqID, subType, marketDepth);
    //message.setField(FIX::MDUpdateType(0));
    //message.addGroup( marketDataEntryGroup );
    //message.addGroup( symbolGroup );
    //FIX::Session::sendToTarget(message, sessionID);


    //FIX::MDReqID mdReqID1( "MARKETDATAID1" );
    //FIX::SubscriptionRequestType subType1( FIX::SubscriptionRequestType_SNAPSHOT_PLUS_UPDATES );
    //FIX::MarketDepth marketDepth1( 0 );

    //FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup1;
    //FIX::MDEntryType mdEntryType1( FIX::MDEntryType_BID );
    //marketDataEntryGroup1.set( mdEntryType1 );

    //FIX44::MarketDataRequest::NoRelatedSym symbolGroup1;
    //symbolGroup1.set( FIX::Symbol("GBP/USD") );

    //FIX44::MarketDataRequest message1( mdReqID1, subType1, marketDepth1);
    //message1.setField(FIX::MDUpdateType(0));
    //message1.addGroup( marketDataEntryGroup1 );
    //message1.addGroup( symbolGroup1 );
    //FIX::Session::sendToTarget(message1, sessionID);



}

void Application::onLogout( const FIX::SessionID& sessionID )
{
    cout << endl << "Logout Message - " << sessionID << endl;
}

void Application::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
    crack( message, sessionID ); // Takes the message and routes to the appropriate onMessage function.
}

void Application::toApp( FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::DoNotSend )
{
}

void Application::onMessage
        ( const FIX44::ExecutionReport& executionReport, const FIX::SessionID& sessionID) {

    cout << "Processing Execution Report - " << sessionID << endl;

    unique_ptr<ExecutionReportHandler> execReport(new ExecutionReportHandler());
    execReport->toDB(executionReport);
}

void Application::onMessage
        ( const FIX44::MarketDataRequest& marketData, const FIX::SessionID& sessionID) {
    cout << "Processing MarketData Request - " << sessionID << endl;
}

void Application::onMessage( const FIX44::MarketDataSnapshotFullRefresh& marketData, const FIX::SessionID& sessionID) {
    cout << "Processing MarketData Snapshot Full Refresh- " << sessionID << endl;
    cout << marketData.toXML() << endl;
}

void Application::onMessage(const FIX44::TradingSessionStatus &, const FIX::SessionID &) {
}

void Application::run()
{
    cout << "Running Curve FIX Client." << endl;

    while(!isLoggedOn) {
        cout << "Waiting for Logon." << endl;
    }

    while(true) {}
}