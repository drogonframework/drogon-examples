#include "idrogon_scylladb.h"

namespace drogon_scylladb_crud_basic
{

IDrogonScyllaDB::~IDrogonScyllaDB()
{
}

int IDrogonScyllaDB::getStrategy()
{
    return m_strategy;
}

int IDrogonScyllaDB::getAuthMode()
{
    return m_authMode;
}

void IDrogonScyllaDB::onAuthInitialize(CassAuthenticator *pCassAuth, void *pVoidData)
{
    const auto CONNECTION = drogon::app().getCustomConfig()["integration"]["db"]["scylladb"]["connection"];

    const TAuthCredential *pCredential = (const TAuthCredential*)new TAuthCredential({
        CONNECTION["username"].asString().c_str(),
        CONNECTION["password"].asString().c_str()
    });

    size_t username_size = strlen(pCredential->username);
    size_t password_size = strlen(pCredential->password);
    size_t size = username_size + password_size + 2;

    char* response = cass_authenticator_response(pCassAuth, size);

    response[0] = '\0';
    memcpy(response + 1, pCredential->username, username_size);

    response[username_size + 1] = '\0';
    memcpy(response + username_size + 2, pCredential->password, password_size);

    delete pCredential;
}

void IDrogonScyllaDB::onAuthChallenge(CassAuthenticator *pCassAuth, void *pVoidData, const char *pToken, size_t tokenSize)
{
    /**
     * Not used for plain text authentication, but this is to be used for handling an authentication challenge initiated by the server
    */
}

void IDrogonScyllaDB::onAuthSuccess(CassAuthenticator *pCassAuth, void *pVoidData, const char *pToken, size_t tokenSize)
{
    /**
     * Not used for plain text authentication, but this is to be used for handling the success phase of an exchange
    */
}

void IDrogonScyllaDB::onAuthCleanup(CassAuthenticator *pCassAuth, void *pVoidData)
{
    /**
     * No resources cleanup is necessary for plain text authentication, but this is used to cleanup resources acquired during the authentication exchange
    */
}

void IDrogonScyllaDB::printError(CassFuture *pCassFuture, const char *info)
{
    const char* message;
    size_t message_length;

    cass_future_error_message(pCassFuture, &message, &message_length);

    fprintf(stderr, "ERROR \"%s\":\n%.*s\n", info, (int)message_length, message);
}

void IDrogonScyllaDB::initializeConstructor()
{
    auto const SCYLLADB_CONF = drogon::app().getCustomConfig()["integration"]["db"]["scylladb"];

    m_keyspace = SCYLLADB_CONF["keyspace"].asString();
    m_strategy = SCYLLADB_CONF["strategy"].asInt();
    m_replicationFactor = SCYLLADB_CONF["replication_factor"].asInt();

    if (m_pCassCluster == nullptr) { m_pCassCluster = cass_cluster_new(); }
    if (m_pCassSession == nullptr) { m_pCassSession = cass_session_new(); }

    TAuthConnection *pConnection = new TAuthConnection({
        SCYLLADB_CONF["connection"]["auth"].asInt(),
        SCYLLADB_CONF["connection"]["hosts"].asString().c_str(),
        SCYLLADB_CONF["connection"]["username"].asString().c_str(),
        SCYLLADB_CONF["connection"]["password"].asString().c_str()
    });

    TAuthCredential *pCredential = new TAuthCredential({
        pConnection->username,
        pConnection->password
    });

    CassAuthenticatorCallbacks authCallbacks = {onAuthInitialize, onAuthChallenge, onAuthSuccess, onAuthCleanup};

    switch (pConnection->auth)
    {
        /*
        author: @prothegee
        note: 
        - not really sure since scylladb v 6.0.x
        - this auth mode last time I used was below v 6.0.x
        - cloud services for scylladb is too pricy
        */
        case 1:
        {
            cass_cluster_set_contact_points(m_pCassCluster, pConnection->hosts);

            m_pCassFuture = cass_session_connect(m_pCassSession, m_pCassCluster);
        }
        break;

        case 2:
        {
            cass_cluster_set_contact_points(m_pCassCluster, pConnection->hosts);

            cass_cluster_set_authenticator_callbacks(m_pCassCluster, &authCallbacks, nullptr, pCredential);

            m_pCassFuture = cass_session_connect(m_pCassSession, m_pCassCluster);
        }
        break;

        default:
        {
            drogon::app().getLoop()->runAfter(0, [&]()
            {
                std::cerr << "ERROR: IDrogonScyllaDB::initializeConstructor core interface implementation for auth attempt is default and not implemented/supported\n";
                drogon::app().quit();
            });
        }
        break;
    }

    if (cass_future_error_code(m_pCassFuture) != CASS_OK)
    {
        drogon::app().getLoop()->runAfter(1, [&]()
        {
            printError(m_pCassFuture, "IDrogonScyllaDB::initializeConstructor");
            std::cerr << "ERROR: fail to make connection to database\n";
            drogon::app().quit();
        });
    }
}

std::string IDrogonScyllaDB::getKeyspace()
{
    if (m_keyspace.length() <= 0)
    {
        m_keyspace = drogon::app().getCustomConfig()["integration"]["db"]["scylladb"]["keyspace"].asString();
    }
    return m_keyspace;
}

CassUuid IDrogonScyllaDB::SHelper::stringToCassUuid(std::string &uuidStr)
{
    CassUuid result;

    char uuid[CASS_UUID_STRING_LENGTH];

    cass_uuid_from_string(uuidStr.c_str(), &result);

    cass_uuid_string(result, uuid);

    return result;
}

CassUuid IDrogonScyllaDB::SHelper::stringToCassUuid(const std::string &uuidStr)
{
    CassUuid result;

    char uuid[CASS_UUID_STRING_LENGTH];

    std::string _uuidStr = uuidStr;

    cass_uuid_from_string(_uuidStr.c_str(), &result);

    cass_uuid_string(result, uuid);

    return result;
}

std::string IDrogonScyllaDB::SHelper::cassUuidToString(CassUuid &uuidCass)
{
    std::string result;

    char uuid[CASS_UUID_STRING_LENGTH];

    cass_uuid_string(uuidCass, uuid);

    result = std::string(uuid);

    cass_uuid_from_string(std::string(uuid).c_str(), &uuidCass);

    return result;
}

std::string IDrogonScyllaDB::SHelper::cassUuidToString(const CassUuid &uuidCass)
{
    std::string result;
    CassUuid _uuidCass = uuidCass;

    char uuid[CASS_UUID_STRING_LENGTH];

    cass_uuid_string(_uuidCass, uuid);

    result = std::string(uuid);

    cass_uuid_from_string(std::string(uuid).c_str(), &_uuidCass);

    return result;
}

CassUuid IDrogonScyllaDB::SHelper::generateUuidV1()
{
    CassUuid uuid;

    CassUuidGen *pUuid_gen = cass_uuid_gen_new();

    cass_uuid_gen_time(pUuid_gen, &uuid);

    cass_uuid_gen_free(pUuid_gen);

    return uuid;
}

CassUuid IDrogonScyllaDB::SHelper::generateUuidV4()
{
    CassUuid uuid;

    CassUuidGen *pUuid_gen = cass_uuid_gen_new();

    cass_uuid_gen_random(pUuid_gen, &uuid);

    cass_uuid_gen_free(pUuid_gen);

    return uuid;
}

CassFuture *IDrogonScyllaDB::getCassFuturePtr()
{
    return m_pCassFuture;
}

CassCluster *IDrogonScyllaDB::getCassClusterPtr()
{
    return m_pCassCluster;
}

CassSession *IDrogonScyllaDB::getCassSessionPtr()
{
    return m_pCassSession;
}

CassError IDrogonScyllaDB::executeQuery(CassSession *pCassSession, const char *pQuery)
{
    CassError result = CASS_OK;
    CassFuture* pFuture = NULL;
    CassStatement* pStatement = cass_statement_new(pQuery, 0);

    pFuture = cass_session_execute(pCassSession, pStatement);
    cass_future_wait(pFuture);

    result = cass_future_error_code(pFuture);

    if (result != CASS_OK)
    {
        printError(pFuture, "");
    }

    cass_future_free(pFuture);
    cass_statement_free(pStatement);

    return result;
}

} // namespace drogon_scylladb_crud_basic
