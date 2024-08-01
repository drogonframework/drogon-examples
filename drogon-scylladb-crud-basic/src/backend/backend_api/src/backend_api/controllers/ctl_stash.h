#ifndef BACKEND_API_CTL_STASH_H
#define BACKEND_API_CTL_STASH_H
#include <drogon/drogon.h>

#include <internalcpp/interfaces/idrogon_controller_helper.h>

#include <internalcpp/modules/utility_module.h>

#include <internalcpp/types/ok_types.h>

#include <drogon_scylladb_crud_basic/tables/account.h>
#include <drogon_scylladb_crud_basic/tables/stash.h>

namespace backend_api
{

/**
 * @brief http controller class for stash implementation
 * 
 */
class CtlStash final : public drogon::HttpController<CtlStash>
                     , public internalcpp::IDrogonControllerHelper
{
private:
    /* data */

public:
    CtlStash(/* args */);
    ~CtlStash();

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CtlStash::createNewStash, "/api/stash/{idAccount}/new", drogon::Post);
    ADD_METHOD_TO(CtlStash::getAllStash, "/api/stash/{idAccount}/all", drogon::Get);
    ADD_METHOD_TO(CtlStash::deleteStash, "/api/stash/{idAccount}/{idStash}/delete", drogon::Delete);
    ADD_METHOD_TO(CtlStash::addItem, "/api/stash/{idAccount}/{idStash}/add/item", drogon::Patch);
    ADD_METHOD_TO(CtlStash::deleteItem, "/api/stash/{idAccount}/{idStash}/delete/item", drogon::Patch);
    METHOD_LIST_END

    void createNewStash(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback, const std::string &idAccount);
    void getAllStash(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback, const std::string &idAccount);
    void deleteStash(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback, const std::string &idAccount, const std::string &idStash);
    void addItem(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback, const std::string &idAccount, const std::string &idStash);
    void deleteItem(const drogon::HttpRequestPtr &pReq, std::function<void(const drogon::HttpResponsePtr &)> &&fCallback, const std::string &idAccount, const std::string &idStash);
};

} // namespace backend_api

#endif // BACKEND_API_CTL_STASH_H
