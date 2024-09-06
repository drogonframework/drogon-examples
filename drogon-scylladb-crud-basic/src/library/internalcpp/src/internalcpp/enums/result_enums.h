#ifndef INTERNAL_RESULT_ENUMS_H
#define INTERNAL_RESULT_ENUMS_H

namespace internalcpp
{

/**
 * @brief enum result status structure
 * 
 */
struct EResultStatus
{
    /**
     * @brief enum object for EResultStatus
     * 
     */
    enum Enum : int32_t
    {
        RESULT_STATUS_ERROR = -1,
        RESULT_STATUS_UNDEFINED = 0,
        RESULT_STATUS_OK,
        RESULT_STATUS_WARNING,
        RESULT_STATUS_RESULT_EXISTS,
        RESULT_STATUS_RESULT_NOT_EXISTS,
    };
};

} // namespace internalcpp

#endif // INTERNAL_RESULT_ENUMS_H
