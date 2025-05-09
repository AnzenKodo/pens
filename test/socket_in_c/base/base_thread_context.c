// Thread Context Functions
//====================================================================

C_LINKAGE thread_static TCTX* tctx_thread_local;
#if !BUILD_SUPPLEMENTARY_UNIT
thread_static TCTX* tctx_thread_local = 0;
#endif

fn void tctx_init_and_equip(TCTX *tctx){
    MemZeroStruct(tctx);
    Arena **arena_ptr = tctx->arenas;
    for (U64 i = 0; i < ArrayCount(tctx->arenas); i += 1, arena_ptr += 1){
        *arena_ptr = arena_alloc();
    }
    tctx_thread_local = tctx;
}

fn void tctx_release(void)
{
    for(U64 i = 0; i < ArrayCount(tctx_thread_local->arenas); i += 1)
    {
        arena_free(tctx_thread_local->arenas[i]);
    }
}

fn TCTX* tctx_get_equipped(void){
  return(tctx_thread_local);
}

fn Arena* tctx_get_scratch(Arena **conflicts, U64 count){
    TCTX *tctx = tctx_get_equipped();

    Arena *result = 0;
    Arena **arena_ptr = tctx->arenas;
    for (U64 i = 0; i < ArrayCount(tctx->arenas); i += 1, arena_ptr += 1){
    Arena **conflict_ptr = conflicts;
    I32 has_conflict = 0;
        for (U64 j = 0; j < count; j += 1, conflict_ptr += 1){
            if (*arena_ptr == *conflict_ptr){
                has_conflict = 1;
                break;
            }
        }
        if (!has_conflict){
            result = *arena_ptr;
            break;
        }
    }

    return(result);
}

fn void tctx_set_thread_name(Str8 string){
    TCTX *tctx = tctx_get_equipped();
    U64 size = ClampTop(string.size, sizeof(tctx->thread_name));
    MemMove(tctx->thread_name, string.str, size);
    tctx->thread_name_size = size;
}

fn Str8 tctx_get_thread_name(void){
    TCTX *tctx = tctx_get_equipped();
    Str8 result = str8(tctx->thread_name, tctx->thread_name_size);
    return(result);
}

fn void tctx_write_srcloc(char *file_name, U64 line_number){
    TCTX *tctx = tctx_get_equipped();
    tctx->file_name = file_name;
    tctx->line_number = line_number;
}

fn void tctx_read_srcloc(char **file_name, U64 *line_number){
    TCTX *tctx = tctx_get_equipped();
    *file_name = tctx->file_name;
    *line_number = tctx->line_number;
}
