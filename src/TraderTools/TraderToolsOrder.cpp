#include "TraderTools/TraderToolsOrder.h"

using namespace std;

void TraderToolsOrder::processOrder() const {

    try {
        sql::Driver *driver = get_driver_instance();

        ifstream infile("/root/.mysql_password");
        string sLine;
        if (infile.good())
        {

            getline(infile, sLine);
        }

        infile.close();

        unique_ptr<sql::Connection> con(driver->connect("tcp://localhost", "root", sLine));
        con->setSchema("cmarkets");

        /* Get the common order ID from the Execution ID */
        string curveOrder = this->execID;
        curveOrder.erase(curveOrder.rfind('-'));
        curveOrder.erase(curveOrder.rfind('-'));

        if( !curveOrder.substr(0, 2).compare("V-"))
            curveOrder.erase(0,2);

        unique_ptr<sql::PreparedStatement> pstmt1(con->prepareStatement("SELECT * from FIXOrderReport WHERE CurveOrder=?"));
        pstmt1->setString(1, curveOrder);
        unique_ptr<sql::ResultSet> res(pstmt1->executeQuery());

       if(res->rowsCount() == 0) {
           unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXOrderReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));
           buildFIXOrder(move(pstmt))->executeUpdate();

           unique_ptr<sql::PreparedStatement> pstmtOrd(con->prepareStatement("INSERT INTO contract ( payout_ccy, tdrID, client, ccy_pair, buy_sell, Notional, rate, calc, trade_date, value_date, traded_as, prime_broker, order_entry_time, fx_pair_id, contract, account, trade_entry_type, pb_email, client_email, client_trader) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));
           buildFIXContract(move(pstmtOrd))->executeUpdate();

       } else {
           unique_ptr<sql::PreparedStatement> pstmt1(con->prepareStatement("SELECT * from FIXOrderReport WHERE CurveOrder=? AND Account=?"));
           pstmt1->setString(1, curveOrder);
           pstmt1->setString(2, this->account);
           unique_ptr<sql::ResultSet> res(pstmt1->executeQuery());

           if(res->rowsCount() == 0) {
               unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXOrderReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));
               buildFIXOrderReverse(move(pstmt))->executeUpdate();

               unique_ptr<sql::PreparedStatement> pstmtOrd(con->prepareStatement("INSERT INTO contract ( payout_ccy, tdrID, client, ccy_pair, buy_sell, Notional, rate, calc, trade_date, value_date, traded_as, prime_broker, order_entry_time, fx_pair_id, contract, account, trade_entry_type, pb_email, client_email, client_trader) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));
               buildFIXContractReverse(move(pstmtOrd))->executeUpdate();
           } else {
               unique_ptr<sql::PreparedStatement> pstmt1(con->prepareStatement("SELECT * from FIXOrderReport WHERE CurveOrder=? AND Account=? AND ClientOrder=true"));
               pstmt1->setString(1, curveOrder);
               pstmt1->setString(2, this->account);
               unique_ptr<sql::ResultSet> res(pstmt1->executeQuery());

               if(res->rowsCount() == 0) {
                   unique_ptr<sql::Statement> stmt(con->createStatement());
                   stmt->execute("DELETE FROM FIXOrderReport WHERE CurveOrder='" + curveOrder + "' AND Account='" + this->account + "'");
                   stmt->execute("DELETE FROM contract WHERE fx_pair_id='" + curveOrder + "' AND client='" + this->account + "'");

                   unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXOrderReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));
                   buildFIXOrder(move(pstmt))->executeUpdate();

                   unique_ptr<sql::PreparedStatement> pstmtOrd(con->prepareStatement("INSERT INTO contract ( payout_ccy, tdrID, client, ccy_pair, buy_sell, Notional, rate, calc, trade_date, value_date, traded_as, prime_broker, order_entry_time, fx_pair_id, contract, account, trade_entry_type, pb_email, client_email, client_trader) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));
                   buildFIXContract(move(pstmtOrd))->executeUpdate();

               } else {
                   unique_ptr<sql::Statement> stmt(con->createStatement());
                   stmt->execute("DELETE FROM FIXOrderReport WHERE CurveOrder='" + curveOrder + "' AND Account='" + this->account + "'");
                   stmt->execute("DELETE FROM contract WHERE fx_pair_id='" + curveOrder + "' AND client='" + this->account + "'");

                   unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO FIXOrderReport VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));
                   buildFIXOrderReverse(move(pstmt))->executeUpdate();

                   pstmt->executeUpdate();

                   unique_ptr<sql::PreparedStatement> pstmtOrd(con->prepareStatement("INSERT INTO contract ( payout_ccy, tdrID, client, ccy_pair, buy_sell, Notional, rate, calc, trade_date, value_date, traded_as, prime_broker, order_entry_time, fx_pair_id, contract, account, trade_entry_type, pb_email, client_email, client_trader) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"));
                   buildFIXContractReverse(move(pstmtOrd))->executeUpdate();

                   pstmtOrd->executeUpdate();
               }
           }
       }
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

}

