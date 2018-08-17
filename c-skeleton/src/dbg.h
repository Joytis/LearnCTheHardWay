// DEBUG PRINT MACROS.
// C Version with no cool exception throwing capabilities.

// They don't look super pretty, but these macros are super helpful for
//      printing useful debug messages!


#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

// Definitions for debug phrases.
#define DEBUG_ON 1
#define DEBUG_OFF 0

// Define phrases here for debug(A, M, ...) to pass into A
// EX: #define DBG_MAIN DEBUG_ON
#define DBG_CONN                            DEBUG_OFF
#define DBG_SESSION                         DEBUG_ON
#define DBG_SERVER                          DEBUG_ON

// __FILENAME__ is used to clean up the file paths a fair bit.
#ifdef WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1: __FILE__)
#else // OSX & Linux
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1: __FILE__)
#endif

#if NDEBUG

#define debug(A, M, ...) if(A){ log_info(M, ##__VA_ARGS__); } else{}

// C errno stuff.
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

// Logs an err. Called in check or if you REALLY need to
#define log_err(M, ...)                                                                  \
fprintf(stderr, "[ERROR] (%s:%d | errno: %s): " M "\n",                                  \
        __FILENAME__,                                                                    \
        __LINE__,                                                                        \
        clean_errno(),                                                                   \
        ##__VA_ARGS__)

// Logs a warning. Not fatal, but you probably don't want it happening.
#define log_warn(M, ...)                                                                 \
fprintf(stderr, "[WARN] (%s:%d | errno: %s): " M "\n",                                   \
        __FILENAME__,                                                                    \
        __LINE__,                                                                        \
        clean_errno(),                                                                   \
        ##__VA_ARGS__)

// Just a quick info log. Nothing big.
#define log_info(M, ...)                                                                 \
fprintf(stdout, "[INFO] (%s:%d): " M "\n",                                               \
        __FILENAME__,                                                                    \
        __LINE__,                                                                        \
        ##__VA_ARGS__)

// Checks is A is true, if not, log_err's the message and throws exception E
#define check(A, M, ...)                                                              \
if(!(A))                                                                                 \
{                                                                                        \
    log_err(E, M, ##__VA_ARGS__);                                                        \
    errno=0;                                                                             \
    goto error;                                                                          \
}

// If code hits this, it will throw an exception and log an error.
//      Put where you don't want things to happen.
#define sentinel(M, ...)                                                              \
{                                                                                        \
    log_err(E, M, ##__VA_ARGS__);                                                        \
    errno=0;                                                                             \
    goto error;                                                                          \
}

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }
#define check_mem(A) check((A), e_bad_allocation, "Out of Memory.")

#else
#define debug(A, M, ...)
#define sentinel(M, ...)
#define check(A, M, ...)
#define log_info(M, ...)
#define log_warn(M, ...)
#define log_err(M, ...)
#define clean_errno()
#endif // NDEBUG

#endif //__dbg_h__
