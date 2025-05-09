#ifndef BASE_HELPER_H
#define BASE_HELPER_H

// External Includes
//====================================================================

#include <stdint.h>
#include <errno.h>
#include <stddef.h>

#ifdef SIMD_SSE
#   ifdef COMPILER_TCC
#       include "../external/simde/x86/sse.h"
#   else
#       include <xmmintrin.h>
#   endif
#endif

#ifdef SIMD_NEON
# include <arm_neon.h>
#endif

// Code Keywords
//====================================================================

#define fn          static
#define global      static
#define local_persist   static

// Inline
//====================================================================

#if defined(_MSC_VER)
    #if _MSC_VER < 1300
        #define force_inline
    #else
        #define force_inline __forceinline
    #endif
#else
    #define force_inline __attribute__ ((__always_inline__))
#endif

// Tread static
//====================================================================

#if COMPILER_MSVC
#   define thread_static __declspec(thread)
#elif COMPILER_CLANG || COMPILER_GCC || COMPILER_TCC
#   define thread_static __thread
#endif

// Singly-Linked, singly-headed lists (stacks)
//====================================================================

#define SLLStackPush_N(f,n,next) ((n)->next=(f), (f)=(n))
#define SLLStackPop_N(f,next) ((f)=(f)->next)

// Asserts
//====================================================================

#if COMPILER_MSVC
#   define Trap() __debugbreak()
#elif COMPILER_CLANG || COMPILER_GCC
#   define Trap() __builtin_trap()
#elif COMPILER_TCC
#   define Trap() asm volatile("ud2");
#else
#   error Unknown trap intrinsic for this compiler.
#endif

#define AssertAlways(x) do{if(!(x)) {Trap();}}while(0)
#if BUILD_DEBUG
#   define Assert(x) AssertAlways(x)
#else
#   define Assert(x) (void)(x)
#endif
#define InvalidPath        Assert(!"Invalid Path!")
#define NotImplemented     Assert(!"Not Implemented!")
#define NoOp               ((void)0)
#define StaticAssert(C, ID) global U8 Glue(ID, __LINE__)[(C)?1:-1]

// Linkage Keyword Macros
//====================================================================

#if OS_WINDOWS
  #define shared_function C_LINKAGE __declspec(dllexport)
#else
  #define shared_function C_LINKAGE
#endif

#if LANG_CPP
  #define C_LINKAGE_BEGIN extern "C"{
  #define C_LINKAGE_END }
  #define C_LINKAGE extern "C"
#else
  #define C_LINKAGE_BEGIN
  #define C_LINKAGE_END
  #define C_LINKAGE
#endif

// Build
//====================================================================

#if !defined(BUILD_DEBUG)
#   define BUILD_DEBUG 1
#endif

// Units
//====================================================================

#define KB(n)  (((U64)(n)) << 10)
#define MB(n)  (((U64)(n)) << 20)
#define GB(n)  (((U64)(n)) << 30)
#define TB(n)  (((U64)(n)) << 40)
#define Thousand(n)   ((n)*1000)
#define Million(n)    ((n)*1000000)
#define Billion(n)    ((n)*1000000000)

// Clamps, Mins, Maxes
//====================================================================

#define Min(A,B) (((A)<(B))?(A):(B))
#define Max(A,B) (((A)>(B))?(A):(B))
#define ClampTop(A,X) Min(A,X)
#define ClampBot(X,B) Max(X,B)
#define Clamp(A,X,B) (((X)<(A))?(A):((X)>(B))?(B):(X))

// Alignment
//====================================================================

#if COMPILER_MSVC
#   define AlignOf(T) __alignof(T)
#elif COMPILER_CLANG
#   define AlignOf(T) __alignof(T)
#elif COMPILER_GCC || COMPILER_TCC
#   define AlignOf(T) __alignof__(T)
#else
#   error AlignOf not defined for this compiler.
#endif

// Address Sanitizer Markup
//====================================================================

#if COMPILER_MSVC
#   if defined(__SANITIZE_ADDRESS__)
#       define ASAN_ENABLED 1
#       define NO_ASAN __declspec(no_sanitize_address)
#   else
#       define NO_ASAN
#   endif
#elif COMPILER_CLANG
#   if defined(__has_feature)
#       if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#           define ASAN_ENABLED 1
#       endif
#   endif
#   define NO_ASAN __attribute__((no_sanitize("address")))
#else
#   define NO_ASAN
#endif

