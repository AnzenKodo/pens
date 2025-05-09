#ifndef BASE_THREAD_CONTEXT_H
#define BASE_THREAD_CONTEXT_H

// Types
//====================================================================

typedef struct TCTX {
    Arena *arenas[2];
    U8 thread_name[32];
    U64 thread_name_size;
    char *file_name;
    U64 line_number;
} TCTX;

// Macros
//====================================================================

#define tctx_write_this_srcloc() tctx_write_srcloc(__FILE__, __LINE__)


// Thread Context Functions
//====================================================================

fn void      tctx_init_and_equip(TCTX *tctx);
fn void      tctx_release(void);
fn TCTX*     tctx_get_equipped(void);

fn Arena*    tctx_get_scratch(Arena **conflicts, U64 countt);

fn void      tctx_set_thread_name(Str8 name);
fn Str8      tctx_get_thread_name(void);

fn void      tctx_write_srcloc(char *file_name, U64 line_number);
fn void      tctx_read_srcloc(char **file_name, U64 *line_number);

#endif // BASE_THREAD_CONTEXT_H
