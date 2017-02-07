#include "Application/Application.h"

using namespace std;

void Application::onLogon( const FIX::SessionID& sessionID )
{
    cout << endl << "We are logged on - " << sessionID << endl;

    FIX::MDReqID mdReqID( "MARKETDATAID" );
    FIX::SubscriptionRequestType subType( FIX::SubscriptionRequestType_SNAPSHOT );
    FIX::MarketDepth marketDepth( 0 );

    FIX44::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup;
    FIX::MDEntryType mdEntryType( FIX::MDEntryType_BID );
    marketDataEntryGroup.set( mdEntryType );

    FIX44::MarketDataRequest::NoRelatedSym symbolGroup;
    FIX::Symbol symbol( "EUR/USD" );
    symbolGroup.set( symbol );

    FIX44::MarketDataRequest message( mdReqID, subType, marketDepth );
    message.addGroup( marketDataEntryGroup );
    message.addGroup( symbolGroup );

    FIX44::Header header = message.getHeader();

    header.setField(FIX::SenderCompID("FIXUAT16-MD"));
    header.setField(FIX::TargetCompID("TTUAT-MD"));

    std::cout << message.toXML() << std::endl;
    std::cout << message.toString() << std::endl;

    FIX::Session::sendToTarget(message, sessionID);

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
    execReport->toFile(executionReport, "test.out");
    execReport->toDB(executionReport);
}

void Application::onMessage
        ( const FIX44::MarketDataRequest& marketData, const FIX::SessionID& sessionID) {

    cout << "Processing MarketData - " << sessionID << endl;

    cout << marketData.toString() << endl;
}

void Application::onMessage(const FIX44::TradingSessionStatus &, const FIX::SessionID &) {

}

void Application::run()
{
    cout << "Running Curve FIX Client." << endl;

    while(true) {}
}