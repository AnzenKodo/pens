#ifndef BASE_ARENA_H
#define BASE_ARENA_H

// Types
//====================================================================

typedef struct Arena Arena;
struct Arena
{
    Arena *prev;    // previous arena in chain
    Arena *current; // current arena in chain
    U64 commit_size;
    U64 reserve_size;
    U64 base_pos;
    U64 pos;
    U64 commit;
    U64 reserve;
};

typedef struct Temp Temp;
struct Temp
{
    Arena *arena;
    U64 pos;
};

// Defaults
//====================================================================

global U64 arena_default_reserve_size = MB(64);
global U64 arena_default_commit_size  = KB(64);

// Macros
//====================================================================

#define LINUX_PAGE_SIZE 4096
#define ARENA_HEADER_SIZE 128

#if LANG_C
    typedef struct ArenaParams ArenaParams;
    struct ArenaParams
    {
        U64 reserve_size;
        U64 commit_size;
        void *optional_backing_buffer;
    };
    #define arena_alloc(...) arena_alloc_(&(ArenaParams){.reserve_size = arena_default_reserve_size, .commit_size = arena_default_commit_size, __VA_ARGS__})
#else
    typedef struct ArenaParams ArenaParams;
    struct ArenaParams {
        U64 reserve_size = arena_default_reserve_size;
        U64 commit_size = arena_default_commit_size;
        void *optional_backing_buffer = NULL;
    };
    #define arena_alloc(...) [&]() { \
        ArenaParams params = {__VA_ARGS__}; \
        return arena_alloc_(&params); \
    }()
#endif

#define arena_push_no_zero_aligned(a, Type, c, align) cast(Type *)arena_push_size((a), sizeof(Type)*(c), (align))
#define arena_push_aligned(a, Type, c, align) cast(Type *)MemZero(arena_push_no_zero_aligned(a, Type, c, align), sizeof(Type)*(c))
#define arena_push_no_zero(a, Type, c) arena_push_no_zero_aligned(a, Type, c, Max(8, AlignOf(Type)))
#define arena_push(a, Type, c) arena_push_aligned(a, Type, c, Max(8, AlignOf(Type)))

#define temp_begin(conflicts, count) temp_begin_init(tctx_get_scratch((conflicts), (count)))

// Arena Creation/Destruction functions
//====================================================================

fn Arena *arena_alloc_(ArenaParams *params);
fn void arena_free(Arena *arena);

//// Arena Push/Pop functions
//====================================================================

fn void *arena_push_size(Arena *arena, U64 size, U64 align);
fn U64 arena_pos(Arena *arena);
fn void arena_pop_to(Arena *arena, U64 pos);

// Arena Push/Pop helpers
//====================================================================

fn void arena_clear(Arena *arena);
fn void arena_pop(Arena *arena, U64 amt);

// Temporary Arena
//====================================================================

fn Temp temp_begin_init(Arena *arena);
fn void temp_end(Temp temp);

#endif // BASE_ARENA_H
