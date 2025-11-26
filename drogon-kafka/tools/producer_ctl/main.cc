#include <cppkafka/cppkafka.h>
#include <dgkafka/config.hh>
#include <dgkafka/trade_type.hh>
#include <dgkafka/util_helper.hh>
#include <dgkafka/producer_engine.hh>

#include <vector>
#include <atomic>
#include <csignal>

// --------------------------------------------------------- //

static std::atomic<bool> _producer_is_running(true);

void signal_handler(int signum) {
	// ctrl+c
	if (signum == 2) {
		std::cout << "\nSIG (" << signum << ") shutingdown gracefully at "
				  << util_helper::timestamp() << "\n";
		_producer_is_running = false;
	}
}

// --------------------------------------------------------- //

int main(int argc, char *argv[]) {
	std::signal(SIGINT, signal_handler);

	// --------------------------------------------------------- //

	cppkafka::Configuration config = {
		{"metadata.broker.list", "127.0.0.1:9092"},
	};

	cppkafka::Producer producer(config);

	// --------------------------------------------------------- //

	ProducerEngine *p_engine = new ProducerEngine(new std::vector<StockTrade_t*>{
		new StockTrade_t {
			.stock = 300'000.00,
			.currency = "USD",
			.last_updated = util_helper::timestamp(),
			.id = "BIZ1"
		},
		new StockTrade_t {
			.stock = 400'000.00,
			.currency = "USD",
			.last_updated = util_helper::timestamp(),
			.id = "BIZ2"
		},
		new StockTrade_t {
			.stock = 500'000.00,
			.currency = "USD",
			.last_updated = util_helper::timestamp(),
			.id = "BIZ3"
		}
	});

	while (_producer_is_running) {
		p_engine->_start_runtime();

		const std::string payload = p_engine->get_trade_data_as_string();

		producer.produce(
			cppkafka::MessageBuilder(DGKAFKA_STOCK_TRADE_TOPIC)
				.partition(0)
				.payload(payload)
		);

		producer.flush();
	}

	if (p_engine) { delete p_engine; }

    return 0;
}

