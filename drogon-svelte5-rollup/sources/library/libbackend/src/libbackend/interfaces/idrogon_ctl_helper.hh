#ifndef LIBBACKEND_IDROGON_CTL_HELPER_HH
#define LIBBACKEND_IDROGON_CTL_HELPER_HH
#include <drogon/drogon.h>

#include <libbackend/constants/enduser_const.hh>

using namespace drogon;

namespace libbackend {

/**
 * @brief drogon controller helper interface structure
 */
struct IDrogonCtlHelper {
    virtual ~IDrogonCtlHelper() = default;

    // frontend bundle interface structure
    struct _IFrontendBundle {
        _IFrontendBundle() = default;
        ~_IFrontendBundle() = default;

        /**
         * @brief pass javascript bundle to .csp template
         *
         * @note do this before do any callback for the response
         *
         * @param bundleName
         * @param viewData
         * @param scriptMode 0:no_treatment 1:module 2:module_defer 3:module_async | default is 2
         */
        void addJs(const std::string& bundleName, HttpViewData& viewData, const int& scriptMode = 2);

        /**
         * @brief pass css bundle to .csp template
         *
         * @note do this before do any callback for the response
         *
         * @param bundleName
         * @param viewData
         */
        void addCss(const std::string& bundleName, HttpViewData& viewData);
    };
    // frontend bundle interface access
    _IFrontendBundle IFrontendBundle = _IFrontendBundle();

    // invoke meta interface structure
    struct _IInvokeMeta {
        _IInvokeMeta() = default;
        ~_IInvokeMeta() = default;

        // language meta
        // lookup: {LANGUAGE}
        void language(const std::string& input, HttpViewData& viewData);

        // robots meta
        // lookup: {ROBOTS}
        void robot(const std::string& input, HttpViewData& viewData);

        // title meta
        // lookup: {TITLE}
        void title(const std::string& input, HttpViewData& viewData);

        // keywords meta
        // lookup: {KEYWORDS}
        void keywords(const std::string& input, HttpViewData& viewData);

        // about meta
        // lookup: {ABOUT}
        void about(const std::string& input, HttpViewData& viewData);

        // description meta
        // lookup: {DESCRIPTION}
        void description(const std::string& input, HttpViewData& viewData);

        // url meta
        // lookup: {URL}
        void url(const std::string& input, HttpViewData& viewData);

        // copyright meta
        // lookup: {COPYRIGHT}
        void copyright(const std::string& input, HttpViewData& viewData);

        // image meta
        // lookup: {IMAGE}
        void image(const std::string& input, HttpViewData& viewData);

        // video meta
        // lookup: {VIDEO}
        void video(const std::string& input, HttpViewData& viewData);
    };
    // invoke meta interface access
    // use inside .csp file
    // if meta tag condition doesn't exists, it will skipp
    _IInvokeMeta IInvokeMeta = _IInvokeMeta();

    // before callback interface structure
    struct _IBeforeCallback {
        _IBeforeCallback() = default;
        ~_IBeforeCallback() = default;

        /**
         * @brief accepted language process
         * 
         * @note use to process some language param to check
         * 
         * @param supportedLanguages 
         * @param defaultLanguage 
         * @param languageToCheck 
         * @return true 
         * @return false 
         */
        bool acceptedLanguage(const Json::Value& supportedLanguages, const std::string& defaultLanguage, std::string& languageToCheck);
    };
    // before callback interface access
    _IBeforeCallback IBeforeCallback = _IBeforeCallback();

    // session control interface structure
    // NOTE:
    // - all session key already determined, look for enduser_const.hh for `SESSION_KEY_HINT`
    // - unless some manner meant to used with filter or middleware, use that instead
    struct _ISessionControl {
        _ISessionControl() = default;
        ~_ISessionControl() = default;

        /**
         * @brief initialize drogon session if allowed/exists
         * 
         * @note most of the time, this function called before any HttpViewData implementation & final callback
         * 
         * @param pReq 
         * @param viewData 
         */
        void initialize(const HttpRequestPtr& pReq, HttpViewData& viewData);

        void setIsSignIn(const HttpRequestPtr& pReq, const bool& value);
        bool getIsSignIn(const HttpRequestPtr& pReq);

        void        setUsername(const HttpRequestPtr& pReq, const std::string& value);
        std::string getUsername(const HttpRequestPtr& pReq);

        // what else?
    };
    // session control interface access
    // NOTE:
    // - all session key already determined, look for enduser_const.hh for `SESSION_KEY_HINT`
    // - unless some manner meant to used with filter or middleware, use that instead
    _ISessionControl ISessionControl = _ISessionControl();
};

} // namespace libbackend

#endif // LIBBACKEND_IDROGON_CTL_HELPER_HH
