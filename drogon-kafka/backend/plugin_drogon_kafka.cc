#include "plugin_drogon_kafka.hh"

#define GRP_CONSUMER_1 "grp-consumer1"

// --------------------------------------------------------- //

PluginDrogonKafka::PluginDrogonKafka() {}

// --------------------------------------------------------- //

void PluginDrogonKafka::initAndStart(const Json::Value& config) {
    if (!p_plguin_dgkafka) { p_plguin_dgkafka = this; }

    // finally
    printf("PluginDrogonKafka initialized\n");
}

// --------------------------------------------------------- //

void PluginDrogonKafka::shutdown() {
    if (p_plguin_dgkafka) { delete p_plguin_dgkafka; }

    // finally
    printf("PluginDrogonKafka terminated\n");
}

// --------------------------------------------------------- //

cppkafka::Consumer PluginDrogonKafka::consumer() {
	return cppkafka::Consumer({
		{"metadata.broker.list", "127.0.0.1:9092"},
		{"group.id", GRP_CONSUMER_1}
	});
}

