#ifndef INTERNALCPP_UTILITY_MODULE_H
#define INTERNALCPP_UTILITY_MODULE_H
#include <string>

#include <json/json.h>

namespace internalcpp
{

/**
 * @brief internalcpp utility module class
 * 
 */
class UtilityModule
{
private:
    /* data */

public:
    UtilityModule(/* args */);
    ~UtilityModule();

    // json helper structure
    struct SJsonHelper
    {
        /**
         * @brief get json as string
         * 
         * @param input 
         * @return std::string 
         */
        std::string toString(const Json::Value &input);

        /**
         * @brief get json data from string
         * 
         * @param input 
         * @return Json::Value 
         */
        Json::Value fromString(const std::string &input);
    };
    // json helper object access
    SJsonHelper JsonHelper = SJsonHelper();
};

} // namespace internalcpp

#endif // INTERNALCPP_UTILITY_MODULE_H
