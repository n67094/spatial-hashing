#ifndef CORE_LOG
#define CORE_LOG

#ifdef NDEBUG
  #include <stdarg.h>
  #include <stdio.h>

  #define LOG_WHITE "\x1b[37m"
  #define LOG_BLUE "\x1B[34m"
  #define LOG_MAGENTA "\x1B[35m"
  #define LOG_YELLOW "\x1B[33m"
  #define LOG_RED "\x1B[31m"

  #define LOG_DEBUG_PREFIX "[DEBUG] --- "
  #define LOG_INFO_PREFIX "[INFO] ---- "
  #define LOG_WARNING_PREFIX "[WARNING] - "
  #define LOG_ERROR_PREFIX "[ERROR] --- "

  #define LOG_EX(color, prefix, message, ...)                                  \
    {                                                                          \
      printf(color);                                                           \
      printf("%s %s %s line: %d - ", prefix, __FILE__, __func__, __LINE__);    \
      printf(__VA_ARGS__);                                                     \
    }

  #define LOG_DEBUG(...)                                              \
    LOG_EX(LOG_MAGENTA, LOG_DEBUG_PREFIX, message, __VA_ARGS__)

  #define LOG_INFO(...)                                               \
    LOG_EX(LOG_WHITE, LOG_INFO_PREFIX, message, __VA_ARGS__)

  #define LOG_WARNING(...)                                            \
    LOG_EX(LOG_YELLOW, LOG_WARNING_PREFIX, message, __VA_ARGS__)

  #define LOG_ERROR(...)                                              \
    LOG_EX(LOG_RED, LOG_ERROR_PREFIX, message, __VA_ARGS__)
#else
  #define LOG_DEBUG(...)
  #define LOG_INFO(...)
  #define LOG_WARNING(...)
  #define LOG_ERROR(...)
#endif

#endif
