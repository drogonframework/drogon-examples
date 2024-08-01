#ifndef DROGON_SCYLLADB_CRUD_BASIC_AUTH_TYPES_H
#define DROGON_SCYLLADB_CRUD_BASIC_AUTH_TYPES_H

namespace drogon_scylladb_crud_basic
{

/**
 * @brief scylladb auth credential type for connection
 * 
 */
struct TAuthCredential
{
    const char *username;
    const char *password;
};

/**
 * @brief scylladb auth connection type for connection
 * 
 */
struct TAuthConnection
{
    // 0:undefined 1:AllowAllAuthenticator 2:PasswordAuthenticator 3:com.scylladb.auth.TransitionalAuthenticator
    int auth;
    const char *hosts;
    const char *username;
    const char *password;
};

} // namespace drogon_scylladb_crud_basic

#endif // DROGON_SCYLLADB_CRUD_BASIC_AUTH_TYPES_H
