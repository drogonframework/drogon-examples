#ifndef INTERNALCPP_CONFIG_H
#define INTERNALCPP_CONFIG_H

#ifndef PROJECT_BUILD_TYPE
    // 0:undefined 1:debug 2:profile 3:minsizerel 4:relwithdebinfo 5:release
    #define PROJECT_BUILD_TYPE @PROJECT_BUILD_TYPE@
#endif // PROJECT_BUILD_TYPE

#endif // INTERNALCPP_CONFIG_H
