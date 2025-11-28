#include <dgkafka/util_helper.hh>

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

namespace util_helper {

std::string timestamp(const int &tz_offset) {
	int tz = tz_offset * 3'600;
	std::string s;
	std::stringstream ss;

	if (tz <= -12) { tz = -12; }
	if (tz >= 14) { tz = 14; }

	auto now = std::chrono::system_clock::now();

	    std::time_t now_time = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
    std::time_t now_time_utc = now_time + tz;

    tm tm_buf;

    gmtime_r(&now_time_utc, &tm_buf); // unix compatible

    auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto nanoseconds = now_ns.time_since_epoch() % std::chrono::seconds(1);

    ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(9)
           << std::setfill('0') << nanoseconds.count();

	return ss.str();
}

namespace jsoncpp {

Json::Value from_string(const std::string& input, const int8_t& indent, const int8_t& precision) {
    Json::Value result;

    try {
        int8_t _indent = indent, _precision = precision;

        if (_indent <= 0) {
            _indent = 0;
        }
        if (_precision <= 2) {
            _precision = 2;
        }

        std::string _indent_string = "";
        for (auto i = 0; i < _indent; i++) {
            _indent_string += " ";
        }

        JSONCPP_STRING err;
        Json::CharReaderBuilder builder;

        builder.settings_["indentation"] = _indent_string;
        builder.settings_["precision"] = _precision;

        const int inputLength = static_cast<int>(input.length());

        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        reader->parse(input.c_str(), input.c_str() + inputLength, &result, &err);
    } catch (const std::exception& e) {
        std::cerr << "exception helper_functions::jsoncpp::from_string: " << e.what() << '\n';

        result = (std::string)e.what();
    }

    return result;
}

Json::Value from_json_file(const std::string& json_file_path) {
    Json::Value result = Json::Value::null;

    std::ifstream file(json_file_path);

    if (file.is_open()) {
        file >> result;
    } else {
        std::cerr << "jsoncpp::from_json_file: can't find json file from \"" << json_file_path << "\"\n";
    }

    file.close();

    return result;
}

std::string to_string(const Json::Value& input, const int8_t& indent, const int8_t& precision) {
    int32_t _indent = indent, _precision = precision;

    // force some rule
    if (_indent <= 0) {
        _indent = 0;
    }
    if (_precision <= 2) {
        _precision = 2;
    }

    Json::StreamWriterBuilder writer;

    std::string _indent_string = "";
    for (auto i = 0; i < _indent; i++) {
        _indent_string += " ";
    }

    writer.settings_["indentation"] = _indent_string;
    writer.settings_["precision"] = _precision;

    return std::string(Json::writeString(writer, input));
}

} // namespace jsoncpp

// --------------------------------------------------------- //

namespace drogon_framework {

std::string get_websocket_message_type_as_string(const drogon::WebSocketMessageType& ws_type) {
    switch (ws_type) {
        case drogon::WebSocketMessageType::Ping:
            return "Ping";
        break;

        case drogon::WebSocketMessageType::Pong:
            return "Pong";
        break;

        case drogon::WebSocketMessageType::Text:
            return "Text";
        break;

        case drogon::WebSocketMessageType::Binary:
            return "Binary";
        break;

        case drogon::WebSocketMessageType::Close:
            return "Close";
        break;

        default:
            return "Default";
        break;
    }
}

} // namaespace drogon_framework

} // namespace util_helper

