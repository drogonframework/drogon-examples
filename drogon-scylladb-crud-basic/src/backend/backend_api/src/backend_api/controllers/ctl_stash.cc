#include "ctl_stash.h"

namespace backend_api
{

CtlStash::CtlStash()
{
}

CtlStash::~CtlStash()
{
}

void CtlStash::createNewStash(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback, const std::string &idAccount)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool idAccountPassed = false, stashNamePassed = false;

    Json::Value json, body, data;

    internalcpp::UtilityModule Utility;

    drogon_scylladb_crud_basic::Account Account;
    drogon_scylladb_crud_basic::Stash Stash;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    body = Utility.JsonHelper.fromString(std::string(pReq->getBody()));

    auto stashName = body["stash_name"].asString();

    if (idAccount.length() >= 1)
    {
        switch (Account.readExistingId(idAccount))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                idAccountPassed = true;
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "can't find id account";
            }
            break;

            default:
            {
                okMessage.message = "error while checking id, try again later";
            }
            break;
        }
    }

    if (idAccountPassed)
    {
        if (stashName.length() >= 4)
        {
            switch (Stash.createNewData(idAccount, stashName))
            {
                case internalcpp::EResultStatus::Enum::RESULT_STATUS_OK:
                {
                    okMessage.ok = true;
                    okMessage.message = "stash created";
                }
                break;

                case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
                {
                    okMessage.message = "this stash name already exists for you";
                }
                break;

                default:
                {
                    okMessage.message = "can't create stash for now, try again later";
                }
                break;
            }
        }
        else
        {
            okMessage.message = "stash name required at least 4 characters";
        }
    }

    json["ok"] = okMessage.ok;
    json["message"] = okMessage.message;
    json["data"] = data;

    pResp = drogon::HttpResponse::newHttpJsonResponse(json);

    this->BeforeCallback.checkOriginIsFromWhitelist(ORIGIN_WHITELIST, pReq, pResp);

    fCallback(pResp);
}

void CtlStash::getAllStash(const drogon::HttpRequestPtr & pReq, std::function<void(const drogon::HttpResponsePtr&)>&& fCallback, const std::string & idAccount)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool idAccountPassed = false;

    Json::Value json, body, data;

    internalcpp::UtilityModule Utility;

    drogon_scylladb_crud_basic::Account Account;
    drogon_scylladb_crud_basic::Stash Stash;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    /*
    ## NOTE
    {
        data:
        {
            stash:
            [
                {
                    created_timestamp: "20240801 14:59:27",
                    id: "3cd46083-11b1-4514-84c8-76e84849f2f4",
                    stash_items:
                    [
                        "item1", "item2"
                    ],
                    stash_name: "stash1"

                },
                {
                    created_timestamp: "20240801 15:32:32",
                    id: "a874533e-8c1e-4b87-a27b-9226b6970e3d",
                    stash_items: null,
                    stash_name: "stash2"

                }
            ]
        },
        message: "",
        ok: true
    }
    */ 
    // 
    if (idAccount.length() >= 1)
    {
        switch (Account.readExistingId(idAccount))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                idAccountPassed = true;
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "can't find id account";
            }
            break;

            default:
            {
                okMessage.message = "error while checking id, try again later";
            }
            break;
        }
    }

    if (idAccountPassed)
    {
        Json::Value stashData;

        if (Stash.readAllStash(idAccount, stashData) == internalcpp::EResultStatus::Enum::RESULT_STATUS_OK)
        {
            okMessage.ok = true;
            okMessage.message = "";

            data = stashData;
        }
        else
        {
            stashData.nullSingleton();
            data = stashData;
        }
    }

    json["ok"] = okMessage.ok;
    json["message"] = okMessage.message;
    json["data"] = data;

    pResp = drogon::HttpResponse::newHttpJsonResponse(json);

    this->BeforeCallback.checkOriginIsFromWhitelist(ORIGIN_WHITELIST, pReq, pResp);

    fCallback(pResp);
}

