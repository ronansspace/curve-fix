#include "Application/Application.h"

using namespace std;

void Application::onLogon( const FIX::SessionID& sessionID )
{
    cout << endl << "We are logged on - " << sessionID << endl;
    this->isLoggedOn = true;
}

void Application::onLogout( const FIX::SessionID& sessionID )
{
    cout << endl << "Logout Message - " << sessionID << endl;
}

void Application::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
    crack( message, sessionID );
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

void Application::onMessage
        ( const FIX44::MarketDataSnapshotFullRefresh& marketData, const FIX::SessionID& sessionID) {
    cout << "Processing MarketData Snapshot Full Refresh- " << sessionID << endl;

    unique_ptr<MarketDataReportHandler> mktReport(new MarketDataReportHandler());
    mktReport->toDB(marketData);
    string ccyPair = mktReport->getCcyPairStr(marketData);
    ccyPairs.remove(ccyPair);

}

void Application::onMessage
        ( const FIX44::MarketDataRequestReject& mdReject, const FIX::SessionID& sessionID) {
    cout << "Process Market Data Request Reject- " << sessionID << endl;

    FIX::MDReqID mdReqID;

    if( mdReject.getIfSet(mdReqID) ) {
        string mdReqIDStr = mdReject.get(mdReqID).getString();
        string ccyPair = mdReqIDStr.substr(mdReqIDStr.length() - 5);
        ccyPair.erase(remove(ccyPair.begin(), ccyPair.end(), '/'));
        ccyPairs.remove(ccyPair);
    }
}

void Application::onMessage(const FIX44::TradingSessionStatus &, const FIX::SessionID &) {
}

void Application::sendMarketDataRequest(const string &iCcyPair) {

    cout << "Requesting " + iCcyPair << endl;

    ccyPairs.push_back(iCcyPair);
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

void Application::run()
{
    cout << "Running Curve FIX Client." << endl;

    if(isMarketSession) {
        while(!isLoggedOn) {
            cout << "Waiting for successful Login." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        sendMarketDataRequest("EUR/USD");
        sendMarketDataRequest("USD/CHF");
        sendMarketDataRequest("USD/JPY");
        sendMarketDataRequest("AUD/USD");
        sendMarketDataRequest("GBP/USD");
        sendMarketDataRequest("USD/CAD");
        sendMarketDataRequest("EUR/CHF");
        sendMarketDataRequest("EUR/GBP");
        sendMarketDataRequest("EUR/CAD");
        sendMarketDataRequest("EUR/JPY");
        sendMarketDataRequest("GBP/CHF");
        sendMarketDataRequest("GBP/CAD");
        sendMarketDataRequest("USD/TRY");
        sendMarketDataRequest("EUR/TRY");
        sendMarketDataRequest("USD/ZAR");
        sendMarketDataRequest("NZD/USD");

        while(!ccyPairs.empty()) {} // Loop until all ccy pairs have been updated.

    } else{
        while(true) {}
    }

    cout << "All Done." << endl;

}