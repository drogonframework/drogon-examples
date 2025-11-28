#include <drogon/drogon.h>

#define LISTENER_IP "0.0.0.0"
#define LISTENER_PORT 9000

int main() {
    printf("starting backend_drogon_kafka: %s:%d\n",
            LISTENER_IP,
            LISTENER_PORT);

    // base conf
    drogon::app().addListener(LISTENER_IP, LISTENER_PORT)
                 .setLogLevel(trantor::Logger::kTrace)
                 .setDocumentRoot("../public")
                 .setUploadPath("upload")
                 .setLogPath("../logs");

    // 404
    Json::Value json404 = 404;
    drogon::HttpResponsePtr p_resp404 = drogon::HttpResponse::newHttpJsonResponse(json404);
    p_resp404->setStatusCode(drogon::k404NotFound);
    p_resp404->setExpiredTime(0);

    // plugin
    std::string plugin_name = "PluginDrogonKafka";
    std::vector<std::string> plugin_deps = {};
    Json::Value plugin_config;
    drogon::app().addPlugin(plugin_name,
                            plugin_deps,
                            plugin_config);

    // connection
    drogon::app().setIdleConnectionTimeout(0)
                 .setKeepaliveRequestsNumber(0);

    // init run
    drogon::app().setCustom404Page(p_resp404)
                 .run();

    return 0;
}

