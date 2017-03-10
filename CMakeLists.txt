cmake_minimum_required(VERSION 3.5)
project(curve_fix)

set(CMAKE_CXX_STANDARD 11)

set ( PROJECT_LINK_LIBS quickfix mysqlcppconn)
link_directories( /usr/local/lib /usr/local/share/mysql/mysql-connector-c++-1.1.8/lib)

include_directories(include /usr/include /usr/local/Cellar/boost/1.63.0/include /usr/local/include/quickfix /usr/local/share/mysql/mysql-connector-c++-1.1.8/include)

set(SOURCES src/main.cpp src/ExecutionReport/ExecutionReportHandler.cpp src/MarketDataReport/MarketDataReportHandler.cpp src/MarketDataReport/MarketDataRequestor.cpp src/Application/Application.cpp src/TraderTools/TraderToolsOrder.cpp)

add_executable(curve_fix ${SOURCES})

target_link_libraries(curve_fix ${PROJECT_LINK_LIBS} )

SET(HS cfg/FIXSpecs/FIX44.xml cfg/flex-trade-engine.cfg cfg/trader-tools-engine-live.cfg cfg/trader-tools-engine.cfg cfg/trader-tools-MD-engine-live.cfg cfg/trader-tools-MD-engine.cfg cfg/flex-trade-engine.cfg)

install(FILES ${HS} DESTINATION curve_fix/cfg)
install(TARGETS curve_fix DESTINATION curve_fix)