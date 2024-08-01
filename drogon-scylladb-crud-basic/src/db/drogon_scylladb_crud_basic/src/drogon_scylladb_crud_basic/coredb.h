#ifndef DROGON_SCYLLADB_CRUD_BASIC_COREDB_H
#define DROGON_SCYLLADB_CRUD_BASIC_COREDB_H
#include <drogon_scylladb_crud_basic/interfaces/idrogon_scylladb.h>

namespace drogon_scylladb_crud_basic
{

/**
 * @brief represent coredb class for this project
 * 
 * @note mostly only to authorize database creation for drogon plugins
 */
class CoreDB final : public IDrogonScyllaDB
{
private:
    /* data */

public:
    CoreDB(/* args */);
    ~CoreDB();

    void initializeTable() { /* NOT IMPLEMENTED */ }
    void alterizeCurrentTable() { /* NOT IMPLEMENTED */ }

    void initializeProjectKeyspace();
    void initializeAndAlterizeProjectTables();
};

} // namespace drogon_scylladb_crud_basic

#endif // DROGON_SCYLLADB_CRUD_BASIC_COREDB_H
