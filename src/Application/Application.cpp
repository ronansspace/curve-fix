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

    unique_ptr<ExecutionReportHandler> execReport(new ExecutionReportHandler(sourceSystem));
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

}

void Application::onMessage
        ( const FIX44::MarketDataRequestReject& mdReject, const FIX::SessionID& sessionID) {
    cout << "Process Market Data Request Reject- " << sessionID << endl;
}

void Application::onMessage(const FIX44::TradingSessionStatus &, const FIX::SessionID &) {
}

void Application::run()
{
    cout << "Running Curve FIX Client." << endl;

    if(isMarketSession) {
        while(!isLoggedOn) {
            cout << "Waiting for successful Login." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        unique_ptr<MarketDataRequestor> mdRequestor(new MarketDataRequestor());
        mdRequestor->send(sessionID);

        // Very basic timer.
        int count = 0;
        while(count < 10) {
            cout << "Waiting for market data requests to be filled." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            count++;
        }

    } else{
        bool check = true;
        while(check) {
            time_t t = time(0);   // get time now
            unique_ptr<tm> now(localtime(&t));
            int hour = now->tm_hour;
            int minute = now->tm_min;

            if( hour >= 23 && minute >= 55) {
                check = false;
            }
        }
    }

    cout << "All Done." << endl;

}