#include "utility_module.h"

namespace internalcpp
{

UtilityModule::UtilityModule()
{
}

UtilityModule::~UtilityModule()
{
}

std::string UtilityModule::SJsonHelper::toString(const Json::Value &input)
{
    std::string result;

    Json::StreamWriterBuilder builder;
    result = Json::writeString(builder, input);

    return result;
}

Json::Value UtilityModule::SJsonHelper::fromString(const std::string &input)
{
    Json::Value result;

    JSONCPP_STRING err;
    Json::CharReaderBuilder builder;
    const int inputLength = static_cast<int>(input.length());

    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    reader->parse(input.c_str(), input.c_str() + inputLength, &result, &err);

    return result;
}

} // namespace internalcpp
