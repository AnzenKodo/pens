#ifndef BASE_CONTEXT_H
#define BASE_CONTEXT_H

// Clang OS/Arch Chacking
//====================================================================

#if defined(__clang__)

#   define COMPILER_CLANG 1

#   if defined(_WIN32)
#       define OS_WINDOWS 1
#   elif defined(__gnu_linux__) || defined(__linux__)
#       define OS_LINUX 1
#   elif defined(__APPLE__) && defined(__MACH__)
#       define OS_MAC 1
#   else
#       error This compiler/OS combo is not supported.
#   endif

#   if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#       define ARCH_X64 1
#   elif defined(i386) || defined(__i386) || defined(__i386__)
#       define ARCH_X86 1
#   elif defined(__aarch64__)
#       define ARCH_ARM64 1
#   elif defined(__arm__)
#       define ARCH_ARM32 1
#   else
#       error Architecture not supported.
#   endif

// MSVC OS/Arch Cracking
//====================================================================

#elif defined(_MSC_VER)

#   define COMPILER_MSVC 1

#   if _MSC_VER >= 1920
#       define COMPILER_MSVC_YEAR 2019
#   elif _MSC_VER >= 1910
#       define COMPILER_MSVC_YEAR 2017
#   elif _MSC_VER >= 1900
#       define COMPILER_MSVC_YEAR 2015
#   elif _MSC_VER >= 1800
#       define COMPILER_MSVC_YEAR 2013
#   elif _MSC_VER >= 1700
#       define COMPILER_MSVC_YEAR 2012
#   elif _MSC_VER >= 1600
#       define COMPILER_MSVC_YEAR 2010
#   elif _MSC_VER >= 1500
#       define COMPILER_MSVC_YEAR 2008
#   elif _MSC_VER >= 1400
#       define COMPILER_MSVC_YEAR 2005
#   else
#       define COMPILER_MSVC_YEAR 0
#   endif

#   if defined(_WIN32)
#       define OS_WINDOWS 1
#   else
#       error This compiler/OS combo is not supported.
#   endif

#   if defined(_M_AMD64)
#       define ARCH_X64 1
#   elif defined(_M_IX86)
#       define ARCH_X86 1
#   elif defined(_M_ARM64)
#       define ARCH_ARM64 1
#   elif defined(_M_ARM)
#       define ARCH_ARM32 1
#   else
#       error Architecture not supported.
#   endif

#if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
	#ifndef CPU_X86
		#define CPU_X86 1
	#endif
#endif

// GCC OS/Arch Cracking
//====================================================================

#elif defined(__GNUC__) || defined(__GNUG__)

#   define COMPILER_GCC 1

#   if defined(__gnu_linux__) || defined(__linux__)
#       define OS_LINUX 1
#   else
#       error This compiler/OS combo is not supported.
#   endif

#   if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#       define ARCH_X64 1
#   elif defined(i386) || defined(__i386) || defined(__i386__)
#       define ARCH_X86 1
#   elif defined(__aarch64__)
#       define ARCH_ARM64 1
#   elif defined(__arm__)
#       define ARCH_ARM32 1
#   else
#       error Architecture not supported.
#   endif

// TCC OS/Arch Checking
//====================================================================

#elif defined(__TINYC__)

#   define COMPILER_TCC 1

#   if defined(__linux__)
#       define OS_LINUX 1
#   elif defined(__windows__)
#       define OS_WINDOWS 1
#   else
#       error This OS is not supported by TCC.
#   endif

#   if defined(__x86_64__)
#       define ARCH_X64 1
#   elif defined(__i386__)
#       define ARCH_X86 1
#   elif defined(__aarch64__)
#       define ARCH_ARM64 1
#   elif defined(__arm__)
#       define ARCH_ARM32 1
#   else
#       error Architecture not supported by TCC.
#   endif

// Not supported compiler
//====================================================================

#else
#   error Compiler not supported.
#endif

// Arch Cracking
//====================================================================

#if defined(ARCH_X64)
# define ARCH_64BIT 1
#elif defined(ARCH_X86)
# define ARCH_32BIT 1
#endif

#if ARCH_ARM32 || ARCH_ARM64 || ARCH_X64 || ARCH_X86
#   define ARCH_LITTLE_ENDIAN 1
#else
#   error Endianness of this architecture not understood by context cracker.
#endif

// Language Cracking
//====================================================================

#if defined(__cplusplus)
#   define LANG_CPP 1
#else
#   define LANG_C 1
#endif

// Zero All Undefined Options
//====================================================================

#if !defined(ARCH_32BIT)
#   define ARCH_32BIT 0
#endif
#if !defined(ARCH_64BIT)
#   define ARCH_64BIT 0
#endif
#if !defined(ARCH_X64)
#   define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
#   define ARCH_X86 0
#endif
#if !defined(ARCH_ARM64)
#   define ARCH_ARM64 0
#endif
#if !defined(ARCH_ARM32)
#   define ARCH_ARM32 0
#endif
#if !defined(COMPILER_MSVC)
#   define COMPILER_MSVC 0
#endif
#if !defined(COMPILER_GCC)
#   define COMPILER_GCC 0
#endif
#if !defined(COMPILER_CLANG)
#   define COMPILER_CLANG 0
#endif
#if !defined(OS_WINDOWS)
#   define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
#   define OS_LINUX 0
#endif
#if !defined(OS_MAC)
#   define OS_MAC 0
#endif
#if !defined(LANG_CPP)
#   define LANG_CPP 0
#endif
#if !defined(LANG_C)
#   define LANG_C 0
#endif

// SIMD
////==================================================================

#ifdef COMPILER_MSVC /* MSVC supports SSE in amd64 mode or _M_IX86_FP >= 1 (2 means SSE2) */
#   if defined(ARCH_X64) || ( defined(_M_IX86_FP) && _M_IX86_FP >= 1 )
#       define SIMD_SSE 1
#   endif
#else /* not MSVC, probably GCC, clang, icc or something that doesn't support SSE anyway */
#   ifdef __SSE__ /* they #define __SSE__ if it's supported */
#       define SIMD_SSE 1
#   endif /*  __SSE__ */
#endif /* not _MSC_VER */
#ifdef __ARM_NEON
#   define SIMD_NEON 1
#endif /* NEON Supported */
#if !defined(SIMD_SSE) && !defined(SIMD_NEON)
#	error No SIMD supported
#endif

#endif // BASE_CONTEXT_H
