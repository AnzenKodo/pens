// OS Layer
//====================================================================

#if OS_LINUX
#   include "os/os_linux.c"
#else
#   error OS layer not implemented for this operating system.
#endif
