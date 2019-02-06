#ifdef _WIN32
  /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0A00  /* Windows 10 */
  #endif
  #ifndef OS_Windows
    #define OS_Windows
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>
  // For windows: MinGW/include/pthread.h redefine timespec struc
  // this instruction avoid redefinition
  #include <time.h>
  #include <windows.h>
  #include "windows_nanosleep.h"
#ifndef HAVE_STRUCT_TIMESPEC
  #define HAVE_STRUCT_TIMESPEC
#endif
#else
  /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
  #include <sys/select.h>
  #include <arpa/inet.h>
  #include <netinet/in.h>
  #include <netdb.h>
  // For windows: MinGW/include/pthread.h redefine timespec struc
  #include <sys/socket.h>
  #include <time.h>
#endif
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
