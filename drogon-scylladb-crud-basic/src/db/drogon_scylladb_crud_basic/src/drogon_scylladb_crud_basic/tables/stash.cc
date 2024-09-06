#include "stash.h"

namespace drogon_scylladb_crud_basic
{

int Stash::getItemPositionFromStashItems(const std::string &id, const std::string &idAccount, const std::string &itemName)
{
    int result = -1;

    std::string query = "select stash_items from {KEYSPACE}.{TABLE_NAME} where id=? and id_account=? allow filtering;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 2;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // id
    cass_statement_bind_uuid(pStatement, 0, IHelper.stringToCassUuid(id));

    // id_account
    cass_statement_bind_uuid(pStatement, 1, IHelper.stringToCassUuid(idAccount));

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Stash::getItemPositionFromStashItems");
    }
    else
    {
        auto pResult = cass_future_get_result(pFuture);
        auto pRows = cass_iterator_from_result(pResult);

        if (cass_iterator_next(pRows))
        {
            auto pRow = cass_iterator_get_row(pRows);
            auto stashItems = cass_row_get_column_by_name(pRow, SCols::stash_items);

            auto count = -1;
            auto pItems = cass_iterator_from_collection(stashItems);
            while (cass_iterator_next(pItems))
            {
                count++;

                const char *item;size_t itemSize;
                if (cass_value_get_string(cass_iterator_get_value(pItems), &item, &itemSize) == CASS_OK)
                {
                    auto exactItem = std::string(item, itemSize);

                    if (exactItem == itemName)
                    {
                        result = count;
                        break;
                    }
                }
            }

            cass_iterator_free(pItems);
        }

        cass_result_free(pResult);
    }

    cass_statement_free(pStatement);
    cass_future_free(pFuture);

    return result;
}

Stash::Stash()
{
    initializeConstructor();
}

Stash::~Stash()
{
}

void Stash::initializeTable()
{
    drogon::utils::replaceAll(TABLE_GENERATOR, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(TABLE_GENERATOR, "{TABLE_NAME}", TABLE_NAME);

    executeQuery(getCassSessionPtr(), TABLE_GENERATOR.c_str());
}

void Stash::alterizeCurrentTable()
{
    // author: @prothegee
    // created date: YYYYMMDD
    // {
    //     std::string alterize = R"()"; // reserved
    // }
}

internalcpp::EResultStatus::Enum Stash::createNewData(const std::string &idAccount, const std::string &stashName)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    auto stashCheck = readExistingStashName(idAccount, stashName);

    if (stashCheck == internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS)
    {
        std::string query = "insert into {KEYSPACE}.{TABLE_NAME} (id, id_account, stash_name, created_timestamp) values (?, ?, ?, ?) if not exists;";

        drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
        drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        const size_t parametersCount = 4;

        auto pStatement = cass_statement_new(query.c_str(), parametersCount);

        // id
        cass_statement_bind_uuid(pStatement, 0, IHelper.generateUuidV4());

        // id_account
        cass_statement_bind_uuid(pStatement, 1, IHelper.stringToCassUuid(idAccount));

        // stash_name
        cass_statement_bind_string(pStatement, 2, stashName.c_str());

        // created_timestamp
        cass_statement_bind_string(pStatement, 3, trantor::Date::now().toFormattedString(false).c_str());

        auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
        cass_future_wait(pFuture);

        auto status = cass_future_error_code(pFuture);

        if (status != CASS_OK)
        {
            printError(pFuture, "Stash::createNewData");
        }
        else
        {
            result = internalcpp::EResultStatus::Enum::RESULT_STATUS_OK;
        }

        cass_statement_free(pStatement);
        cass_future_free(pFuture);
    }
    else
    {
        result = stashCheck;
    }

    return result;
}

internalcpp::EResultStatus::Enum Stash::createItemInsideStash(const std::string &idStash, const std::string &idAccount, const std::string &itemName)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = "update {KEYSPACE}.{TABLE_NAME} set stash_items=stash_items+[?] where id=? if id_account=?;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 3;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // itemName
    cass_statement_bind_string(pStatement, 0, itemName.c_str());

    // id
    cass_statement_bind_uuid(pStatement, 1, IHelper.stringToCassUuid(idStash));

    // id_account
    cass_statement_bind_uuid(pStatement, 2, IHelper.stringToCassUuid(idAccount));

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Stash::createItemInsideStash");
    }
    else
    {
        result = internalcpp::EResultStatus::Enum::RESULT_STATUS_OK;
    }

    cass_statement_free(pStatement);
    cass_future_free(pFuture);

    return result;
}

internalcpp::EResultStatus::Enum Stash::readExistingId(const std::string &idStash)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = "select * from {KEYSPACE}.{TABLE_NAME} where id=?;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 1;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // id
    cass_statement_bind_uuid(pStatement, 0, IHelper.stringToCassUuid(idStash));

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Account::readExistingId");
    }
    else
    {
        auto pResult = cass_future_get_result(pFuture);

        if (cass_result_row_count(pResult) != 0)
        {
            result = internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS;
        }
        else
        {
            result = internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS;
        }

        cass_result_free(pResult);
    }

    cass_statement_free(pStatement);
    cass_future_free(pFuture);

    return result;
}

