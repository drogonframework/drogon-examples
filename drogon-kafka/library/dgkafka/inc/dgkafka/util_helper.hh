#ifndef UTIL_HELPER_HH
#define UTIL_HELPER_HH
#include <drogon/WebSocketController.h>
#include <json/json.h>
#include <random>

namespace util_helper {

static std::random_device _rand;
static std::default_random_engine _rande(_rand());

// --------------------------------------------------------- //

template<typename T>
T random_num_round(const T &min, const T &max) {
	std::uniform_int_distribution<T> eval(min, max);

	return eval(_rande);
}

template<typename T>
T random_num_decimal(const T &min, const T &max) {
	std::uniform_real_distribution<T> eval(min, max);

	return eval(_rande);
}

// --------------------------------------------------------- //

std::string timestamp(const int &tz_offset = 0);

// --------------------------------------------------------- //

namespace jsoncpp {

/// @brief convert json from json string input
/// 
/// @param input
/// @param indent
/// @param precision
///
/// @return Json::Value
Json::Value from_string(const std::string &input, const int8_t &indent = 4, const int8_t &precision = 16);

/// @brief read json from file path and convert it to json object as is
/// 
/// @param json_file_path
///
/// @return Json::Value
Json::Value from_json_file(const std::string &json_file_path);

 /// @brief read json input and convert to string
 /// 
 /// @param input
 /// @param indent
 /// @param precision
 ///
 /// @return std::string
std::string to_string(const Json::Value &input, const int8_t &indent = 4, const int8_t &precision = 16);

} // namespace jsoncpp

// --------------------------------------------------------- //

namespace drogon_framework {

/// @brief get websocket message type as string
///
/// @param ws_type
///
/// @return std::string
std::string get_websocket_message_type_as_string(const drogon::WebSocketMessageType &ws_type);

} // namespace drogon_framework

} // namespace helper_functions

#endif // UTIL_HELPER_HH