void CtlStash::deleteStash(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback, const std::string &idAccount, const std::string &idStash)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool idAccountPassed = false, idStashPassed = false;

    Json::Value json, body, data;

    internalcpp::UtilityModule Utility;

    drogon_scylladb_crud_basic::Account Account;
    drogon_scylladb_crud_basic::Stash Stash;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    if (idAccount.length() >= 1)
    {
        switch (Account.readExistingId(idAccount))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                idAccountPassed = true;
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "can't find id account";
            }
            break;

            default:
            {
                okMessage.message = "error while checking id, try again later";
            }
            break;
        }
    }

    if (idAccountPassed)
    {
        switch (Stash.readExistingId(idStash))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                idStashPassed = true;
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "this stash proly consumed by black hole";
            }
            break;

            default:
            {
                okMessage.message = "couldn't check your stash, try again later";
            }
            break;
        }
    }

    if (idAccountPassed && idStashPassed)
    {
        switch (Stash.deleteExistingStash(idAccount, idStash))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_OK:
            {
                okMessage.ok = true;
                okMessage.message = "stash removed";
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_WARNING:
            {
                okMessage.message = "nothing todo";
            }
            break;


            default:
            {
                okMessage.message = "can't this stash, try again later";
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

void CtlStash::addItem(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback, const std::string &idAccount, const std::string &idStash)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool idAccountPassed = false, idStashPassed = false, itemNamePassed = false;

    Json::Value json, body, data;

    internalcpp::UtilityModule Utility;

    drogon_scylladb_crud_basic::Account Account;
    drogon_scylladb_crud_basic::Stash Stash;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    body = Utility.JsonHelper.fromString(std::string(pReq->getBody()));

    auto itemName = body["item_name"].asString();

    if (idAccount.length() >= 1)
    {
        switch (Account.readExistingId(idAccount))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                idAccountPassed = true;
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "can't find id account";
            }
            break;

            default:
            {
                okMessage.message = "error while checking id, try again later";
            }
            break;
        }
    }

    if (idAccountPassed)
    {
        switch (Stash.readExistingId(idStash))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                idStashPassed = true;
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "this stash proly consumed by black hole";
            }
            break;

            default:
            {
                okMessage.message = "couldn't check your stash, try again later";
            }
            break;
        }
    }

    // check itemName
    if (idAccountPassed && idStashPassed)
    {
        if (itemName.length() != 0)
        {
            itemNamePassed = true;
        }
        else
        {
            okMessage.message = "you want to put something in this stash, but ...";
        }
    }

    if (idAccountPassed && idStashPassed && itemNamePassed)
    {
        switch (Stash.createItemInsideStash(idAccount, idStash, itemName))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_OK:
            {
                okMessage.ok = true;
                okMessage.message = "adding item to this stash";
            }
            break;

            default:
            {
                okMessage.message = "can't add item to this stash, try again later";
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

void CtlStash::deleteItem(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback, const std::string &idAccount, const std::string &idStash)
{
    const auto ORIGIN_WHITELIST = drogon::app().getCustomConfig()["integration"]["security"]["origin_whitelist"];
    auto pResp = drogon::HttpResponse::newHttpResponse();

    bool idAccountPassed = false, idStashPassed = false, itemNamePassed = false;

    Json::Value json, body, data;

    internalcpp::UtilityModule Utility;

    drogon_scylladb_crud_basic::Account Account;
    drogon_scylladb_crud_basic::Stash Stash;

    internallcpp::TOkMessage okMessage = {false, "n/a"};

    body = Utility.JsonHelper.fromString(std::string(pReq->getBody()));

    auto itemName = body["item_name"].asString();

    if (idAccount.length() >= 1)
    {
        switch (Account.readExistingId(idAccount))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                idAccountPassed = true;
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "can't find id account";
            }
            break;

            default:
            {
                okMessage.message = "error while checking id, try again later";
            }
            break;
        }
    }

    if (idAccountPassed)
    {
        switch (Stash.readExistingId(idStash))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_EXISTS:
            {
                idStashPassed = true;
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "this stash proly consumed by black hole";
            }
            break;

            default:
            {
                okMessage.message = "couldn't check your stash, try again later";
            }
            break;
        }
    }

    // check itemName
    if (idAccountPassed && idStashPassed)
    {
        if (itemName.length() != 0)
        {
            itemNamePassed = true;
        }
        else
        {
            okMessage.message = "you want to delete something in this stash, but ...";
        }
    }

    if (idAccountPassed && idStashPassed && itemNamePassed)
    {
        switch (Stash.deleteItemInsideStash(idAccount, idStash, itemName))
        {
            case internalcpp::EResultStatus::Enum::RESULT_STATUS_OK:
            {
                okMessage.ok = true;
                okMessage.message = "item '" + itemName + "' deleted from this stash";
            }
            break;

            case internalcpp::EResultStatus::Enum::RESULT_STATUS_RESULT_NOT_EXISTS:
            {
                okMessage.message = "you are deleting what?!";
            }
            break;

            default:
            {
                okMessage.message = "can't delete item to this stash, try again later";
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
