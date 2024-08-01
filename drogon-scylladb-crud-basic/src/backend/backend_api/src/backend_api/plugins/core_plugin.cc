#include "core_plugin.h"

namespace backend_api
{

void CorePlugin::initAndStart(const Json::Value &config)
{
    #if PROJECT_BUILD_TYPE != 5
    std::cout << "DEBUG: initializing backend_api::CorePlugin::initAndStart\n";
    #endif

    // project core db
    {
        drogon_scylladb_crud_basic::CoreDB CoreDb;
        CoreDb.initializeProjectKeyspace();
        CoreDb.initializeAndAlterizeProjectTables();
    }
}

void CorePlugin::shutdown()
{
}

CorePlugin::CorePlugin()
{
}

CorePlugin::~CorePlugin()
{
}

} // namespace backend_api
