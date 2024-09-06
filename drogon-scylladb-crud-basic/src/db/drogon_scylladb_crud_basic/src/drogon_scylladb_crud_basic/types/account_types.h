#ifndef DROGON_SCYLLADB_CRUD_BASIC_ACCOUNT_TYPES_H
#define DROGON_SCYLLADB_CRUD_BASIC_ACCOUNT_TYPES_H
#include <string>

namespace drogon_scylladb_crud_basic
{

/**
 * @brief represent account type structure
 * 
 */
struct TAccount
{
    std::string id = "";
    std::string email = "";
    // std::string password_salt = "";
    // std::string password_input = "";
    std::string created_timestamp = "";
};

} // namespace drogon_scylladb_crud_basic

#endif // DROGON_SCYLLADB_CRUD_BASIC_ACCOUNT_TYPES_H
