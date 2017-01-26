#include "Application/Application.h"
#include <fstream>

void Application::onLogon( const FIX::SessionID& sessionID )
{
    std::cout << std::endl << "We are logged on - " << sessionID << std::endl;
}

void Application::onLogout( const FIX::SessionID& sessionID )
{
    std::cout << std::endl << "Logout Message - " << sessionID << std::endl;
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
    std::cout << "Got an Execution Report" << std::endl;
    std::fstream fs;
    fs.open ("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    fs << executionReport.toString();
    fs.close();


}

void Application::run()
{
    std::cout << "Running Curve FIX Client." << std::endl;

    while(true) {}
}