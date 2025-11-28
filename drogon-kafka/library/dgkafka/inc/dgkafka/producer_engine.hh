#ifndef PRODUCER_ENGINE_HH
#define PRODUCER_ENGINE_HH
#include <vector>

#include <json/json.h>

#include "trade_type.hh"

struct ProducerEngine {
	std::vector<StockTrade_t*> *trade_data = nullptr;

	ProducerEngine(std::vector<StockTrade_t*> *data);
	~ProducerEngine();

    // --------------------------------------------------------- //

	void _start_runtime();

	// --------------------------------------------------------- //

	Json::Value get_trade_data() const;
	std::string get_trade_data_as_string() const;
}; // struct ProducerEngine

#endif // PRODUCER_ENGINE_HH

