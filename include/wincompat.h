#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <BaseTsd.h>
#include <stddef.h>
#include <stdint.h>

#ifndef ssize_t
typedef SSIZE_T ssize_t;
#endif

#ifndef strcasecmp
#define strcasecmp _stricmp
#endif

#ifndef strncasecmp
#define strncasecmp _strnicmp
#endif

#ifndef inline
#define inline __inline
#endif
#endif
