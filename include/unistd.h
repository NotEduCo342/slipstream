#pragma once

#ifdef _WIN32
#include <io.h>
#include <process.h>
#include <windows.h>
#include <BaseTsd.h>

typedef SSIZE_T ssize_t;

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#endif

#ifndef close
#define close _close
#endif

#ifndef read
#define read _read
#endif

#ifndef write
#define write _write
#endif

static inline unsigned int sleep(unsigned int seconds) {
    Sleep(seconds * 1000u);
    return 0;
}
#endif
