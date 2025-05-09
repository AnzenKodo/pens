// Arena Creation/Destruction functions
//====================================================================

fn Arena *arena_alloc_(ArenaParams *params)
{
    U64 reserve_size = params->reserve_size;
    U64 commit_size = params->commit_size;
    reserve_size = AlignPow2(reserve_size, LINUX_PAGE_SIZE);
    commit_size  = AlignPow2(commit_size,  LINUX_PAGE_SIZE);

    void *base = params->optional_backing_buffer;
    if(base == 0)
    {
        base = os_memory_alloc(reserve_size);
        os_memory_commit(base, commit_size);
    }

    Arena *arena = (Arena *)base;
    arena->current = arena;
    arena->commit_size = params->commit_size;
    arena->reserve_size = params->reserve_size;
    arena->base_pos = 0;
    arena->pos = ARENA_HEADER_SIZE;
    arena->commit = commit_size;
    arena->reserve = reserve_size;

    AsanPoisonMemoryRegion(base, commit_size);
    AsanUnpoisonMemoryRegion(base, ARENA_HEADER_SIZE);
    return arena;
}

fn void arena_free(Arena *arena)
{
    for(Arena *n = arena->current, *prev = 0; n != 0; n = prev)
    {
        prev = n->prev;
        os_memory_free(n, n->reserve);
    }
}

// Arena Push/Pop functions
//====================================================================

fn void *arena_push_size(Arena *arena, U64 size, U64 align)
{
    Arena *current = arena->current;
    U64 pos_pre = AlignPow2(current->pos, align);
    U64 pos_post = pos_pre + size;

    if(current->reserve < pos_post)
    {
        Arena *new_block = 0;

        if(new_block == 0)
        {
            U64 reserve_size = current->reserve_size;
            U64 commit_size = current->commit_size;
            if(size + ARENA_HEADER_SIZE > reserve_size)
            {
              reserve_size = AlignPow2(size + ARENA_HEADER_SIZE, align);
              commit_size = AlignPow2(size + ARENA_HEADER_SIZE, align);
            }
            new_block = arena_alloc(
                .reserve_size = reserve_size, .commit_size  = commit_size
            );
        }

        new_block->base_pos = current->base_pos + current->reserve;
        SLLStackPush_N(arena->current, new_block, prev);

        current = new_block;
        pos_pre = AlignPow2(current->pos, align);
        pos_post = pos_pre + size;
    }

    // commit new pages, if needed
    if(current->commit < pos_post)
    {
        U64 commit_post_aligned = pos_post + current->commit_size-1;
        commit_post_aligned -= commit_post_aligned%current->commit_size;
        U64 commit_post_clamped = ClampTop(commit_post_aligned, current->reserve);
        U64 commit_size = commit_post_clamped - current->commit;
        U8 *commit_ptr = (U8 *)current + current->commit;
        os_memory_commit(commit_ptr, commit_size);
        current->commit = commit_post_clamped;
    }

    // push onto current block
    void *result = 0;
    if(current->commit >= pos_post)
    {
        result = (U8 *)current+pos_pre;
        current->pos = pos_post;
        AsanUnpoisonMemoryRegion(result, size);
    }

    return result;
}

fn U64 arena_pos(Arena *arena)
{
    Arena *current = arena->current;
    U64 pos = current->base_pos + current->pos;
    return pos;
}

fn void arena_pop_to(Arena *arena, U64 pos)
{
    U64 big_pos = ClampBot(ARENA_HEADER_SIZE, pos);
    Arena *current = arena->current;

    for(Arena *prev = 0; current->base_pos >= big_pos; current = prev)
    {
        prev = current->prev;
        os_memory_free(current, current->reserve);
    }

    arena->current = current;
    U64 new_pos = big_pos - current->base_pos;
    AssertAlways(new_pos <= current->pos);
    AsanPoisonMemoryRegion((U8*)current + new_pos, (current->pos - new_pos));
    current->pos = new_pos;
}

// Arena Push/Pop helpers
//====================================================================

fn void arena_clear(Arena *arena)
{
    arena_pop_to(arena, 0);
}

fn void arena_pop(Arena *arena, U64 amt)
{
    U64 pos_old = arena_pos(arena);
    U64 pos_new = pos_old;
    if(amt < pos_old)
    {
        pos_new = pos_old - amt;
    }
    arena_pop_to(arena, pos_new);
}

// Temporary Arena
//====================================================================

fn Temp temp_begin_init(Arena *arena)
{
    U64 pos = arena_pos(arena);
    Temp temp = {arena, pos};
    return temp;
}

fn void temp_end(Temp temp)
{
    arena_pop_to(temp.arena, temp.pos);
}
