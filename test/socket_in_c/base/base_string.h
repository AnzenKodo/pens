#ifndef BASE_STRING_H
#define BASE_STRING_H

// String Types
//====================================================================

typedef struct Str8 {
    U8 *str;
    U64 size;
} Str8;

typedef struct Str16 {
    U16 *str;
    U64 size;
} Str16;

typedef struct str32 {
    U32 *str;
    U64 size;
} Str32;

typedef U32 StrMatchFlags;
enum {
    StrMatchFlag_CaseInsensitive  = (1 << 0),
    StrMatchFlag_RightSideSloppy  = (1 << 1),
    StrMatchFlag_SlashInsensitive = (1 << 2),
};

// String Constructors
//====================================================================

#define str8_lit(S)  str8((U8*)(S), sizeof(S) - 1)
#define str8_lit_comp(S) {(U8*)(S), sizeof(S) - 1,}
#define str8_varg(S) ((S).str), (I32)((S).size),

// C-String Measurement
//====================================================================

fn U64 cstr8_len(U8 *c);
fn U64 cstr16_len(U16 *c);
fn U64 cstr32_len(U32 *c);

// Character Classification & Conversion Functions
//====================================================================

fn bool char_is_slash(U8 c);
fn bool char_is_upper(U8 c);
fn bool char_is_lower(U8 c);
fn U8 char_to_lower(U8 c);
fn U8 char_to_upper(U8 c);
fn U8 char_to_correct_slash(U8 c);

// String Constructors
//====================================================================

fn Str8  str8(U8 *str, U64 size);
fn Str8  str8_range(U8 *first, U8 *one_past_last);
fn Str8  str8_zero(void);
fn Str16 str16(U16 *str, U64 size);
fn Str16 str16_zero(void);
fn Str32 str32(U32 *str, U64 size);
fn Str32 str32_zero(void);
fn Str8  str8_cstr(char *c);
fn Str16 str16_cstr(U16 *c);
fn Str32 str32_cstr(U32 *c);

// String Slicing
//====================================================================

fn Str8 str8_skip(Str8 str, U64 amt);
fn Str8 str8_postfix(Str8 str, U64 size);

// String Matching
//====================================================================

fn bool str8_match(Str8 a, Str8 b, StrMatchFlags flags);
fn U64 str8_find_needle(Str8 string, U64 start_pos, Str8 needle, StrMatchFlags flags);
fn bool str8_ends_with(Str8 string, Str8 end, StrMatchFlags flags);

#endif // BASE_STRING_H
