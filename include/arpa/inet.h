#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN 16
#endif
#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46
#endif

#else
#include_next <arpa/inet.h>
#endif
