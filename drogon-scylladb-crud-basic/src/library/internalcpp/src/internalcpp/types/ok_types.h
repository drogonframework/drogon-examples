#ifndef INTERNALCPP_OK_TYPES_H
#define INTERNALCPP_OK_TYPES_H
#include <string>

namespace internallcpp
{

/**
 * @brief type storage with ok and message for properties
 * 
 */
struct TOkMessage
{
    bool ok = false;
    std::string message = "";
};

} // namespace internallcpp

#endif // INTERNALCPP_OK_TYPES_H
