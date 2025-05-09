#ifndef BASE_FMT_T
#define BASE_FMT_T

#define STB_SPRINTF_IMPLEMENTATION
#include "ccore/external/stb_sprintf.h"

#define fmt_vsnprintf stbsp_vsnprintf

// Write to the character string
//====================================================================

fn Str8 fmt_sprintv_str8(Arena *arena, Str8 fmt, va_list vlist);
fn Str8 fmt_sprintf_str8(Arena *arena, Str8 fmt, ...);

// File Print
//====================================================================

// fn void fmt_vfprintf_str8(Os_File fd, Str8 fmt, va_list vlist);
// fn void fmt_fprintf_str8(Os_File fd, Str8 fmt, ...);
// fn void fmt_fprintf(Os_File fd, const char *fmt, ...);

// Standard Ouput Print
//====================================================================

fn void fmt_printv_str8(Str8 fmt, va_list vlist);
fn void fmt_printf_str8(Str8 fmt, ...);
fn void fmt_printf(const char *fmt, ...);

// Print Error
//====================================================================

fn void fmt_eprintv_str8(Str8 fmt, va_list vlist);
fn void fmt_eprintf_str8(Str8 fmt, ...);
fn void fmt_eprintf(const char *fmt, ...);

#endif // BASE_FMT_T
