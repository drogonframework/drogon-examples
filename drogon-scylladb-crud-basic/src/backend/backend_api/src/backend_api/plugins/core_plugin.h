#ifndef BACKEND_API_CORE_PLUGIN_H
#define BACKEND_API_CORE_PLUGIN_H
#include <drogon/drogon.h>

#include <internalcpp/base/config.h>

#include <drogon_scylladb_crud_basic/coredb.h>

namespace backend_api
{

/**
 * @brief backend_api core plugin
 * 
 * @note required to start first before any plugins
 */
class CorePlugin final : public drogon::Plugin<CorePlugin>
{
private:
    /* data */

protected:
    void initAndStart(const Json::Value &config);
    void shutdown();

public:
    CorePlugin(/* args */);
    ~CorePlugin();
};

} // namespace backend_api

#endif // BACKEND_API_CORE_PLUGIN_H
