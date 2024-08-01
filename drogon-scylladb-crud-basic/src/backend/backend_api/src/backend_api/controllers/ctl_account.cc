#include "ctl_account.h"

namespace backend_api
{

CtlAccount::CtlAccount()
{
}

CtlAccount::~CtlAccount()
{
}

void CtlAccount::checkEmail(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool emailPassed = false;

    Json::Value json, data;

    drogon_scylladb_crud_basic::Account Account;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    auto email = pReq->getParameter("q");

    if (email.length() != 0)
    {
        int emailCountCheck = 0;

        for (auto i = 0; i < email.length(); i++)
        {
            const std::string check = "@.";

            if (email[i] == check[0])
            {
                emailCountCheck += 1;
            }
            if (email[i] == check[1])
            {
                emailCountCheck += 1;
            }
        }

        if (emailCountCheck == 2)
        {
            emailPassed = true;
        }
        else
        {
            okMessage.message = "email format is wrong";
        }
    }
    else
    {
        okMessage.message = "ignored";
    }

    if (emailPassed)
    {
        auto emailStatus = Account.readExistingEmail(email);

        switch (emailStatus)
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.ok = true;
                okMessage.message = "this email isn't registered";
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                okMessage.message = "this email already registered";
            }
            break;

            default:
            {
                okMessage.message = "error while checking email";
            }
            break;
        }
    }

    json["ok"] = okMessage.ok;
    json["message"] = okMessage.message;
    json["data"] = data;

    pResp = drogon::HttpResponse::newHttpJsonResponse(json);

    this->BeforeCallback.checkOriginIsFromWhitelist(ORIGIN_WHITELIST, pReq, pResp);

    fCallback(pResp);
}

void CtlAccount::checkAccount(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool idPassed = false;

    std::string idResult;

    Json::Value json, data;

    drogon_scylladb_crud_basic::Account Account;
    drogon_scylladb_crud_basic::TAccount accountData;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    if (pReq->getHeader("authorization").length() != 0)
    {
        auto BEARER_KEY = pReq->getHeader("authorization");

        drogon::utils::replaceAll(BEARER_KEY, "Bearer ", "");

        idResult = drogon::utils::base64Decode(BEARER_KEY);

        drogon::utils::replaceAll(idResult, ":", "");

        idPassed = true;
    }

    if (idPassed)
    {
        auto dataStatus = Account.readDataById(idResult, accountData);

        switch (dataStatus)
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_OK:
            {
                data["account"]["id"] = accountData.id;
                data["account"]["email"] = accountData.email;
                data["account"]["created_timestamp"] = accountData.created_timestamp;

                okMessage.ok = true;
                okMessage.message = "";
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "data doesn't exists";
            }
            break;

            default:
            {
                okMessage.message = "can't find data from id";
            }
            break;
        }
    }
    else
    {
        okMessage.message = "not authorized";
    }

    json["ok"] = okMessage.ok;
    json["message"] = okMessage.message;
    json["data"] = data;

    pResp = drogon::HttpResponse::newHttpJsonResponse(json);

    this->BeforeCallback.checkOriginIsFromWhitelist(ORIGIN_WHITELIST, pReq, pResp);

    fCallback(pResp);
}

void CtlAccount::updateAccount(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool idPassed = false, emailPassed = false;

    Json::Value json, body, data;

    internalcpp::UtilityModule Utility;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    drogon_scylladb_crud_basic::TAccount accountData;

    drogon_scylladb_crud_basic::Account Account;

    body = Utility.JsonHelper.fromString(std::string(pReq->getBody()));

    auto id = body["id"].asString();
    auto email = body["email"].asString();

    if (id.length() != 0)
    {
        idPassed = true;
    }
    else
    {
        okMessage.message = "required id";
    }

    if (idPassed && email.length() != 0)
    {
        auto accountStatus = Account.readDataById(id, accountData);

        if (accountStatus == internalcpp::EResultStatus::Enum::RESULT_STATUS_OK)
        {
            if (email == accountData.email)
            {
                okMessage.message = "nothing change";
            }
            else
            {
                emailPassed = true;
            }
        }
        else
        {
            okMessage.message = "can't request to read data, try again later";
        }
    }
    else
    {
        okMessage.message = "email is required";
    }

    if (idPassed && emailPassed)
    {
        auto updateStatus = Account.updateEmailById(id, email);

        switch (updateStatus)
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_OK:
            {
                okMessage.ok = true;
                okMessage.message = "email has been updated";
            }
            break;

            default:
            {
                okMessage.message = "can't update email by id, try again later";
            }
            break;
        }
    }

    json["ok"] = okMessage.ok;
    json["message"] = okMessage.message;
    json["data"] = data;

    pResp = drogon::HttpResponse::newHttpJsonResponse(json);

    this->BeforeCallback.checkOriginIsFromWhitelist(ORIGIN_WHITELIST, pReq, pResp);

    fCallback(pResp);
}

