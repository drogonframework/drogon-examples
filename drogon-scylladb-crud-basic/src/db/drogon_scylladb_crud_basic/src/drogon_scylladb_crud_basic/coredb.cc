#include "coredb.h"

#include <drogon_scylladb_crud_basic/tables/account.h>
#include <drogon_scylladb_crud_basic/tables/stash.h>

namespace drogon_scylladb_crud_basic
{

CoreDB::CoreDB()
{
    initializeConstructor();
}

CoreDB::~CoreDB()
{
}

void CoreDB::initializeProjectKeyspace()
{
    std::string query = "";

    const auto KEYSPACE = getKeyspace();
    const auto TOPOLOGY_STRATEGY = [&]()
    {
        std::string result = "";

        switch (getStrategy())
        {
            case 1: { result = "SimpleStrategy"; } break;

            case 2: { result = "NetworkTopologyStrategy"; } break;

            case 3: { result = "LocalStrategy"; } break;

            case 4: { result = "EverywhereStrategy"; } break;

            default: { result = "undefined"; } break;
        }

        return result;
    }();

    switch (getStrategy())
    {
        case 3:
        {
            query = "create keyspace if not exists {KEYSPACE} with replication = { 'class': '{TOPOLOGY_STRATEGY}' };";

            drogon::utils::replaceAll(query, "{KEYSPACE}", KEYSPACE);
            drogon::utils::replaceAll(query, "{TOPOLOGY_STRATEGY}", TOPOLOGY_STRATEGY);
        }
        break;

        default:
        {
            drogon::app().getLoop()->runAfter(0, [&]()
            {
                std::cout << "ERROR CoreDB::initializeProjectKeyspace: topology strategy of \"" << TOPOLOGY_STRATEGY << "\" is not supported";
                drogon::app().quit();
            });
        }
        break;
    }

    executeQuery(getCassSessionPtr(), query.c_str());
}

void CoreDB::initializeAndAlterizeProjectTables()
{
    {
        Account table;
        table.initializeTable();
        table.alterizeCurrentTable();
    }
    {
        Stash table;
        table.initializeTable();
        table.alterizeCurrentTable();
    }
}

} // namespace drogon_scylladb_crud_basic
