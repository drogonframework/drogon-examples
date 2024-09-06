#include "idrogon_controller_helper.h"

namespace internalcpp
{

IDrogonControllerHelper::~IDrogonControllerHelper()
{
}

void IDrogonControllerHelper::SBeforeCallback::checkOriginIsFromWhitelist(const Json::Value &originWhitelist, const drogon::HttpRequestPtr &pReq, drogon::HttpResponsePtr &pResp, const bool &force)
{
    bool isOk = false;

    for (auto list : originWhitelist)
    {
        if (pReq->getHeader(SHeader::HTTP_HEADER_ALIASES::ORIGIN) == list.asString())
        {
            isOk = true;
            break;
        }
    }

    if (isOk || force)
    {
        pResp->addHeader(SHeader::HTTP_HEADER_ALIASES::ACCESS_CONTROL_ALLOW_ORIGIN, pReq->getHeader(SHeader::HTTP_HEADER_ALIASES::ORIGIN));
    }
}

} // namespace internalcpp
