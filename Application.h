#ifndef CURVE_FIX_CURVE_H
#define CURVE_FIX_CURVE_H


#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"

#include "quickfix/fix44/ExecutionReport.h"

#include <queue>

class Application :
        public FIX::Application,
        public FIX::MessageCracker
{
public:
    void run();

private:
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

};

#endif //CURVE_FIX_CURVE_H
