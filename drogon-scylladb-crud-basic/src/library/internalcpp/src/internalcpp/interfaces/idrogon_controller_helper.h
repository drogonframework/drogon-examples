#ifndef INTERNALCPP_IDROGON_CONTROLLER_HELPER_H
#define INTERNALCPP_IDROGON_CONTROLLER_HELPER_H
#include <drogon/drogon.h>

namespace internalcpp
{

struct SHeader
{
    struct HTTP_HEADER_ALIASES
    {
        inline static const char *HOST = "host";
        inline static const char *ORIGIN = "origin";
        inline static const char *ACCESS_CONTROL_ALLOW_ORIGIN = "access-control-allow-origin";
    };
};

/**
 * @brief interface helper class for drogon controller
 * 
 */
class IDrogonControllerHelper
{
private:
    /* data */

public:
    virtual ~IDrogonControllerHelper();

    // drogon before callback structure
    struct SBeforeCallback
    {
        /**
         * @brief check if origin header is on whitelist
         * 
         * @note commonly use before callback for json page
         * 
         * @param originWhitelist 
         * @param pReq 
         * @param pResp 
         * @param force default is false, if true, object header will be added no matter what
         */
        void checkOriginIsFromWhitelist(const Json::Value &originWhitelist, const drogon::HttpRequestPtr &pReq, drogon::HttpResponsePtr &pResp, const bool &force = false);
    };
    // drogon before callback helper access
    SBeforeCallback BeforeCallback = SBeforeCallback();
};

} // namespace internalcpp

#endif // INTERNALCPP_IDROGON_CONTROLLER_HELPER_H
