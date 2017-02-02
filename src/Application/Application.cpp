#include "Application/Application.h"

using namespace std;

void Application::onLogon( const FIX::SessionID& sessionID )
{
    cout << endl << "We are logged on - " << sessionID << endl;
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

void Application::onMessage(const FIX44::TradingSessionStatus &, const FIX::SessionID &) {

}

void Application::run()
{
    cout << "Running Curve FIX Client." << endl;

    while(true) {}
}