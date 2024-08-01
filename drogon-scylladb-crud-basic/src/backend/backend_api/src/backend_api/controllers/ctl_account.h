#ifndef BACKEND_API_CTL_ACCOUNT_H
#define BACKEND_API_CTL_ACCOUNT_H
#include <drogon/drogon.h>

#include <internalcpp/interfaces/idrogon_controller_helper.h>

#include <internalcpp/modules/utility_module.h>

#include <internalcpp/types/ok_types.h>

#include <drogon_scylladb_crud_basic/tables/account.h>

namespace backend_api
{

/**
 * @brief http controller class for account implementation
 * 
 */
class CtlAccount final : public drogon::HttpController<CtlAccount>
                       , public internalcpp::IDrogonControllerHelper
{
private:
    /* data */

public:
    CtlAccount(/* args */);
    ~CtlAccount();

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CtlAccount::checkEmail, "/api/availability/email", drogon::Get);

    ADD_METHOD_TO(CtlAccount::checkAccount, "/api/account/data", drogon::Get);
    ADD_METHOD_TO(CtlAccount::updateAccount, "/api/account/update", drogon::Patch);
    ADD_METHOD_TO(CtlAccount::deleteAccount, "/api/account/delete", drogon::Delete);
    ADD_METHOD_TO(CtlAccount::createAccount, "/api/account/register", drogon::Post);
    METHOD_LIST_END

    void checkEmail(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback);

    void checkAccount(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback);
    void updateAccount(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback);
    void deleteAccount(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback);
    void createAccount(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback);
};

} // namespace backend_api

#endif // BACKEND_API_CTL_ACCOUNT_H
