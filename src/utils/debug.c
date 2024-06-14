#include <stdio.h>
#include <string.h>

#ifndef HAARAGAME_UTILS_DEBUG
    #define HAARAGAME_UTILS_DEBUG

    #define HG_LOG_INFO "INFO"
    #define HG_LOG_DEBUG "DEBUG"
    #define HG_LOG_WARNING "WARNING"
    #define HG_LOG_ERROR "ERROR"

    #define HG_DEBUG(level, format, ...) fprintf(stderr, "[%s] "format"\n", level __VA_OPT__(, __VA_ARGS__))
#endif