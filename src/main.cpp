#include "quickfix/FileStore.h"
#include "quickfix/SocketInitiator.h"
#include "Application/Application.h"

int main( int argc, char** argv )
{
    if ( argc != 4 )
    {
        std::cout << "usage: " << argv[ 0 ]
                  << " QuickFIX Settings File."
                  << " isMarketSession(true/false)."
                  << " source system.."
                  << std::endl;
        return 0;
    }
    std::string file = argv[ 1 ];
    std::string source = argv[3];
    std::stringstream ss(argv[2]);
    bool isMarketSession;
    if(!(ss >> std::boolalpha >> isMarketSession)) {
        isMarketSession = false;
    }

    try
    {
        FIX::SessionSettings settings( file );
        Application application;
        application.setIsLoggedOn(false);
        application.setSourceSystem(source);
        application.setIsMarketSession(isMarketSession);
        FIX::FileStoreFactory storeFactory( settings );
        FIX::ScreenLogFactory logFactory( settings );
        FIX::SocketInitiator initiator( application, storeFactory, settings, logFactory );
        initiator.start();
        application.run();
        initiator.stop();

        return 0;
    }
    catch ( std::exception & e )
    {
        std::cout << e.what();
        return 1;
    }
}