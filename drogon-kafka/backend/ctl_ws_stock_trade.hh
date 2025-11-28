#ifndef CTL_WS_STOCK_TRADE_HH
#define CTL_WS_STOCK_TRADE_HH
#include <drogon/WebSocketController.h>
#include <drogon/PubSubService.h>
#include <drogon/drogon.h>
#include <cppkafka/cppkafka.h>
#include <dgkafka/trade_type.hh>

using namespace drogon;

/// @brief consume stock trade controller
class CtlWsStockTrade : public WebSocketController<CtlWsStockTrade> {
    PubSubService<std::string> _stocks;
public:
	CtlWsStockTrade();
	// METHOD_LIST_BEGIN
	// WS_PATH_ADD("/ws/stock/trade", {Get});
	// WS_ADD_PATH_VIA_REGEX("/ws/stock/trade[^/]*", {Get});
	// METHOD_LIST_END
	// or
	static void initPathRouting() {
		registerSelf__("/ws/stock/trade", { Get });
		registerSelfRegex__("/ws/stock/trade[^/]*", { Get });
	}

    virtual void handleNewMessage(const WebSocketConnectionPtr &p_wsconn,
                                  std::string &&message,
                                  const WebSocketMessageType &ws_msg_type) override;
    virtual void handleNewConnection(const HttpRequestPtr &p_req,
                                     const WebSocketConnectionPtr &p_wsconn) override;
    virtual void handleConnectionClosed(const WebSocketConnectionPtr &p_wsconn) override;
}; // class CtlWsStockTrade

#endif // CTL_WS_STOCK_TRADE_HH

