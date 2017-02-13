#ifndef CURVE_APPLICATION_H
#define CURVE_APPLICATION_H

#include <memory>
#include <chrono>
#include <thread>

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"
#include "quickfix/fix44/ExecutionReport.h"
#include "quickfix/fix44/MarketDataRequest.h"
#include "quickfix/fix44/MarketDataSnapshotFullRefresh.h"
#include "ExecutionReport/ExecutionReportHandler.h"

class Application :
        public FIX::Application,
        public FIX::MessageCracker
{
public:
    void run();
    void setIsLoggedOn(bool i) {isLoggedOn = i;}
    void setIsMarketSession(bool i) {isMarketSession = i;}

private:
    bool isLoggedOn;
    bool isMarketSession;

    void onCreate( const FIX::SessionID& ) {}
    void onLogon( const FIX::SessionID& sessionID );
    void onLogout( const FIX::SessionID& sessionID );
    void toAdmin( FIX::Message&, const FIX::SessionID& ) {}
    void toApp( FIX::Message&, const FIX::SessionID& )
    throw( FIX::DoNotSend );
    void fromAdmin( const FIX::Message&, const FIX::SessionID& )
    throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {}
    void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
    throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );

    void onMessage( const FIX44::ExecutionReport&, const FIX::SessionID& );
    void onMessage( const FIX44::TradingSessionStatus&, const FIX::SessionID& );
    void onMessage( const FIX44::MarketDataRequest&, const FIX::SessionID& );
    void onMessage( const FIX44::MarketDataSnapshotFullRefresh&, const FIX::SessionID& );

};

#endif //CURVE_APPLICATION
