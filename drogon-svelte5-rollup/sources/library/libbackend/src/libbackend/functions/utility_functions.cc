#include "utility_functions.hh"

#include <fstream>
#include <iostream>

namespace libbackend {
namespace utility_functions {

namespace find {

int32_t inputEndsWith(const std::string& input, const std::string& keyword) {
    if (input.length() < keyword.length()) {
        return -1;
    }

    return input.compare(input.length() - keyword.length(), keyword.length(), keyword) == 0 ? 1 : -2;
}

} // namespace find

// ------------------------------------------------------ //

namespace jsoncpp {

Json::Value fromJsonFile(const std::string& jsonFile) {
    Json::Value result;

    if (find::inputEndsWith(jsonFile, ".json") != 1) {
        std::cerr << "jsonFile is not end with .json\n";
        return result;
    }

    std::ifstream file(jsonFile);

    if (file.is_open()) {
        file >> result;
        file.close();
    } else {
        std::cerr << "jsoncpp::fromJsonFile: can't find json file from \"" << jsonFile << "\"\n";
    }

    return result;
}

} // namespace jsoncpp

} // namespace utility_functions
} // namespace libbackend
