#include "Application/Application.h"

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
    crack( message, sessionID );
    std::cout << std::endl << "IN: " << message << std::endl;
}

void Application::toApp( FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::DoNotSend )
{
}

void Application::onMessage
        ( const FIX44::ExecutionReport&, const FIX::SessionID& ) {
    std::cout << "Got an Execution Report" << std::endl;
}

void Application::run()
{
    std::cout << "Running Curve FIX Client." << std::endl;

    while(true) {}
}