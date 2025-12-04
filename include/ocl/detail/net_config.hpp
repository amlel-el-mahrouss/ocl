
#pragma once

#include <stdexcept>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <cstddef>
#include <cstring>

#ifdef OCL_WINDOWS
#error !!! "Windows is not supported yet for <unique_socket>" !!!
#endif // OCL_WINDOWS
