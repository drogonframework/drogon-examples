#include "main.h"

int main(int argc, char *argv[])
{
    drogon::app().loadConfigFile("../configs/json/backend.api.json");

    drogon::app().run();
}
