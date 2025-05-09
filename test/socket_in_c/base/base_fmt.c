// Write to the character string
//====================================================================

fn Str8 fmt_sprintv_str8(Arena *arena, Str8 fmt, va_list vlist)
{
    va_list args;
    va_copy(args, vlist);
        U32 needed_bytes = fmt_vsnprintf(0, 0, (char const *)fmt.str, vlist) + 1;
        Str8 result = ZERO_STRUCT;
        result.str = arena_push_no_zero(arena, U8, needed_bytes);
        result.size = fmt_vsnprintf((char*)result.str, needed_bytes, (char const *)fmt.str, args);
        result.str[result.size] = 0;
    va_end(args);
    return(result);
}

fn Str8 fmt_sprintf_str8(Arena *arena, Str8 fmt, ...)
{
    va_list args;
    va_start(args, fmt);
        Str8 result = fmt_sprintv_str8(arena, fmt, args);
    va_end(args);
    return(result);
}

// File Print
//====================================================================

fn void fmt_vfprintf_str8(Os_File fd, Str8 fmt, va_list vlist)
{
    Temp temp = temp_begin(0, 0);
    Str8 result = fmt_sprintv_str8(temp.arena, fmt, vlist);
    os_write_str8(fd, result);
    temp_end(temp);
}

fn void fmt_fprintf_str8(Os_File fd, Str8 fmt, ...)
{
    va_list args;
    va_start(args, fmt);
        fmt_vfprintf_str8(fd, fmt, args);
    va_end(args);
}

fn void fmt_fprintf(Os_File fd, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
        fmt_vfprintf_str8(fd, str8_lit(fmt), args);
    va_end(args);
}

// Standard Ouput Print
//====================================================================

fn void fmt_printv_str8(Str8 fmt, va_list vlist)
{
    fmt_vfprintf_str8(OS_STDOUT, fmt, vlist);
}

fn void fmt_printf_str8(Str8 fmt, ...)
{
    va_list args;
    va_start(args, fmt);
        fmt_printv_str8(fmt, args);
    va_end(args);
}

fn void fmt_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
        fmt_printv_str8(str8_lit(fmt), args);
    va_end(args);
}

// Print Error
//====================================================================

fn void fmt_eprintv_str8(Str8 fmt, va_list vlist)
{
    fmt_vfprintf_str8(OS_STDERR, fmt, vlist);
}

fn void fmt_eprintf_str8(Str8 fmt, ...)
{
    va_list args;
    va_start(args, fmt);
        fmt_eprintv_str8(fmt, args);
    va_end(args);
}

fn void fmt_eprintf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
        fmt_eprintv_str8(str8_lit(fmt), args);
    va_end(args);
}