#if ASAN_ENABLED
#pragma comment(lib, "clang_rt.asan-x86_64.lib")
C_LINKAGE void __asan_poison_memory_region(void const volatile *addr, size_t size);
C_LINKAGE void __asan_unpoison_memory_region(void const volatile *addr, size_t size);
#   define AsanPoisonMemoryRegion(addr, size)   __asan_poison_memory_region((addr), (size))
#   define AsanUnpoisonMemoryRegion(addr, size) __asan_unpoison_memory_region((addr), (size))
#else
#   define AsanPoisonMemoryRegion(addr, size)   ((void)(addr), (void)(size))
#   define AsanUnpoisonMemoryRegion(addr, size) ((void)(addr), (void)(size))
#endif

// Misc. Macros
//====================================================================

#define cast(Type) (Type)

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)

#define ArrayCount(a) (sizeof(a) / sizeof((a)[0]))

#define Glue_(A,B) A##B
#define Glue(A,B) Glue_(A,B)

#if ARCH_64BIT
#   define IntFromPtr(ptr) ((U64)(ptr))
#elif ARCH_32BIT
#   define IntFromPtr(ptr) ((U32)(ptr))
#else
#   error Missing pointer-to-integer cast for this architecture.
#endif

#define AlignPow2(x,b)     (((x) + (b) - 1)&(~((b) - 1)))
#define AlignDownPow2(x,b) ((x)&(~((b) - 1)))
#define AlignPadPow2(x,b)  ((0-(x)) & ((b) - 1))
#define IsPow2(x)          ((x)!=0 && ((x)&((x)-1))==0)
#define IsPow2OrZero(x)    ((((x) - 1)&(x)) == 0)

// Base Types
//====================================================================

#if LANG_C
    #define bool  _Bool
#endif

#define true  1
#define false 0

typedef uint8_t   U8;
typedef int8_t    I8;
typedef uint16_t  U16;
typedef int16_t   I16;
typedef uint32_t  U32;
typedef int32_t   I32;
typedef uint64_t  U64;
typedef int64_t   I64;

typedef float    F32;
typedef double   F64;

typedef size_t    USize;
typedef ptrdiff_t ISize;

#if defined(_WIN64)
    typedef signed   __int64  IPtr;
    typedef unsigned __int64 UPtr;
#elif defined(_WIN32)
    // NOTE: To mark types changing their size, e.g. IPtr
    #ifndef _W64
        #if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
            #define _W64 __w64
        #else
            #define _W64
        #endif
    #endif

    typedef _W64   signed int  IPtr;
    typedef _W64 unsigned int UPtr;
#else
    typedef uintptr_t UPtr;
    typedef  intptr_t  IPtr;
#endif

// Define Values
//====================================================================

#ifndef NULL
    #if defined(__cplusplus)
        #if __cplusplus >= 201103L
            #define NULL nullptr
        #else
            #define NULL 0
        #endif
    #else
        #define NULL ((void *)0)
    #endif
#endif

#if LANG_CPP
#   define ZERO_STRUCT {}
#else
#   define ZERO_STRUCT {0}
#endif

// Time
//====================================================================

typedef enum WeekDay {
    WeekDay_sun,
    WeekDay_mon,
    WeekDay_tue,
    WeekDay_wed,
    WeekDay_thu,
    WeekDay_fri,
    WeekDay_sat,
    WeekDay_COUNT,
} WeekDay;

typedef enum Month {
    Month_jan,
    Month_feb,
    Month_mar,
    Month_apr,
    Month_may,
    Month_jun,
    Month_jul,
    Month_aug,
    Month_sep,
    Month_oct,
    Month_nov,
    Month_dec,
    Month_COUNT,
} Month;

typedef struct DateTime
{
    U16 micro_sec; // [0,999]
    U16 msec; // [0,999]
    U16 sec;  // [0,60]
    U16 min;  // [0,59]
    U16 hour; // [0,24]
    U16 day;  // [0,30]
    union
    {
        WeekDay week_day;
        U32 wday;
    };
    union
    {
        Month month;
        U32 mon;
    };
    U32 year; // 1 = 1 CE, 0 = 1 BC
} DateTime;

#endif // BASE_HELPER_H
