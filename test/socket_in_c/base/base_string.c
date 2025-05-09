// C-String Measurement
//====================================================================

fn U64 cstr8_len(U8 *c) { U8 *p = c; for (;*p != 0; p += 1); return(p - c); }
fn U64 cstr16_len(U16 *c) { U16 *p = c; for (;*p != 0; p += 1); return(p - c); }
fn U64 cstr32_len(U32 *c) { U32 *p = c; for (;*p != 0; p += 1); return(p - c); }

// Character Classification & Conversion Functions
//====================================================================

fn bool char_is_slash(U8 c)         { return(c == '/' || c == '\\'); }
fn bool char_is_upper(U8 c)         { return('A' <= c && c <= 'Z'); }
fn bool char_is_lower(U8 c)         { return('a' <= c && c <= 'z'); }
fn U8 char_to_lower(U8 c)           { if (char_is_upper(c)) { c += ('a' - 'A'); } return(c); }
fn U8 char_to_upper(U8 c)           { if (char_is_lower(c)) { c += ('A' - 'a'); } return(c); }
fn U8 char_to_correct_slash(U8 c)   { if(char_is_slash(c)) { c = '/'; } return(c); }

// String Constructors
//====================================================================

fn Str8  str8(U8 *str, U64 size)                  { Str8 result = {str, size}; return(result); }
fn Str8  str8_range(U8 *first, U8 *one_past_last) { Str8 result = {first, (U64)(one_past_last - first)}; return(result); }
fn Str8  str8_zero(void)                          { Str8 result = ZERO_STRUCT; return(result); }
fn Str16 str16(U16 *str, U64 size)                { Str16 result = {str, size}; return(result); }
fn Str16 str16_zero(void)                         { Str16 result = ZERO_STRUCT; return(result); }
fn Str32 str32(U32 *str, U64 size)                { Str32 result = {str, size}; return(result); }
fn Str32 str32_zero(void)                         { Str32 result = ZERO_STRUCT; return(result); }
fn Str8  str8_cstr(char *c)                       { Str8 result = {(U8*)c, cstr8_len((U8*)c)}; return(result); }
fn Str16 str16_cstr(U16 *c)                       { Str16 result = {(U16*)c, cstr16_len((U16*)c)}; return(result); }
fn Str32 str32_cstr(U32 *c)                       { Str32 result = {(U32*)c, cstr32_len((U32*)c)}; return(result); }


// String Slicing
//====================================================================

fn Str8 str8_skip(Str8 str, U64 amt)
{
  amt = ClampTop(amt, str.size);
  str.str += amt;
  str.size -= amt;
  return(str);
}

fn Str8 str8_postfix(Str8 str, U64 size)
{
  size = ClampTop(size, str.size);
  str.str = (str.str + str.size) - size;
  str.size = size;
  return str;
}

// String Matching
//====================================================================

fn bool str8_match(Str8 a, Str8 b, StrMatchFlags flags)
{
    bool result = 0;
    if(a.size == b.size && flags == 0)
    {
        result = MemMatch(a.str, b.str, b.size);
    }
    else if(a.size == b.size || (flags & StrMatchFlag_RightSideSloppy))
    {
        I32 case_insensitive  = (flags & StrMatchFlag_CaseInsensitive);
        I32 slash_insensitive = (flags & StrMatchFlag_SlashInsensitive);
        U64 size              = Min(a.size, b.size);
        result = 1;
        for(U64 i = 0; i < size; i += 1)
        {
            U8 at = a.str[i];
            U8 bt = b.str[i];
            if(case_insensitive)
            {
                at = char_to_upper(at);
                bt = char_to_upper(bt);
            }
            if(slash_insensitive)
            {
                at = char_to_correct_slash(at);
                bt = char_to_correct_slash(bt);
            }
            if(at != bt)
            {
                result = 0;
                break;
            }
        }
    }
    return result;
}

fn U64 str8_find_needle(Str8 string, U64 start_pos, Str8 needle, StrMatchFlags flags){
    U8 *p = string.str + start_pos;
    U64 stop_offset = Max(string.size + 1, needle.size) - needle.size;
    U8 *stop_p = string.str + stop_offset;
    if (needle.size > 0){
        U8 *string_opl = string.str + string.size;
        Str8 needle_tail = str8_skip(needle, 1);
        StrMatchFlags adjusted_flags = flags | StrMatchFlag_RightSideSloppy;
        U8 needle_first_char_adjusted = needle.str[0];
        if(adjusted_flags & StrMatchFlag_CaseInsensitive){
            needle_first_char_adjusted = char_to_upper(needle_first_char_adjusted);
        }
        for (;p < stop_p; p += 1){
            U8 haystack_char_adjusted = *p;
            if(adjusted_flags & StrMatchFlag_CaseInsensitive){
                haystack_char_adjusted = char_to_upper(haystack_char_adjusted);
            }
            if (haystack_char_adjusted == needle_first_char_adjusted){
                if (str8_match(str8_range(p + 1, string_opl), needle_tail, adjusted_flags)){
                    break;
                }
            }
        }
    }
    U64 result = string.size;
    if (p < stop_p){
        result = (U64)(p - string.str);
    }
    return(result);
}

fn bool str8_ends_with(Str8 string, Str8 end, StrMatchFlags flags)
{
    Str8 postfix = str8_postfix(string, end.size);
    bool is_match = str8_match(end, postfix, flags);
    return is_match;
}
