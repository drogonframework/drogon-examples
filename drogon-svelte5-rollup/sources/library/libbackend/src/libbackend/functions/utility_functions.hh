#ifndef LIBBACKEND_UTILITY_FUNCTIONS_HH
#define LIBBACKEND_UTILITY_FUNCTIONS_HH
#include <json/json.h>

namespace libbackend {
namespace utility_functions {

namespace find {

/**
 * @brief check if input param ended with keyword param
 * 
 * @param input 
 * @param keyword 
 * @return int32_t 1 == true
 */
int32_t inputEndsWith(const std::string& input, const std::string& keyword);

} // namespace find

namespace jsoncpp {

/**
 * @brief read json from file path and convert it to json object as is
 *
 * @param jsonFile
 * @return Json::Value
 */
Json::Value fromJsonFile(const std::string& jsonFile);

} // namespace jsoncpp

} // namespace utility_functions
} // namespace libbackend

#endif // LIBBACKEND_UTILITY_FUNCTIONS_HH
