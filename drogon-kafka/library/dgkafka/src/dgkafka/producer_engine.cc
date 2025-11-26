#include <dgkafka/producer_engine.hh>
#include <dgkafka/util_helper.hh>
#include <dgkafka/config.hh>

#include <thread>

// --------------------------------------------------------- //

ProducerEngine::ProducerEngine(std::vector<StockTrade_t*> *data)
	: trade_data(data) {}

ProducerEngine::~ProducerEngine() {
	if (trade_data || !trade_data->empty()) {
		for (auto *data : *trade_data) {
			if (data) { delete data; }
		}
		delete trade_data;
	}
}

// --------------------------------------------------------- //

void ProducerEngine::_start_runtime() {
	if (this->trade_data->empty()) {
		std::cerr << "ERROR: trade_data still empty\n";
		return;
	}

	std::vector<std::thread> threads;

	// runtime adjustmen data
	// this loop is meant to simulate
	// when entity purchased & sold their stock
	for (auto p_biz : *trade_data) {
		threads.emplace_back([p_biz]() {
			double update_value = 0.00;
			int32_t increase_or_decrease = util_helper::random_num_round(0, 10);
			
			// only apply 1 (purchased) & 2 (sold) by entity
			switch (increase_or_decrease) {
			case 1: {
				update_value = util_helper::random_num_decimal(1'000.00, 3'000.00);

				p_biz->stock += update_value;

				p_biz->last_updated = util_helper::timestamp();
			} break;

			case 2: {
				update_value = util_helper::random_num_decimal(1'000.00, 3'000.00);

				if (!(p_biz->stock < 0.00)) {
					p_biz->stock -= update_value;
				}

				p_biz->last_updated = util_helper::timestamp();
			} break;

			default: {
				// skip, nothing to update
			} break;
			}
		}).detach(); // or se THIS_ONE if not using detach
	}

	// // NOTE: THIS_ONE
	// // wait to all threads task completed
	// for (auto &t : threads) {
	// 	if (t.joinable()) { t.join(); }
	// }

	// delay trap
	std::this_thread::sleep_for(std::chrono::milliseconds(DGKAFKA_DELAY));
}

// --------------------------------------------------------- //

Json::Value ProducerEngine::get_trade_data() const {
	Json::Value json;

	for (auto p_biz : *trade_data) {
		Json::Value data;

		data["id"] = p_biz->id;
		data["currency"] = p_biz->currency;
		data["last_updated"] = p_biz->last_updated;
		data["stock"] = p_biz->stock;

		json.append(data);
	}

	return json;
}

std::string ProducerEngine::get_trade_data_as_string() const {
	return util_helper::jsoncpp::to_string(this->get_trade_data(), 0);
}

