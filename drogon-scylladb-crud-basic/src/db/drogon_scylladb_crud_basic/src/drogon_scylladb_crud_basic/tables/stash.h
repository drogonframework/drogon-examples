#ifndef DROGON_SCYLLADB_CRUD_BASIC_STASH_H
#define DROGON_SCYLLADB_CRUD_BASIC_STASH_H
#include <drogon_scylladb_crud_basic/interfaces/idrogon_scylladb.h>

#include <drogon_scylladb_crud_basic/types/stash_types.h>

#include <internalcpp/enums/result_enums.h>

namespace drogon_scylladb_crud_basic
{

/**
 * @brief represent stash table
 * 
 */
class Stash final : public IDrogonScyllaDB
{
private:
    const std::string TABLE_NAME = "stash";

    /*
    author: @prothegee
    last updated: 20240728
    */
    std::string TABLE_GENERATOR = R"(create table if not exists {KEYSPACE}.{TABLE_NAME}
(
    id                  uuid,
    id_account          uuid,
    stash_name          text,
    stash_items         list<text>,
    created_timestamp   text,

    primary key (id)
);)";

protected:
    /**
     * @brief get item index from stash_items
     * 
     * @note if value < 0 mean not found
     * 
     * @param id 
     * @param idAccount 
     * @param itemName 
     * @return int 
     */
    int getItemPositionFromStashItems(const std::string &id, const std::string &idAccount, const std::string &itemName);

public:
    Stash(/* args */);
    ~Stash();

    // represent current table columns key structure
    struct SCols
    {
        inline static const char *id = "id";
        inline static const char *id_account = "id_account";
        inline static const char *stash_name = "stash_name";
        inline static const char *stash_items = "stash_items";
        inline static const char *created_timestamp = "created_timestamp";
    };

    void initializeTable();
    void alterizeCurrentTable();

    /**
     * @brief create new data for stash table
     * 
     * @note this is only create a stash, not adding items
     * 
     * @param idAccount 
     * @param stashName 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum createNewData(const std::string &idAccount, const std::string &stashName);

    /**
     * @brief update an item to stash_items
     * 
     * @note ignoring null, it will append the items
     * 
     * @param idStash 
     * @param idAccount 
     * @param itemName item name to add, duplication is fine
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum createItemInsideStash(const std::string &idStash, const std::string &idAccount, const std::string &itemName);

    /**
     * @brief read existing id by using id
     * 
     * @param idStash 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum readExistingId(const std::string &idStash);

    /**
     * @brief read all stash data by id_account
     * 
     * @param idAccount 
     * @param stashData stashData to pass
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum readAllStash(const std::string &idAccount, Json::Value &stashData);

    /**
     * @brief read existing stash_name by id_account and stash_name
     * 
     * @param idAccount 
     * @param stashName 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum readExistingStashName(const std::string &idAccount, const std::string &stashName);

    /**
     * @brief delete existing stash
     * 
     * @note ignoring whether item_stash is not empty
     * 
     * @param idAccount 
     * @param idStash 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum deleteExistingStash(const std::string &idAccount, const std::string &idStash);

    /**
     * @brief delete an existing item inside stash_items
     * 
     * @param idAccount 
     * @param idStash 
     * @param itemName 
     * @return internalcpp::EResultStatus::Enum 
     */
    internalcpp::EResultStatus::Enum deleteItemInsideStash(const std::string &idAccount, const std::string &idStash, const std::string &itemName);
};

} // namespace drogon_scylladb_crud_basic

#endif // DROGON_SCYLLADB_CRUD_BASIC_STASH_H
