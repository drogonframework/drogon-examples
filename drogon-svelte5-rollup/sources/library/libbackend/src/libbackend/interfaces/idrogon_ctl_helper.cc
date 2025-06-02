#include "idrogon_ctl_helper.hh"

#include <libbackend/constants/header_const.hh>
#include <libbackend/functions/utility_functions.hh>

namespace libbackend {

void IDrogonCtlHelper::_IFrontendBundle::addJs(const std::string& bundleName, HttpViewData& viewData, const int& scriptMode) {
    std::string bundle;

    switch (scriptMode) {
    case 0: {
        bundle += "<script src=\"";
    } break;
    case 1: {
        bundle += "<script type=\"module\" src=\"";
    } break;
    case 2: {
        bundle += "<script defer type=\"module\" src=\"";
    } break;
    case 3: {
        bundle += "<script async type=\"module\" src=\"";
    } break;
    default: {
        bundle += "<script async type=\"module\" src=\"";
    } break;
    }

    bundle += bundleName;
    bundle += ".js";
    bundle += "\"></script>";

    viewData.insert("{BUNDLE_JS}", bundle);
}

void IDrogonCtlHelper::_IFrontendBundle::addCss(const std::string& bundleName, HttpViewData& viewData) {
    std::string bundle;

    bundle += "<link rel=\"stylesheet\" href=\"";
    bundle += bundleName;
    bundle += ".css";
    bundle += "\">";

    viewData.insert("{BUNDLE_CSS}", bundle);
}

// ------------------------------------------------------ //

void IDrogonCtlHelper::_IInvokeMeta::language(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{LANGUAGE}", input);
}

void IDrogonCtlHelper::_IInvokeMeta::robot(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{ROBOTS}", input);
}

void IDrogonCtlHelper::_IInvokeMeta::title(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{TITLE}", input);
}

void IDrogonCtlHelper::_IInvokeMeta::keywords(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{KEYWORDS}", input);
}

void IDrogonCtlHelper::_IInvokeMeta::about(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{ABOUT}", input);
}

void IDrogonCtlHelper::_IInvokeMeta::description(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{DESCRIPTION}", input);
}

void IDrogonCtlHelper::_IInvokeMeta::url(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{URL}", input);
}

void IDrogonCtlHelper::_IInvokeMeta::copyright(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{COPYRIGHT}", input);
}

void IDrogonCtlHelper::_IInvokeMeta::image(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{IMAGE}", input);
}

void IDrogonCtlHelper::_IInvokeMeta::video(const std::string& input, HttpViewData& viewData) {
    viewData.insert("{VIDEO}", input);
}

// ------------------------------------------------------ //

bool IDrogonCtlHelper::_IBeforeCallback::acceptedLanguage(const Json::Value& supportedLanguages, const std::string& defaultLanguage, std::string& languageToCheck) {
    bool languageAccepted = false;

    for (auto& language : supportedLanguages) {
        if (languageToCheck == language.asString()) {
            languageAccepted = true;
            break;
        }
    }

    if (!languageAccepted) {
        languageToCheck = defaultLanguage;
    }

    return languageAccepted;
}

// ------------------------------------------------------ //

void IDrogonCtlHelper::_ISessionControl::initialize(const HttpRequestPtr &pReq, HttpViewData &viewData) {
    const Json::Value CONFIG_PROJECT = utility_functions::jsoncpp::fromJsonFile("../.config/config.project.json");
    const std::string DEFAULT_USERNAME = CONFIG_PROJECT["default"]["non_signin_username"].asString();

    auto is_signin = pReq->session()->get<bool>(ENDUSER::SESSION_KEY_HINT::IS_SIGN_IN);
    auto username = pReq->session()->get<std::string>(ENDUSER::SESSION_KEY_HINT::USERNAME);

    if (is_signin) {
        viewData.insert("{USERNAME}", username);
    } else {
        viewData.insert("{USERNAME}", DEFAULT_USERNAME);
    }
}

void IDrogonCtlHelper::_ISessionControl::setIsSignIn(const HttpRequestPtr &pReq, const bool &value)
{
    pReq->session()->insert(ENDUSER::SESSION_KEY_HINT::IS_SIGN_IN, value);
}

bool IDrogonCtlHelper::_ISessionControl::getIsSignIn(const HttpRequestPtr& pReq) {
    return pReq->session()->get<bool>(ENDUSER::SESSION_KEY_HINT::IS_SIGN_IN);
}

void IDrogonCtlHelper::_ISessionControl::setUsername(const HttpRequestPtr& pReq, const std::string& value) {
    pReq->session()->insert(ENDUSER::SESSION_KEY_HINT::USERNAME, value);
}

std::string IDrogonCtlHelper::_ISessionControl::getUsername(const HttpRequestPtr& pReq) {
    return pReq->session()->get<std::string>(ENDUSER::SESSION_KEY_HINT::USERNAME);
}

} // namespace libbackend