std::unique_ptr<sql::PreparedStatement> TraderToolsOrder::buildFIXOrder(std::unique_ptr<sql::PreparedStatement> pstmt) const {

    string curveOrder = this->execID;
    curveOrder.erase(curveOrder.rfind('-'));
    curveOrder.erase(curveOrder.rfind('-'));

    if( !curveOrder.substr(0, 2).compare("V-"))
        curveOrder.erase(0,2);

    pstmt->setString(1, this->account);
    pstmt->setString(2, this->symbol);
    pstmt->setDouble(3, this->avgPx);
    pstmt->setString(4, this->clOrdID);
    pstmt->setDouble(5, this->cumQty);
    pstmt->setString(6, this->currency);
    pstmt->setString(7, this->execID);
    pstmt->setDouble(8, this->lastPx);
    pstmt->setDouble(9, this->lastQty);
    pstmt->setString(10, this->orderID);
    pstmt->setDouble(11, this->orderQty);
    pstmt->setString(12, this->ordStatus);
    pstmt->setString(13, this->ordType);
    pstmt->setDouble(14, this->price);
    pstmt->setString(15, this->side);
    pstmt->setString(16, this->timeInForce);
    pstmt->setString(17, this->transactTime);
    pstmt->setString(18, this->settlDate);
    pstmt->setString(19, this->listID);
    pstmt->setString(20, this->tradeDate);
    pstmt->setString(21, this->execType);
    pstmt->setDouble(22, this->leavesQty);
    pstmt->setString(23, this->effectiveTime);
    pstmt->setString(24, this->noContraBrokers);
    pstmt->setString(25, this->secondaryExecID);
    pstmt->setString(26, this->partyID);
    pstmt->setString(27, this->contraBroker);
    pstmt->setString(28, "TraderTools");
    pstmt->setBoolean(29, 0);
    pstmt->setString(30, curveOrder);

    return move(pstmt);
}

std::unique_ptr<sql::PreparedStatement> TraderToolsOrder::buildFIXOrderReverse(std::unique_ptr<sql::PreparedStatement> pstmt) const {

    string curveOrder = this->execID;
    curveOrder.erase(curveOrder.rfind('-'));
    curveOrder.erase(curveOrder.rfind('-'));

    if( !curveOrder.substr(0, 2).compare("V-"))
        curveOrder.erase(0,2);

    pstmt->setString(1, this->account);
    pstmt->setString(2, this->symbol);
    pstmt->setDouble(3, this->avgPx);
    pstmt->setString(4, this->clOrdID);
    pstmt->setDouble(5, this->cumQty);
    pstmt->setString(6, this->currency);
    pstmt->setString(7, this->execID);
    pstmt->setDouble(8, this->lastPx);
    pstmt->setDouble(9, this->lastQty);
    pstmt->setString(10, this->orderID);
    pstmt->setDouble(11, this->orderQty);
    pstmt->setString(12, this->ordStatus);
    pstmt->setString(13, this->ordType);
    pstmt->setDouble(14, this->price);
    pstmt->setString(15, this->side == "Buy" ? "Sell" : "Buy");
    pstmt->setString(16, this->timeInForce);
    pstmt->setString(17, this->transactTime);
    pstmt->setString(18, this->settlDate);
    pstmt->setString(19, this->listID);
    pstmt->setString(20, this->tradeDate);
    pstmt->setString(21, this->execType);
    pstmt->setDouble(22, this->leavesQty);
    pstmt->setString(23, this->effectiveTime);
    pstmt->setString(24, this->noContraBrokers);
    pstmt->setString(25, this->secondaryExecID);
    pstmt->setString(26, this->partyID);
    pstmt->setString(27, this->contraBroker);
    pstmt->setString(28, "TraderTools");
    pstmt->setBoolean(29, 1);
    pstmt->setString(30, curveOrder);

    return move(pstmt);
}


