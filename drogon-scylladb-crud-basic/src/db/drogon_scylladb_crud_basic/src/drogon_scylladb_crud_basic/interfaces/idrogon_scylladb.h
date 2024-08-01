#ifndef DROGON_SCYLLADB_CRUD_BASIC_IDROGON_SCYLLADB_H
#define DROGON_SCYLLADB_CRUD_BASIC_IDROGON_SCYLLADB_H
#include <drogon/drogon.h>

#include <cassandra.h>

#include <drogon_scylladb_crud_basic/types/auth_types.h>

namespace drogon_scylladb_crud_basic
{

/**
 * @brief core interface for drogon scylladb
 * 
 */
class IDrogonScyllaDB
{
private:
    // 0:undefined 1:SimpleStrategy 2:NetworkTopologyStrategy 3:LocalStrategy 4:EverywhereStrategy
    int m_strategy;
    int m_authMode;
    int m_replicationFactor;

    std::string m_keyspace;

    CassFuture *m_pCassFuture = nullptr;

    CassCluster *m_pCassCluster = nullptr;

    CassSession *m_pCassSession = nullptr;

public:
    virtual ~IDrogonScyllaDB();

    /**
     * @brief get this project topology strategy
     * 
     * @note 0:undefined 1:SimpleStrategy 2:NetworkTopologyStrategy 3:LocalStrategy 4:EverywhereStrategy
     * 
     * @return int 
     */
    int getStrategy();

    /**
     * @brief get this project auth mode
     * 
     * @return int 
     */
    int getAuthMode();

    /**
     * @brief initialize table implementation
     * 
     */
    virtual void initializeTable() = 0;

    /**
     * @brief alterize current table implementation
     * 
     */
    virtual void alterizeCurrentTable() = 0;

#pragma region authenticator
    /**
     * @brief auth authenticator callback on initialize
     * 
     * @param pCassAuth 
     * @param pVoidData 
     */
    static void onAuthInitialize(CassAuthenticator *pCassAuth, void *pVoidData);

    /**
     * @brief auth authenticator callback on challenge
     * 
     * @param pCassAuth 
     * @param pVoidData 
     * @param pToken 
     * @param tokenSize 
     */
    static void onAuthChallenge(CassAuthenticator *pCassAuth, void *pVoidData, const char *pToken, size_t tokenSize);

    /**
     * @brief auth authenticator callback on success
     * 
     * @param pCassAuth 
     * @param pVoidData 
     * @param pToken 
     * @param tokenSize 
     */
    static void onAuthSuccess(CassAuthenticator *pCassAuth, void *pVoidData, const char *pToken, size_t tokenSize);

    /**
     * @brief auth authenticator callback on cleanup
     * 
     * @param pCassAuth 
     * @param pVoidData 
     */
    static void onAuthCleanup(CassAuthenticator *pCassAuth, void *pVoidData);
#pragma endregion

    /**
     * @brief drogon scylladb print error
     * 
     * @param pCassFuture 
     * @param info 
     */
    void printError(CassFuture *pCassFuture, const char *info = "");

    /**
     * @brief immediately initialize pointer/s for session & cluster
     * 
     * @note should be call in constructor before create or alter table implementation
     */
    void initializeConstructor();

    /**
     * @brief get this project keyspace
     * 
     * @return std::string 
     */
    std::string getKeyspace();

    // IDrogonScyllaDB helper structure
    struct SHelper
    {
        /**
         * @brief format string to a cass uuid
         * 
         * @param uuidStr 
         * @return CassUuid 
         */
        CassUuid stringToCassUuid(std::string &uuidStr);
        /**
         * @brief format string to a cass uuid
         * 
         * @param uuidStr 
         * @return CassUuid 
         */
        CassUuid stringToCassUuid(const std::string &uuidStr);
        
        /**
         * @brief format cass uuid to a string
         * 
         * @param uuidCass 
         * @return std::string 
         */
        std::string cassUuidToString(CassUuid &uuidCass);
        std::string cassUuidToString(const CassUuid &uuidCass);

        /**
         * @brief generate uuid v1
         * 
         * @return CassUuid 
         */
        CassUuid generateUuidV1();
        /**
         * @brief generate uuid v4
         * 
         * @return CassUuid 
         */
        CassUuid generateUuidV4();
    };
    // drogon scylladb helper interface access
    SHelper IHelper = SHelper();

    /**
     * @brief get CassFuture pointer
     * 
     * @return CassFuture* 
     */
    CassFuture *getCassFuturePtr();

    /**
     * @brief get CassCluster pointer
     * 
     * @return CassCluster* 
     */
    CassCluster *getCassClusterPtr();

    /**
     * @brief get CassSession pointer
     * 
     * @return CassSession* 
     */
    CassSession *getCassSessionPtr();

    /**
     * @brief execute cqlsh command
     * 
     * @param pCassSession 
     * @param pQuery 
     * @return CassError 
     */
    CassError executeQuery(CassSession *pCassSession, const char *pQuery);
};

} // namespace drogon_scylladb_crud_basic

#endif // DROGON_SCYLLADB_CRUD_BASIC_IDROGON_SCYLLADB_H
