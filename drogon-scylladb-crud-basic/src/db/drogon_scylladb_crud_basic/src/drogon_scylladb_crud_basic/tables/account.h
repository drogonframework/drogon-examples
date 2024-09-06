#ifndef DROGON_SCYLLADB_CRUD_BASIC_ACCOUNT_H
#define DROGON_SCYLLADB_CRUD_BASIC_ACCOUNT_H
#include <drogon_scylladb_crud_basic/interfaces/idrogon_scylladb.h>

#include <drogon_scylladb_crud_basic/types/account_types.h>

#include <internalcpp/enums/result_enums.h>

namespace drogon_scylladb_crud_basic
{

/**
 * @brief represent account table
 * 
 */
class Account final : public IDrogonScyllaDB
{
private:
    const std::string TABLE_NAME = "account";

    /*
    author: @prothegee
    last updated: 20240728
    */
    std::string TABLE_GENERATOR = R"(create table if not exists {KEYSPACE}.{TABLE_NAME}
(
    id                  uuid,
    email               text,
    created_timestamp   text,

    primary key (id)
);)";

public:
    Account(/* args */);
    ~Account();

    // represent current table columns key structure
    struct SCols
    {
        inline static const char *id = "id";
        inline static const char *email = "email";
        inline static const char *created_timestamp = "created_timestamp";
    };

    void initializeTable();
    void alterizeCurrentTable();

    /**
     * @brief create new data for account table
     * 
     * @note this is default to create
     * 
     * @param email 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum createNewData(const std::string &email);

    /**
     * @brief read existing id by using id
     * 
     * @param id 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum readExistingId(const std::string &id);

    /**
     * @brief read existing email from account table
     * 
     * @note if result is internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS it mean exists
     * 
     * @param email 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum readExistingEmail(const std::string &email);

    /**
     * @brief read existing id by using email
     * 
     * @param email 
     * @param idData object string to pass
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum readExistingIdByEmail(const std::string &email, std::string &idData);

    /**
     * @brief read data by using id
     * 
     * @param id 
     * @param accountData account data type object to pass
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum readDataById(const std::string &id, TAccount &accountData);

    /**
     * @brief update email by using id
     * 
     * @param id 
     * @param email 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum updateEmailById(const std::string &id, const std::string &email);

    /**
     * @brief delete data by using id and email
     * 
     * @param id 
     * @param email 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum deleteDataByIdAndEmail(const std::string &id, const std::string &email);
};

} // namespace drogon_scylladb_crud_basic

#endif // DROGON_SCYLLADB_CRUD_BASIC_ACCOUNT_H
