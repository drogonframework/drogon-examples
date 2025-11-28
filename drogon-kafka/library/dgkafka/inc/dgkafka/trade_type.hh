#ifndef TRADE_TYPE_HH
#define TRADE_TYPE_HH
#include <json/json.h>
#include <drogon/PubSubService.h>

// --------------------------------------------------------- //

/// @brief stock trade type
typedef struct _StockTrade_t {
    double stock; // should not less than 0.00
	std::string currency; // must capital
	std::string last_updated; // timestamp
	std::string id; // must capital
} StockTrade_t;

/// @brief convert TradeData_t to Json::Value
///
/// @param data TradeData_t - data to convert 
///
/// @return Json::Value 
static Json::Value _TradeData_to_json(const StockTrade_t &data) {
    Json::Value json;

    json["stock"] = data.stock;
    json["currency"] = data.currency;
    json["id"] = data.id;

    return json;
}

// --------------------------------------------------------- //

#endif // TRADE_TYPE_HH

