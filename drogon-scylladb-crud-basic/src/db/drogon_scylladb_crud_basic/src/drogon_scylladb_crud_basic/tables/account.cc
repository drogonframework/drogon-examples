#include "account.h"

namespace drogon_scylladb_crud_basic
{

Account::Account()
{
    initializeConstructor();
}

Account::~Account()
{
}

void Account::initializeTable()
{
    drogon::utils::replaceAll(TABLE_GENERATOR, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(TABLE_GENERATOR, "{TABLE_NAME}", TABLE_NAME);

    executeQuery(getCassSessionPtr(), TABLE_GENERATOR.c_str());
}

void Account::alterizeCurrentTable()
{
    // author: @prothegee
    // created date: YYYYMMDD
    // {
    //     std::string alterize = R"()"; // reserved
    // }
}

internalcpp::EResultStatus::Enum Account::createNewData(const std::string &email)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = R"(insert into {KEYSPACE}.{TABLE_NAME} (id, email, created_timestamp) values (?, ?, ?) if not exists;)";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 3;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // id
    cass_statement_bind_uuid(pStatement, 0, IHelper.generateUuidV4());

    // email
    cass_statement_bind_string(pStatement, 1, email.c_str());

    // created_timestamp
    cass_statement_bind_string(pStatement, 2, trantor::Date::now().toFormattedString(false).c_str());

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Account::createNewData");
    }
    else
    {
        result = internalcpp::EResultStatus::Enum::RESULT_STATUS_OK;
    }

    cass_statement_free(pStatement);
    cass_future_free(pFuture);

    return result;
}

internalcpp::EResultStatus::Enum Account::readExistingId(const std::string &id)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = "select * from {KEYSPACE}.{TABLE_NAME} where id=?;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 1;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // id
    cass_statement_bind_uuid(pStatement, 0, IHelper.stringToCassUuid(id));

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

internalcpp::EResultStatus::Enum Account::readExistingEmail(const std::string &email)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = "select * from {KEYSPACE}.{TABLE_NAME} where email=? allow filtering;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 1;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // email
    cass_statement_bind_string(pStatement, 0, email.c_str());

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Account::readExistingEmail");
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

internalcpp::EResultStatus::Enum Account::readExistingIdByEmail(const std::string &email, std::string &idData)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = "select id from {KEYSPACE}.{TABLE_NAME} where email=? allow filtering;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 1;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // email
    cass_statement_bind_string(pStatement, 0, email.c_str());

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Account::readExistingIdByEmail");
    }
    else
    {
        auto pResult = cass_future_get_result(pFuture);

        if (cass_result_row_count(pResult) != 0)
        {
            result = internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS;

            if (auto pFirstRow =cass_result_first_row(pResult))
            {
                // id
                auto idCol = cass_row_get_column_by_name(pFirstRow, SCols::id);
                CassUuid id;
                if (cass_value_get_uuid(idCol, &id) == CASS_OK)
                {
                    idData = IHelper.cassUuidToString(id);
                }
            }
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

internalcpp::EResultStatus::Enum Account::readDataById(const std::string &id, TAccount &accountData)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = "select * from {KEYSPACE}.{TABLE_NAME} where id=?;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 1;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // id
    cass_statement_bind_uuid(pStatement, 0, IHelper.stringToCassUuid(id));

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Account::readDataById");
    }
    else
    {
        result = internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS;

        auto pResult = cass_future_get_result(pFuture);
        auto pFirstRow = cass_result_first_row(pResult);

        if (pFirstRow)
        {
            // id
            auto idCol = cass_row_get_column_by_name(pFirstRow, SCols::id);
            CassUuid id;
            if (cass_value_get_uuid(idCol, &id) == CASS_OK)
            {
                accountData.id = IHelper.cassUuidToString(id);
            }

            // email
            auto emailCol = cass_row_get_column_by_name(pFirstRow, SCols::email);
            const char *emailVal;size_t emailValSize;
            if (cass_value_get_string(emailCol, &emailVal, &emailValSize) == CASS_OK)
            {
                accountData.email = std::string(emailVal, emailValSize);
            }

            // created_timestamp
            auto createdTimeStampCol = cass_row_get_column_by_name(pFirstRow, SCols::created_timestamp);
            const char *createdTimeStampVal;size_t createdTimeStampValSize;
            if (cass_value_get_string(createdTimeStampCol, &createdTimeStampVal, &createdTimeStampValSize) == CASS_OK)
            {
                accountData.created_timestamp = std::string(createdTimeStampVal, createdTimeStampValSize);
            }

            result = internalcpp::EResultStatus::Enum::RESULT_STATUS_OK;
        }

        cass_result_free(pResult);
    }

    cass_statement_free(pStatement);
    cass_future_free(pFuture);

    return result;
}

internalcpp::EResultStatus::Enum Account::updateEmailById(const std::string &id, const std::string &email)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    std::string query = "update {KEYSPACE}.{TABLE_NAME} set email=? where id=?;";

    drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
    drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

    const size_t parametersCount = 2;

    auto pStatement = cass_statement_new(query.c_str(), parametersCount);

    // id
    cass_statement_bind_uuid(pStatement, 0, IHelper.stringToCassUuid(id));

    // email
    cass_statement_bind_string(pStatement, 1, email.c_str());

    auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
    cass_future_wait(pFuture);

    auto status = cass_future_error_code(pFuture);

    if (status != CASS_OK)
    {
        printError(pFuture, "Account::updateEmailById");
    }
    else
    {
        result = internalcpp::EResultStatus::Enum::RESULT_STATUS_OK;
    }

    cass_statement_free(pStatement);
    cass_future_free(pFuture);

    return internalcpp::EResultStatus::Enum();
}

internalcpp::EResultStatus::Enum Account::deleteDataByIdAndEmail(const std::string &id, const std::string &email)
{
    internalcpp::EResultStatus::Enum result = internalcpp::EResultStatus::Enum::RESULT_STATUS_ERROR;

    auto existsAccount = this->readExistingEmail(email);

    if (existsAccount != internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS)
    {
        result = internalcpp::EResultStatus::Enum::RESULT_STATUS_WARNING;
    }
    else
    {
        std::string query = "delete from {KEYSPACE}.{TABLE_NAME} where id=? if email=?;";

        drogon::utils::replaceAll(query, "{KEYSPACE}", getKeyspace());
        drogon::utils::replaceAll(query, "{TABLE_NAME}", TABLE_NAME);

        const size_t parametersCount = 2;

        auto pStatement = cass_statement_new(query.c_str(), parametersCount);

        // id
        cass_statement_bind_uuid(pStatement, 0, IHelper.stringToCassUuid(id));

        // email
        cass_statement_bind_string(pStatement, 1, email.c_str());

        auto pFuture = cass_session_execute(getCassSessionPtr(), pStatement);
        cass_future_wait(pFuture);

        auto status = cass_future_error_code(pFuture);

        if (status != CASS_OK)
        {
            printError(pFuture, "Account::deleteDataByIdAndEmail");
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
