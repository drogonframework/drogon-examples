#ifndef PLUGIN_DROGON_KAFKA_HH
#define PLUGIN_DROGON_KAFKA_HH
#include <drogon/drogon.h>
#include <cppkafka/cppkafka.h>

/// @brief plugin drogon kafka
///
/// @note this object has global pointer named `pDgKafka`
/// !note could contain rdkafka object?
class PluginDrogonKafka : public drogon::Plugin<PluginDrogonKafka> {
	// tbd
public:
    PluginDrogonKafka();

    virtual void initAndStart(const Json::Value &config) override;
    virtual void shutdown() override;

	// --------------------------------------------------------- //

	// @note assume this is for /consume/stock/trade
	cppkafka::Consumer consumer();
}; // class PluginDrogonKafka

/// @brief global pointer for PluginDrogonKafka
///
/// @note do not delete this pointer on runtime
static PluginDrogonKafka* p_plguin_dgkafka = nullptr;

#endif // PLUGIN_DROGON_KAFKA_HH