internalcpp::EResultStatus::Enum Stash::readAllStash(const std::string &idAccount, Json::Value &stashData)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = "select id, stash_name, created_timestamp, stash_items from {KEYSPACE}.{TABLE_NAME} where id_account=? allow filtering;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 1;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // id_account
    cass_statement_bind_uuid(pStatement, 0, IHelper.stringToCassUuid(idAccount));

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Stash::readAllStash");
    }
    else
    {
        Json::Value root;

        auto pResult = cass_future_get_result(pFuture);
        auto pRows = cass_iterator_from_result(pResult);

        while (cass_iterator_next(pRows))
        {
            Json::Value base;

            auto pRow = cass_iterator_get_row(pRows);

            // id
            auto idRow = cass_row_get_column_by_name(pRow, SCols::id);
            CassUuid idRes;
            if (cass_value_get_uuid(idRow, &idRes) == CASS_OK)
            {
                base["id"] = IHelper.cassUuidToString(idRes);
            }

            // created_timestamp
            auto createdTimestampRow = cass_row_get_column_by_name(pRow, SCols::created_timestamp);
            const char *createdTimestamp;size_t createdTimestampSize;
            if (cass_value_get_string(createdTimestampRow, &createdTimestamp, &createdTimestampSize) == CASS_OK)
            {
                base["created_timestamp"] = std::string(createdTimestamp, createdTimestampSize);
            }

            // stash_name
            auto stashNameRow = cass_row_get_column_by_name(pRow, SCols::stash_name);
            const char *stashName;size_t stashNameSize;
            if (cass_value_get_string(stashNameRow, &stashName, &stashNameSize) == CASS_OK)
            {
                base["stash_name"] = std::string(stashName, stashNameSize);
            }

            // stash_items
            auto stashItemsRow = cass_row_get_column_by_name(pRow, SCols::stash_items);
            if (!cass_value_is_null(stashItemsRow))
            {
                auto pItems = cass_iterator_from_collection(stashItemsRow);
                while (cass_iterator_next(pItems))
                {
                    const char *item;size_t itemSize;
                    if (cass_value_get_string(cass_iterator_get_value(pItems), &item, &itemSize) == CASS_OK)
                    {
                        base["stas_items"].append(std::string(item, itemSize));
                    }
                    else
                    {
                        base["stas_items"].nullSingleton();
                    }
                }
                cass_iterator_free(pItems);
            }
            else
            {
                base["stas_items"].nullSingleton();
            }

            root["stash"].append(base);
        }

        stashData = root;

        result = internalcpp::EResultStatus::Enum::RESULT_STATUS_OK;

        cass_result_free(pResult);
        cass_iterator_free(pRows);
    }

    cass_statement_free(pStatement);
    cass_future_free(pFuture);

    return result;
}

internalcpp::EResultStatus::Enum Stash::readExistingStashName(const std::string &idAccount, const std::string &stashName)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = "select id, stash_name from {KEYSPACE}.{TABLE_NAME} where id_account=? and stash_name=? allow filtering;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 2;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // id_account
    cass_statement_bind_uuid(pStatement, 0, IHelper.stringToCassUuid(idAccount));

    // stash_name
    cass_statement_bind_string(pStatement, 1, stashName.c_str());

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Stash::readExistingStashName");
    }
    else
    {
        auto pResult = cass_future_get_result(pFuture);

        if (cass_result_row_count(pResult) != 0)
        {
            result = internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS;
        }
        else
        {
            result = internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS;
        }

        cass_result_free(pResult);
    }

    cass_statement_free(pStatement);
    cass_future_free(pFuture);

    return result;
}

internalcpp::EResultStatus::Enum Stash::deleteExistingStash(const std::string &idAccount, const std::string &idStash)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    auto existsStash = this->readExistingId(idStash);

    if (existsStash != internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS)
    {
        result = internalcpp::EResultStatus::Enum::RESULT_STATUS_WARNING;
    }
    else
    {
        std::string query = "delete from {KEYSPACE}.{TABLE_NAME} where id=? if id_account=?;";

        drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
        drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        const size_t parametersCount = 2;

        auto pStatement = cass_statement_new(query.c_str(), parametersCount);

        // id
        cass_statement_bind_uuid(pStatement, 0, IHelper.stringToCassUuid(idStash));

        // id_account
        cass_statement_bind_uuid(pStatement, 1, IHelper.stringToCassUuid(idAccount));

        auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
        cass_future_wait(pFuture);

        auto status = cass_future_error_code(pFuture);

        if (status != CASS_OK)
        {
            printError(pFuture, "Stash::deleteExistingStash");
        }
        else
        {
            result = internalcpp::EResultStatus::Enum::RESULT_STATUS_OK;
        }

        cass_statement_free(pStatement);
        cass_future_free(pFuture);
    }


    return result;
}

internalcpp::EResultStatus::Enum Stash::deleteItemInsideStash(const std::string &idAccount, const std::string &idStash, const std::string &itemName)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    auto indexPosition = this->getItemPositionFromStashItems(idStash, idAccount, itemName);

    if (indexPosition <= 0)
    {
        result = internalcpp::EResultStatus::RESULT_STATUS_RESULT_NOT_EXISTS;
    }
    else
    {
        std::string query = "delete stash_items[?] from {KEYSPACE}.{TABLE_NAME} where id=? if id_account=?;";

        drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
        drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        const size_t parametersCount = 3;

        auto pStatement = cass_statement_new(query.c_str(), parametersCount);

        // index
        cass_statement_bind_int32(pStatement, 0, indexPosition);

        // id
        cass_statement_bind_uuid(pStatement, 1, IHelper.stringToCassUuid(idStash));

        // id_account
        cass_statement_bind_uuid(pStatement, 2, IHelper.stringToCassUuid(idAccount));

        auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
        cass_future_wait(pFuture);

        auto status = cass_future_error_code(pFuture);

        if (status != CASS_OK)
        {
            printError(pFuture, "Stash::deleteItemInsideStash");
        }
        else
        {
            result = internalcpp::EResultStatus::Enum::RESULT_STATUS_OK;
        }

        cass_statement_free(pStatement);
        cass_future_free(pFuture);
    }

    return result;
}

} // namespace drogon_scylladb_crud_basic