void CtlAccount::deleteAccount(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool idPassed = false, emailPassed = false;

    Json::Value json, body, data;

    internalcpp::UtilityModule Utility;

    drogon_scylladb_crud_basic::Account Account;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    body = Utility.JsonHelper.fromString(std::string(pReq->getBody()));

    auto id = body["id"].asString();
    auto email = body["email"].asString();

    if (id.length() != 0)
    {
        idPassed = true;
    }
    else
    {
        okMessage.message = "required id";
    }

    if (idPassed && email.length() != 0)
    {
        emailPassed = true;
    }
    else
    {
        okMessage.message = "email is required";
    }

    if (idPassed && emailPassed)
    {
        auto deleteStatus = Account.deleteDataByIdAndEmail(id, email);

        switch (deleteStatus)
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_OK:
            {
                okMessage.ok = true;
                okMessage.message = "account has been removed";
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_WARNING:
            {
                okMessage.message = "nothing todo";
            }
            break;


            default:
            {
                okMessage.message = "error, try again later";
            }
            break;
        }
    }

    json["ok"] = okMessage.ok;
    json["message"] = okMessage.message;
    json["data"] = data;

    pResp = drogon::HttpResponse::newHttpJsonResponse(json);

    this->BeforeCallback.checkOriginIsFromWhitelist(ORIGIN_WHITELIST, pReq, pResp);

    fCallback(pResp);
}

void CtlAccount::createAccount(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool emailPassed = false, emailExistPassed = false;

    Json::Value json, body, data;

    internalcpp::UtilityModule Utility;

    drogon_scylladb_crud_basic::Account Account;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    body = Utility.JsonHelper.fromString(std::string(pReq->getBody()));

    auto email = body["email"].asString();

    if (email.length() != 0)
    {
        int emailCountCheck = 0;

        for (auto i = 0; i < email.length(); i++)
        {
            const std::string check = "@.";

            if (email[i] == check[0])
            {
                emailCountCheck += 1;
            }
            if (email[i] == check[1])
            {
                emailCountCheck += 1;
            }
        }

        if (emailCountCheck == 2)
        {
            emailPassed = true;
        }
        else
        {
            okMessage.message = "email format is wrong";
        }
    }
    else
    {
        okMessage.message = "ignored, email can't be empty";
    }

    if (emailPassed)
    {
        auto emailStatus = Account.readExistingEmail(email);

        switch (emailStatus)
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                emailExistPassed = true;
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                okMessage.message = "can't register this email";
            }
            break;

            default:
            {
                okMessage.message = "error while registering email";
            }
            break;
        }
    }

    if (emailPassed && emailExistPassed)
    {
        drogon_scylladb_crud_basic::Account Account;

        auto statusRegistration = Account.createNewData(email);

        switch (statusRegistration)
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_OK:
            {
                std::string idData;

                okMessage.ok = true;
                okMessage.message = "";

                Account.readExistingIdByEmail(email, idData);

                data["id"] = idData;
            }
            break;

            default:
            {
                okMessage.message = "something not right while creating account, try again later";
            }
            break;
        }
    }

    json["ok"] = okMessage.ok;
    json["message"] = okMessage.message;
    json["data"] = data;

    pResp = drogon::HttpResponse::newHttpJsonResponse(json);

    this->BeforeCallback.checkOriginIsFromWhitelist(ORIGIN_WHITELIST, pReq, pResp);

    fCallback(pResp);
}

} // namespace backend_api