std::unique_ptr<sql::PreparedStatement> TraderToolsOrder::buildFIXContract(std::unique_ptr<sql::PreparedStatement> pstmtOrd) const {
    string curveOrder = this->execID;
    curveOrder.erase(curveOrder.rfind('-'));
    curveOrder.erase(curveOrder.rfind('-'));

    if( !curveOrder.substr(0, 2).compare("V-"))
        curveOrder.erase(0,2);

    pstmtOrd->setString(1, this->currency);
    pstmtOrd->setString(2, this->partyID);
    pstmtOrd->setString(3, this->account);
    pstmtOrd->setString(4, this->symbol);
    pstmtOrd->setString(5, this->side.substr(0, 1));
    pstmtOrd->setDouble(6, this->cumQty);
    pstmtOrd->setString(7, this->avgPxStr);
    pstmtOrd->setString(8, "Multiply");
    pstmtOrd->setString(9, this->tradeDate.substr(6, 2) + "/" + this->tradeDate.substr(4, 2) + "/" + this->tradeDate.substr(0, 4));
    pstmtOrd->setString(10, this->settlDate.substr(6, 2) + "/" + this->settlDate.substr(4, 2) + "/" + this->settlDate.substr(0, 4));
    pstmtOrd->setString(11, "FX");
    pstmtOrd->setString(12, "RBS");
    pstmtOrd->setString(13, this->transactTime);
    pstmtOrd->setString(14, curveOrder);
    pstmtOrd->setString(15, "FXSP");
    pstmtOrd->setString(16, "Curve");
    pstmtOrd->setString(17, "FIX");
    pstmtOrd->setString(18, "2");
    pstmtOrd->setString(19, "2");
    pstmtOrd->setString(20, this->partyID);

    return move(pstmtOrd);

}

std::unique_ptr<sql::PreparedStatement> TraderToolsOrder::buildFIXContractReverse(std::unique_ptr<sql::PreparedStatement> pstmtOrd) const {
    string curveOrder = this->execID;
    curveOrder.erase(curveOrder.rfind('-'));
    curveOrder.erase(curveOrder.rfind('-'));

    if( !curveOrder.substr(0, 2).compare("V-"))
        curveOrder.erase(0,2);

    pstmtOrd->setString(1, this->currency);
    pstmtOrd->setString(2, this->partyID);
    pstmtOrd->setString(3, this->account);
    pstmtOrd->setString(4, this->symbol);
    pstmtOrd->setString(5, this->side == "Buy" ? "S" : "B");
    pstmtOrd->setDouble(6, this->cumQty);
    pstmtOrd->setString(7, this->avgPxStr);
    pstmtOrd->setString(8, "Multiply");
    pstmtOrd->setString(9, this->tradeDate.substr(6, 2) + "/" + this->tradeDate.substr(4, 2) + "/" + this->tradeDate.substr(0, 4));
    pstmtOrd->setString(10, this->settlDate.substr(6, 2) + "/" + this->settlDate.substr(4, 2) + "/" + this->settlDate.substr(0, 4));
    pstmtOrd->setString(11, "FX");
    pstmtOrd->setString(12, "RBS");
    pstmtOrd->setString(13, this->transactTime);
    pstmtOrd->setString(14, curveOrder);
    pstmtOrd->setString(15, "FXSP");
    pstmtOrd->setString(16, "Curve");
    pstmtOrd->setString(17, "FIX");
    pstmtOrd->setString(18, "2");
    pstmtOrd->setString(19, "2");
    pstmtOrd->setString(20, this->partyID);

    return move(pstmtOrd);

}