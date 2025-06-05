#include "common_pages.hh"

#include <libbackend/constants/header_const.hh>
#include <libbackend/functions/utility_functions.hh>
#include <libbackend/lib.hh>

#define CONFIG_PROJECT_FILE "../.config/config.project.json"

#define THIS_VALID_USERNAME "dgdrogon"
#define THIS_VALID_USER_EMAIL "dg@drogon.org"
#define THIS_VALID_USER_PSWRD "drogonframework"

using namespace libbackend;

namespace backend_www {

void CommonPages::base(const HttpRequestPtr& pReq, std::function<void(const HttpResponsePtr&)>&& callback) {
    HttpViewData viewData;
    std::string checkEndpoint, checkLanguage;
    bool languageSupported = false;
    HttpResponsePtr pResp = HttpResponse::newHttpResponse();

    const Json::Value CONFIG_PROJECT = utility_functions::jsoncpp::fromJsonFile(CONFIG_PROJECT_FILE);
    const Json::Value SUPPORTED_LANGUAGES = CONFIG_PROJECT["supported"]["languages"];

    // controll the method/s here manually
    // each method must do imediate callback
    if (pReq->getMethod() == Get) {
        for (auto& language : SUPPORTED_LANGUAGES) {
            if (pReq->getHeader(HTTP_HEADER_ALIASES::ACCEPT_LANGUAGE).find(language.asString()) != std::string::npos) {
                languageSupported = true;
                checkLanguage = language.asString();
                checkEndpoint = "/" + checkLanguage + "/home";
                break;
            }
        }

        if (!languageSupported) {
            checkLanguage = "en";
            checkEndpoint = "/en/home";
        }

        // invoke basic title
        IInvokeMeta.title("My Website", viewData);

        pResp = HttpResponse::newHttpViewResponse("www_svelte", viewData);

        // do callback but also based on language
        callback(pResp->newRedirectionResponse(checkEndpoint, k307TemporaryRedirect));
        return; // finish for get method
    }

    // out of impl
    pResp = HttpResponse::newHttpResponse();
    pResp->setStatusCode(k405MethodNotAllowed);

    callback(pResp);
}

void CommonPages::home(const HttpRequestPtr& pReq, std::function<void(const HttpResponsePtr&)>&& callback, std::string&& lang) {
    HttpViewData viewData;
    HttpResponsePtr pResp = HttpResponse::newHttpResponse();

    std::string bundleName; // required `/` at the 0 position
    std::string defaultEndpoint = "/en/home", defaultLanguage = "en";

    const Json::Value CONFIG_PROJECT = utility_functions::jsoncpp::fromJsonFile(CONFIG_PROJECT_FILE);
    const Json::Value SUPPORTED_LANGUAGES = CONFIG_PROJECT["supported"]["languages"];

    // session region
    {
        ISessionControl.initialize(pReq, viewData);
    }

    if (pReq->getMethod() == Get) {
        // check lang param, use `en` as default
        // redirect to defaultEndpoint if not supported
        // otherwise it keep modified lang var to confirm from SUPPORTED_LANGAUGES
        // - will modify 3rd param
        if (!IBeforeCallback.acceptedLanguage(SUPPORTED_LANGUAGES, defaultLanguage, lang)) {
            callback(pResp->newRedirectionResponse(defaultEndpoint, k307TemporaryRedirect));
            return;
        }

        bundleName = "/www-home-bundle-" + lang;

        // invoke basic title - en
        IInvokeMeta.title("My Website: Home#", viewData); // default
        if (lang == "en") {
            IInvokeMeta.language("en", viewData);
            IInvokeMeta.title("My Website: Home", viewData);
        }

        // invoke basic title - id
        if (lang == "id") {
            IInvokeMeta.language("id", viewData);
            IInvokeMeta.title("My Website: Beranda", viewData);
        }

// assign core meta in `production` (release/minsizerel build)
// NOTE:
// - see inside html head tag after the page rendered
// - if you want to expose in debug, demo/alpha, or staging, create your own rule condition here
#if !PROJECT_IS_DEBUG
        // en section
        if (lang == "en") {
            IInvokeMeta.about("this is my website", viewData);
            IInvokeMeta.description("page description", viewData);
        }

        // id section
        if (lang == "id") {
            IInvokeMeta.title("ini website-ku", viewData);
            IInvokeMeta.description("deskripsi/keterangan halaman", viewData);
        }
        // no default prevention
#endif // !PROJECT_IS_DEBUG

        // create bundle frontend
        IFrontendBundle.addJs(bundleName, viewData);
        IFrontendBundle.addCss(bundleName, viewData);

        pResp = HttpResponse::newHttpViewResponse("www_svelte", viewData);

        callback(pResp);
        return;
    } // end get method

    // out of impl
    pResp = HttpResponse::newHttpResponse();
    pResp->setStatusCode(k405MethodNotAllowed);

    callback(pResp);
}

void CommonPages::signin(const HttpRequestPtr& pReq, std::function<void(const HttpResponsePtr&)>&& callback, std::string&& lang) {
    HttpViewData viewData;
    HttpResponsePtr pResp = HttpResponse::newHttpResponse();

    std::string bundleName; // required `/` at the 0 position
    std::string defaultEndpoint = "/en/sign-in", defaultLanguage = "en";

    const Json::Value CONFIG_PROJECT = utility_functions::jsoncpp::fromJsonFile(CONFIG_PROJECT_FILE);
    const Json::Value SUPPORTED_LANGUAGES = CONFIG_PROJECT["supported"]["languages"];

    // session region
    {
        ISessionControl.initialize(pReq, viewData);
    }

    IInvokeMeta.title("My Website: sign-in", viewData);

    if (pReq->getMethod() == Get) {
        if (!IBeforeCallback.acceptedLanguage(SUPPORTED_LANGUAGES, defaultLanguage, lang)) {
            callback(pResp->newRedirectionResponse(defaultEndpoint, k307TemporaryRedirect));
            return;
        }

        // already sign-in, redirect
        if (ISessionControl.getIsSignIn(pReq)) {
            std::string redirect = "/" + lang + "/home";
            callback(pResp->newRedirectionResponse(redirect));
            return;
        }

        bundleName = "/www-signin-bundle-" + lang;

        // create bundle frontend
        IFrontendBundle.addJs(bundleName, viewData);
        IFrontendBundle.addCss(bundleName, viewData);

        // adding empty message
        viewData.insert("{MESSAGE}", "");

        pResp = HttpResponse::newHttpViewResponse("www_svelte", viewData);

        callback(pResp);
        return;
    } // end get method

    if (pReq->getMethod() == Post) {
        if (!IBeforeCallback.acceptedLanguage(SUPPORTED_LANGUAGES, defaultLanguage, lang)) {
            callback(pResp->newRedirectionResponse(defaultEndpoint, k307TemporaryRedirect));
            return;
        }

        bundleName = "/www-signin-bundle-" + lang;

        // create bundle frontend
        IFrontendBundle.addJs(bundleName, viewData);
        IFrontendBundle.addCss(bundleName, viewData);

        bool signInOk = false, formNameNotEmpty = false;
        std::string backendMessage = "";

        std::string email = pReq->getParameter("email");
        std::string password = pReq->getParameter("password");

        // make sure email & password is not empty
        if (email.empty() || password.empty()) {
            // en
            if (lang == "en") {
                backendMessage = "email & password can't be empty";
            }

            // id
            if (lang == "en") {
                backendMessage = "email & kata sandi tidak boleh kosong";
            }
        }
        if (!email.empty() && !password.empty()) {
            formNameNotEmpty = true;
        }

        if (formNameNotEmpty) {
            // do query your db to match the requirements in here

            if (email != THIS_VALID_USER_EMAIL) {
                // en
                if (lang == "en") {
                    backendMessage = "wrong email/password #1";
                }

                // id
                if (lang == "id") {
                    backendMessage = "email/password salah #1";
                }
            }

            if (password != THIS_VALID_USER_PSWRD) {
                // en
                if (lang == "en") {
                    backendMessage = "wrong email/password #2";
                }

                // id
                if (lang == "id") {
                    backendMessage = "email/password salah #2";
                }
            }

            // ok
            if (email == THIS_VALID_USER_EMAIL && password == THIS_VALID_USER_PSWRD) {
                signInOk = true;
                backendMessage.clear();
            }
        }

        // adding empty message
        viewData.insert("{MESSAGE}", backendMessage);

        if (signInOk) {
            // tmp
            viewData.insert("{MESSAGE}", "tmp: ok");

            pResp = HttpResponse::newHttpViewResponse("www_svelte", viewData);

            // create session & redirect
            pReq->session()->insert(ENDUSER::SESSION_KEY_HINT::IS_SIGN_IN, true);
            pReq->session()->insert(ENDUSER::SESSION_KEY_HINT::USERNAME, std::string(THIS_VALID_USERNAME));

            std::string redirect = "/" + lang + "/secret";

            callback(pResp->newRedirectionResponse(redirect, k307TemporaryRedirect));
        } else {
            pResp = HttpResponse::newHttpViewResponse("www_svelte", viewData);

            callback(pResp);
        }
        return;
    } // end post method

    // out of impl
    pResp = HttpResponse::newHttpResponse();
    pResp->setStatusCode(k405MethodNotAllowed);
    
    callback(pResp);
}

void CommonPages::signout(const HttpRequestPtr& pReq, std::function<void(const HttpResponsePtr&)>&& callback) {
    HttpViewData viewData;
    HttpResponsePtr pResp = HttpResponse::newHttpResponse();

    // note: ignoring method

    IInvokeMeta.title("My Website: sign-out", viewData);

    pResp = HttpResponse::newHttpViewResponse("www_svelte", viewData);

    pReq->session()->clear();

    callback(pResp->newRedirectionResponse("/", k307TemporaryRedirect));
}

void CommonPages::secret(const HttpRequestPtr &pReq, std::function<void(const HttpResponsePtr &)> &&callback, std::string&& lang)
{
    HttpViewData viewData; // technically junk
    HttpResponsePtr pResp = HttpResponse::newHttpResponse();

    // note: ignoring method

    std::string defaultEndpoint = "/en/sign-in", defaultLanguage = "en";

    const Json::Value CONFIG_PROJECT = utility_functions::jsoncpp::fromJsonFile(CONFIG_PROJECT_FILE);
    const Json::Value SUPPORTED_LANGUAGES = CONFIG_PROJECT["supported"]["languages"];

    if (!IBeforeCallback.acceptedLanguage(SUPPORTED_LANGUAGES, defaultLanguage, lang)) {
        callback(pResp->newRedirectionResponse(defaultEndpoint, k307TemporaryRedirect));
        return;
    }

    // start session
    {
        ISessionControl.initialize(pReq, viewData);
    }

    // redirect to sign-in
    if (!ISessionControl.getIsSignIn(pReq)) {
        std::string redirect = "/" + lang + "/sign-in";
        callback(pResp->newRedirectionResponse(redirect, k307TemporaryRedirect));
        return;
    }

    const std::string lazyTemplate = R"(<!DOCTYPE html>
<html lang="">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SECRET PAGE</title>
</head>
<body>
    <p>this is secret page that required to sign-in</p>
    <br>
    <a href="/">
        home
    </a>
</body>
</html>)";

    pResp->setBody(lazyTemplate);
    pResp->setStatusCode(k200OK);
    pResp->setContentTypeCode(CT_TEXT_HTML);

    callback(pResp);
}

} // namespace backend_www
