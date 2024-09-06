#ifndef DROGON_SCYLLADB_CRUD_BASIC_STASH_TYPES_H
#define DROGON_SCYLLADB_CRUD_BASIC_STASH_TYPES_H
#include <string>
#include <vector>

namespace drogon_scylladb_crud_basic
{

/**
 * @brief represent stash type structure
 * 
 */
struct TStash
{
    std::string id = "";
    std::string id_account = "";
    std::string stash_name = "";
    std::vector<std::string> stash_items = {};
    std::string created_timestamp = "";
};

} // namespace drogon_scylladb_crud_basic

#endif // DROGON_SCYLLADB_CRUD_BASIC_STASH_TYPES_H
