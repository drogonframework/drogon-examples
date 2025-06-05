#ifndef BACKEND_WWW_COMMON_PAGES_HH
#define BACKEND_WWW_COMMON_PAGES_HH
#include <drogon/drogon.h>

#include <libbackend/interfaces/idrogon_ctl_helper.hh>

using namespace drogon;
using namespace libbackend;

namespace backend_www {

/**
 * @brief common pages controller class
 * 
 * @note most function handler using internal interface, see `idrogon_ctl_helper.hh`
 */
class CommonPages final : public HttpController<CommonPages>
                        , public IDrogonCtlHelper {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CommonPages::base, "/");
    ADD_METHOD_TO(CommonPages::home, "/{lang}/home", Get);
    ADD_METHOD_TO(CommonPages::signin, "/{lang}/sign-in");
    // 
    ADD_METHOD_TO(CommonPages::signout, "/{lang}/sign-out");
    ADD_METHOD_TO(CommonPages::secret, "/{lang}/secret");
    METHOD_LIST_END

    void base(const HttpRequestPtr& pReq, std::function<void(const HttpResponsePtr&)>&& callback);

    void home(const HttpRequestPtr& pReq, std::function<void(const HttpResponsePtr&)>&& callback, std::string&& lang);

    void signin(const HttpRequestPtr& pReq, std::function<void(const HttpResponsePtr&)>&& callback, std::string&& lang);
    // signup skipped
    void signout(const HttpRequestPtr& pReq, std::function<void(const HttpResponsePtr&)>&& callback);

    void secret(const HttpRequestPtr& pReq, std::function<void(const HttpResponsePtr&)>&& callback, std::string&& lang);
};

} // namespace backend_www

#endif // BACKEND_WWW_COMMON_PAGES_HH
