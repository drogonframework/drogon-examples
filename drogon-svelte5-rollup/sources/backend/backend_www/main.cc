#include <drogon/drogon.h>

#include <libbackend/functions/utility_functions.hh>

// relative from the executeable
#define CONFIG_FILE "../.config/config.backend_www.json"

int main() {
    drogon::app().loadConfigFile(CONFIG_FILE);

    // this config file for backend
    Json::Value const CONFIG = libbackend::utility_functions::jsoncpp::fromJsonFile(CONFIG_FILE);

    // status init check
    {
        std::cout << "INFO: backend_www initialize:\n";

        // listeners list
        Json::Value listeners = CONFIG["listeners"];

        for (int32_t i = 0; i < listeners.size(); i++) {
            std::cout << "#" << i+1 << " -> http://localhost:" << listeners[i]["port"].asInt() << "/\n";
        }
    }

    // cusotm page 404
    {
        drogon::HttpResponsePtr pResp404 = drogon::HttpResponse::newHttpResponse();
        
        pResp404->setBody("<!DOCTYPE html><html><head><title>404</title></head><body><h1>404</h1></body></html>");
        pResp404->setStatusCode(drogon::k404NotFound);
        pResp404->setExpiredTime(0);

        drogon::app().setCustom404Page(pResp404);
    }

    drogon::app().run();

    return 0;
}
