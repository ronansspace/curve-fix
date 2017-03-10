# curve-fix

sudo cmake .. -DCMAKE_INSTALL_PREFIX=/usr/bin

The Execution Report we get from TraderTools includes the number codes of each field.

To Key -> Field mappings are described here http://www.onixs.biz/fix-dictionary/4.4/fields_by_tag.html

Specifics for the Execution Report fields can be found here http://www.onixs.biz/fix-dictionary/4.4/msgType_8_8.html

Some fields such as A54=Side are sent as a char. Which further maps to the fields enumeration e.g 1 = Buy, 2 = Sell


std::string FIXMessage;
    std::string BeginString;
    FIX::LENGTH  BodyLength;
    std::string MsgType;
    FIX::SEQNUM MsgSeqNum;
    std::string SenderCompID;
    FIX::UTCTIMESTAMP SendingTime;
    std::string TargetCompID;
    std::string Account;
    FIX::PRICE AvgPx;
    std::string ClOrdID;
    FIX::QTY CumQty;
    FIX::CURRENCY Currency;
    std::string ExecID;
    FIX::PRICE LastPx;
    FIX::QTY LastQty;
    std::string OrderID;
    FIX::QTY OrderQty;
    char OrderStatus;
    char OrdType;
    FIX::PRICE  Price;
    char Side;
    char TimeInForce;
    FIX::UTCTIMESTAMP TransactTime;
    FIX::LOCALMKTDATE SettlDate;
    std::string ListID;
    FIX::LOCALMKTDATE TradeDate;
    char ExecType;
    FIX::QTY LeavesQty;
    FIX::UTCTIMESTAMP EffectiveTime;
    FIX::NUMINGROUP NoContraBrokers;
    std::string ContraBroker;
    std::string SecondaryExecID;
    std::string CheckSum;
