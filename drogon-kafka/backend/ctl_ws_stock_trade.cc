#include "ctl_ws_stock_trade.hh"
#include "plugin_drogon_kafka.hh"

#include <dgkafka/config.hh>
#include <dgkafka/util_helper.hh>
#include <cppkafka/cppkafka.h>

#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>

#define DEFAULT_TOPIC "ALL_STOCKS"

// --------------------------------------------------------- //

namespace {
    std::vector<drogon::WebSocketConnectionPtr> g_connections;
    std::mutex g_connections_mutex;
    std::atomic<bool> g_consumer_running{false};

    void start_consume() {
        if (g_consumer_running.exchange(true)) return;

        std::thread([]() {
            auto consumer = p_plguin_dgkafka->consumer();
            consumer.subscribe({DGKAFKA_STOCK_TRADE_TOPIC});

            while (g_consumer_running) {
                auto msg = consumer.poll(std::chrono::milliseconds(DGKAFKA_DELAY));

                if (msg && !msg.get_error()) {
                    std::string data = msg.get_payload();

                    std::vector<drogon::WebSocketConnectionPtr> connections_copy;
					{
                        std::lock_guard lock(g_connections_mutex);
                        connections_copy = g_connections;
                    }

					// broadcast/send payload in drogon main event loop
                    drogon::app().getLoop()->queueInLoop([connections_copy, data]() {
                        for (const auto& p_wsconn : connections_copy) {
                            if (p_wsconn->connected()) {
                                p_wsconn->send(data);
                            }
                        }
                    });
                }

				// connection checking
                {
                    std::lock_guard lock(g_connections_mutex);
                    if (g_connections.empty()) {
                        g_consumer_running = false;
                        break;
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(DGKAFKA_DELAY));
            }

            consumer.unsubscribe();
        }).detach();
    }
}

// --------------------------------------------------------- //

CtlWsStockTrade::CtlWsStockTrade() {}

void CtlWsStockTrade::handleNewMessage(const WebSocketConnectionPtr &p_wsconn,
									   std::string &&message,
									   const WebSocketMessageType &ws_msg_type) {
	// nothing todo
	// end-user don't do interactive feedback
	// they're just receive publish message from main event thread loop
}

void CtlWsStockTrade::handleNewConnection(const HttpRequestPtr &p_req,
                                          const WebSocketConnectionPtr &p_wsconn) {
    // you can do security check here before connection establish
	// you can check from request header or check some parameters

	printf("connection establish\n");

    {
        std::lock_guard lock(g_connections_mutex);
        g_connections.push_back(p_wsconn);

        if (!g_consumer_running) {
            start_consume();
        }
    }
}

void CtlWsStockTrade::handleConnectionClosed(const WebSocketConnectionPtr &p_wsconn) {
    printf("connection closed\n");

    std::lock_guard lock(g_connections_mutex);
    g_connections.erase(
        std::remove(g_connections.begin(), g_connections.end(), p_wsconn),
        g_connections.end()
    );
}
