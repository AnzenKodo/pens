// From: https://gemini.google.com/app/8115ee43189ef763

#ifndef UI_CORE_H
#define UI_CORE_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*=============================================================================
 * BASE TYPES & UTILS
 *===========================================================================*/

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t   S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;
typedef float    F32;
typedef double   F64;
typedef uint8_t  B8;
typedef uint32_t B32;

#define MemoryZero(ptr, size) memset(ptr, 0, size)
#define MemoryZeroStruct(ptr) MemoryZero(ptr, sizeof(*(ptr)))
#define MemoryCopy(dst, src, size) memcpy(dst, src, size)
#define Assert(c) if (!(c)) { *(volatile int *)0 = 0; }
#define ArrayCount(a) (sizeof(a) / sizeof((a)[0]))

#define Min(a, b) (((a)<(b))?(a):(b))
#define Max(a, b) (((a)>(b))?(a):(b))
#define Clamp(a, x, b) (((x)<(a))?(a):((b)<(x))?(b):(x))

typedef struct String8 {
    U8 *str;
    U64 size;
} String8;

#define Str8Lit(s) (String8){(U8 *)(s), sizeof(s)-1}

typedef struct V2 {
    F32 x, y;
} V2;

typedef struct V4 {
    F32 r, g, b, a;
} V4;

typedef struct Rect {
    V2 p0, p1;
} Rect;

typedef struct Arena {
    U8 *base;
    U64 size;
    U64 pos;
    U64 commit_pos;
} Arena;

static Arena* ArenaAlloc(U64 size) {
    Arena *arena = (Arena *)malloc(sizeof(Arena) + size);
    arena->base = (U8 *)(arena + 1);
    arena->size = size;
    arena->pos = 0;
    arena->commit_pos = 0;
    return arena;
}

static void* ArenaPush(Arena *arena, U64 size) {
    void *result = 0;
    if (arena->pos + size <= arena->size) {
        result = arena->base + arena->pos;
        arena->pos += size;
    }
    return result;
}

static void ArenaClear(Arena *arena) {
    arena->pos = 0;
}

#define PushArray(arena, type, count) (type *)ArenaPush(arena, sizeof(type) * (count))
#define PushStruct(arena, type) PushArray(arena, type, 1)

/*=============================================================================
 * UI TYPES & ENUMS
 *===========================================================================*/

typedef U64 UI_Key;

#define UI_KEY_NULL 0

typedef enum Axis2 {
    Axis2_X = 0,
    Axis2_Y = 1,
    Axis2_COUNT = 2
} Axis2;

typedef enum UI_SizeKind {
    UI_SizeKind_Null,
    UI_SizeKind_Pixels,
    UI_SizeKind_TextContent,
    UI_SizeKind_PercentOfParent,
    UI_SizeKind_ChildrenSum
} UI_SizeKind;

typedef struct UI_Size {
    UI_SizeKind kind;
    F32 value;
    F32 strictness;
} UI_Size;

#define UI_Pixels(v, s) (UI_Size){UI_SizeKind_Pixels, v, s}
#define UI_TextContent(s) (UI_Size){UI_SizeKind_TextContent, 0.0f, s}
#define UI_Pct(v, s) (UI_Size){UI_SizeKind_PercentOfParent, v, s}
#define UI_ChildrenSum(s) (UI_Size){UI_SizeKind_ChildrenSum, 0.0f, s}

typedef U64 UI_BoxFlags;
enum {
    UI_BoxFlag_Clickable             = (1<<0),
    UI_BoxFlag_ViewScroll            = (1<<1),
    UI_BoxFlag_DrawText              = (1<<2),
    UI_BoxFlag_DrawBorder            = (1<<3),
    UI_BoxFlag_DrawBackground        = (1<<4),
    UI_BoxFlag_DrawDropShadow        = (1<<5),
    UI_BoxFlag_Clip                  = (1<<6),
    UI_BoxFlag_HotAnimation          = (1<<7),
    UI_BoxFlag_ActiveAnimation       = (1<<8),
    UI_BoxFlag_FloatingX             = (1<<9),
    UI_BoxFlag_FloatingY             = (1<<10),
    UI_BoxFlag_FixedWidth            = (1<<11),
    UI_BoxFlag_FixedHeight           = (1<<12),
};

typedef struct UI_Box UI_Box;
struct UI_Box {
    UI_Box *hash_next;
    UI_Box *hash_prev;

    UI_Box *first;
    UI_Box *last;
    UI_Box *next;
    UI_Box *prev;
    UI_Box *parent;
    
    U64 child_count;

    UI_Key key;
    UI_BoxFlags flags;
    String8 string;

    UI_Size pref_size[Axis2_COUNT];
    Axis2 child_layout_axis;

    F32 calc_size[Axis2_COUNT];
    F32 calc_rel_position[Axis2_COUNT];
    Rect rect;
    
    V2 scroll;
    V2 target_scroll;
    
    F32 hot_t;
    F32 active_t;

    V4 bg_color;
    V4 text_color;
    V4 border_color;

    U64 last_frame_touched_index;
};

typedef struct UI_Signal {
    UI_Box *box;
    V2 mouse_pos;
    B32 hovered;
    B32 clicked;
    B32 double_clicked;
    B32 pressed;
    B32 released;
    B32 dragging;
} UI_Signal;

/*=============================================================================
 * UI STACKS
 *===========================================================================*/

#define UI_STACK_DECL(Type, Name) \
    typedef struct UI_##Name##Node UI_##Name##Node; \
    struct UI_##Name##Node { UI_##Name##Node *next; Type v; }; \
    Type UI_Push##Name(Type v); \
    Type UI_Pop##Name(void); \
    Type UI_Top##Name(void);

UI_STACK_DECL(UI_Box*, Parent)
UI_STACK_DECL(Axis2, ChildLayoutAxis)
UI_STACK_DECL(UI_Size, Width)
UI_STACK_DECL(UI_Size, Height)
UI_STACK_DECL(V4, BgColor)
UI_STACK_DECL(V4, TextColor)

/*=============================================================================
 * UI STATE
 *===========================================================================*/

typedef struct UI_State UI_State;
struct UI_State {
    Arena *build_arena;
    
    UI_Box **box_hash;
    U64 box_hash_size;

    UI_Box *root;

    UI_Key hot_key;
    UI_Key active_key;

    U64 frame_index;

    V2 mouse_pos;
    B32 mouse_down;
    B32 mouse_pressed;
    B32 mouse_released;

    F32 dt;

    UI_ParentNode *parent_stack;
    UI_ChildLayoutAxisNode *child_layout_axis_stack;
    UI_WidthNode *width_stack;
    UI_HeightNode *height_stack;
    UI_BgColorNode *bg_color_stack;
    UI_TextColorNode *text_color_stack;

    UI_Box *parent_top;
    Axis2 child_layout_axis_top;
    UI_Size width_top;
    UI_Size height_top;
    V4 bg_color_top;
    V4 text_color_top;
};

static UI_State *ui_state = 0;

/*=============================================================================
 * UI SYSTEM API
 *===========================================================================*/

void UI_Init(void);
void UI_BeginBuild(F32 dt, V2 mouse_pos, B32 mouse_down, B32 mouse_pressed, B32 mouse_released);
void UI_EndBuild(void);
UI_Box* UI_BoxMake(UI_BoxFlags flags, String8 string);
UI_Signal UI_SignalFromBox(UI_Box *box);
void UI_Layout(void);

#define UI_Parent(v) for (int _i = (UI_PushParent(v), 0); _i < 1; _i++, UI_PopParent())
#define UI_ChildLayoutAxis(v) for (int _i = (UI_PushChildLayoutAxis(v), 0); _i < 1; _i++, UI_PopChildLayoutAxis())
#define UI_Width(v) for (int _i = (UI_PushWidth(v), 0); _i < 1; _i++, UI_PopWidth())
#define UI_Height(v) for (int _i = (UI_PushHeight(v), 0); _i < 1; _i++, UI_PopHeight())
#define UI_BgColor(v) for (int _i = (UI_PushBgColor(v), 0); _i < 1; _i++, UI_PopBgColor())

/*=============================================================================
 * IMPLEMENTATION
 *===========================================================================*/

#define UI_STACK_IMPL(Type, Name, LowerName) \
    Type UI_Push##Name(Type v) { \
        UI_##Name##Node *node = PushStruct(ui_state->build_arena, UI_##Name##Node); \
        node->v = v; \
        node->next = ui_state->LowerName##_stack; \
        ui_state->LowerName##_stack = node; \
        ui_state->LowerName##_top = v; \
        return v; \
    } \
    Type UI_Pop##Name(void) { \
        Type popped = ui_state->LowerName##_top; \
        ui_state->LowerName##_stack = ui_state->LowerName##_stack->next; \
        if (ui_state->LowerName##_stack) { \
            ui_state->LowerName##_top = ui_state->LowerName##_stack->v; \
        } else { \
            MemoryZeroStruct(&ui_state->LowerName##_top); \
        } \
        return popped; \
    } \
    Type UI_Top##Name(void) { return ui_state->LowerName##_top; }

UI_STACK_IMPL(UI_Box*, Parent, parent)
UI_STACK_IMPL(Axis2, ChildLayoutAxis, child_layout_axis)
UI_STACK_IMPL(UI_Size, Width, width)
UI_STACK_IMPL(UI_Size, Height, height)
UI_STACK_IMPL(V4, BgColor, bg_color)
UI_STACK_IMPL(V4, TextColor, text_color)

static UI_Key UI_HashFromString(UI_Key seed, String8 string) {
    UI_Key result = seed;
    for(U64 i = 0; i < string.size; i += 1) {
        result = ((result << 5) + result) + string.str[i];
    }
    return result;
}

static UI_Key UI_KeyFromString(UI_Key seed, String8 string) {
    UI_Key result = 0;
    if(string.size != 0) {
        String8 hash_part = string;
        for(U64 i = 0; i < string.size; i += 1) {
            if(string.str[i] == '#' && string.str[i+1] == '#') {
                hash_part.str = string.str + i + 2;
                hash_part.size = string.size - i - 2;
                break;
            }
        }
        result = UI_HashFromString(seed, hash_part);
    }
    return result;
}

void UI_Init(void) {
    ui_state = (UI_State*)malloc(sizeof(UI_State));
    MemoryZeroStruct(ui_state);
    ui_state->build_arena = ArenaAlloc(1024 * 1024 * 64);
    ui_state->box_hash_size = 4096;
    ui_state->box_hash = (UI_Box**)malloc(sizeof(UI_Box*) * ui_state->box_hash_size);
    MemoryZero(ui_state->box_hash, sizeof(UI_Box*) * ui_state->box_hash_size);
}

void UI_BeginBuild(F32 dt, V2 mouse_pos, B32 mouse_down, B32 mouse_pressed, B32 mouse_released) {
    ArenaClear(ui_state->build_arena);
    ui_state->frame_index += 1;
    ui_state->dt = dt;
    ui_state->mouse_pos = mouse_pos;
    ui_state->mouse_down = mouse_down;
    ui_state->mouse_pressed = mouse_pressed;
    ui_state->mouse_released = mouse_released;

    ui_state->parent_stack = 0;
    ui_state->child_layout_axis_stack = 0;
    ui_state->width_stack = 0;
    ui_state->height_stack = 0;
    ui_state->bg_color_stack = 0;
    ui_state->text_color_stack = 0;

    ui_state->parent_top = 0;
    ui_state->child_layout_axis_top = Axis2_Y;
    ui_state->width_top = UI_Pixels(0.f, 0.f);
    ui_state->height_top = UI_Pixels(0.f, 0.f);
    ui_state->bg_color_top = (V4){0,0,0,0};
    ui_state->text_color_top = (V4){1,1,1,1};

    ui_state->root = UI_BoxMake(0, Str8Lit("Root"));
    UI_PushParent(ui_state->root);
}

UI_Box* UI_BoxMake(UI_BoxFlags flags, String8 string) {
    UI_Key key = UI_KeyFromString(0, string);
    UI_Box *box = 0;

    if (key != UI_KEY_NULL) {
        U64 slot = key % ui_state->box_hash_size;
        for(UI_Box *b = ui_state->box_hash[slot]; b != 0; b = b->hash_next) {
            if(b->key == key) {
                box = b;
                break;
            }
        }
        if(box == 0) {
            box = (UI_Box*)malloc(sizeof(UI_Box));
            MemoryZeroStruct(box);
            box->key = key;
            box->hash_next = ui_state->box_hash[slot];
            if(ui_state->box_hash[slot]) {
                ui_state->box_hash[slot]->hash_prev = box;
            }
            ui_state->box_hash[slot] = box;
        }
    } else {
        box = PushStruct(ui_state->build_arena, UI_Box);
        MemoryZeroStruct(box);
    }

    box->flags = flags;
    box->string = string;
    box->last_frame_touched_index = ui_state->frame_index;

    box->first = box->last = box->next = box->prev = box->parent = 0;
    box->child_count = 0;

    box->pref_size[Axis2_X] = UI_TopWidth();
    box->pref_size[Axis2_Y] = UI_TopHeight();
    box->child_layout_axis = UI_TopChildLayoutAxis();
    box->bg_color = UI_TopBgColor();
    box->text_color = UI_TopTextColor();

    UI_Box *parent = UI_TopParent();
    if(parent != 0) {
        box->parent = parent;
        if(parent->last == 0) {
            parent->first = parent->last = box;
        } else {
            parent->last->next = box;
            box->prev = parent->last;
            parent->last = box;
        }
        parent->child_count += 1;
    }

    return box;
}

UI_Signal UI_SignalFromBox(UI_Box *box) {
    UI_Signal sig = {0};
    sig.box = box;
    
    B32 is_hovered = (ui_state->mouse_pos.x >= box->rect.p0.x && ui_state->mouse_pos.x <= box->rect.p1.x &&
                      ui_state->mouse_pos.y >= box->rect.p0.y && ui_state->mouse_pos.y <= box->rect.p1.y);
                      
    if(is_hovered && ui_state->active_key == UI_KEY_NULL) {
        ui_state->hot_key = box->key;
    }
    
    if(ui_state->hot_key == box->key || ui_state->active_key == box->key) {
        sig.hovered = is_hovered;
    }
    
    if(sig.hovered && ui_state->mouse_pressed) {
        ui_state->active_key = box->key;
        sig.pressed = 1;
    }
    
    if(ui_state->active_key == box->key) {
        sig.dragging = ui_state->mouse_down;
        if(ui_state->mouse_released) {
            ui_state->active_key = UI_KEY_NULL;
            sig.released = 1;
            if(sig.hovered) {
                sig.clicked = 1;
            }
        }
    }

    if(box->flags & UI_BoxFlag_HotAnimation) {
        F32 target = (ui_state->hot_key == box->key) ? 1.0f : 0.0f;
        box->hot_t += (target - box->hot_t) * (1.0f - expf(-20.0f * ui_state->dt));
    }

    if(box->flags & UI_BoxFlag_ActiveAnimation) {
        F32 target = (ui_state->active_key == box->key) ? 1.0f : 0.0f;
        box->active_t += (target - box->active_t) * (1.0f - expf(-20.0f * ui_state->dt));
    }

    return sig;
}

static F32 UI_TextContentSize(String8 str, Axis2 axis) {
    if (axis == Axis2_Y) return 16.0f;
    return str.size * 8.0f;
}

static void UI_LayoutSolveIndependentSizes(UI_Box *node, Axis2 axis) {
    switch (node->pref_size[axis].kind) {
        case UI_SizeKind_Pixels:
            node->calc_size[axis] = node->pref_size[axis].value;
            break;
        case UI_SizeKind_TextContent:
            node->calc_size[axis] = UI_TextContentSize(node->string, axis) + node->pref_size[axis].value;
            break;
        default: break;
    }

    for (UI_Box *child = node->first; child != 0; child = child->next) {
        UI_LayoutSolveIndependentSizes(child, axis);
    }
}

static void UI_LayoutSolveUpwardDependentSizes(UI_Box *node, Axis2 axis) {
    for (UI_Box *child = node->first; child != 0; child = child->next) {
        UI_LayoutSolveUpwardDependentSizes(child, axis);
    }

    if (node->pref_size[axis].kind == UI_SizeKind_ChildrenSum) {
        F32 sum = 0;
        for (UI_Box *child = node->first; child != 0; child = child->next) {
            if (!(child->flags & (UI_BoxFlag_FloatingX << axis))) {
                if (node->child_layout_axis == axis) {
                    sum += child->calc_size[axis];
                } else {
                    sum = Max(sum, child->calc_size[axis]);
                }
            }
        }
        node->calc_size[axis] = sum + node->pref_size[axis].value;
    }
}

static void UI_LayoutSolveDownwardDependentSizes(UI_Box *node, Axis2 axis) {
    for (UI_Box *child = node->first; child != 0; child = child->next) {
        if (child->pref_size[axis].kind == UI_SizeKind_PercentOfParent) {
            child->calc_size[axis] = node->calc_size[axis] * child->pref_size[axis].value;
        }
    }
    for (UI_Box *child = node->first; child != 0; child = child->next) {
        UI_LayoutSolveDownwardDependentSizes(child, axis);
    }
}

static void UI_LayoutCalculatePositions(UI_Box *node, Axis2 axis) {
    F32 cursor = 0;
    for (UI_Box *child = node->first; child != 0; child = child->next) {
        if (!(child->flags & (UI_BoxFlag_FloatingX << axis))) {
            child->calc_rel_position[axis] = cursor;
            if (node->child_layout_axis == axis) {
                cursor += child->calc_size[axis];
            }
        }
    }
    
    for (UI_Box *child = node->first; child != 0; child = child->next) {
        UI_LayoutCalculatePositions(child, axis);
    }
}

static void UI_LayoutFinalizeRects(UI_Box *node) {
    if (node->parent) {
        node->rect.p0.x = node->parent->rect.p0.x + node->calc_rel_position[Axis2_X] - node->parent->scroll.x;
        node->rect.p0.y = node->parent->rect.p0.y + node->calc_rel_position[Axis2_Y] - node->parent->scroll.y;
    } else {
        node->rect.p0.x = node->calc_rel_position[Axis2_X];
        node->rect.p0.y = node->calc_rel_position[Axis2_Y];
    }
    node->rect.p1.x = node->rect.p0.x + node->calc_size[Axis2_X];
    node->rect.p1.y = node->rect.p0.y + node->calc_size[Axis2_Y];

    for (UI_Box *child = node->first; child != 0; child = child->next) {
        UI_LayoutFinalizeRects(child);
    }
}

void UI_Layout(void) {
    for (Axis2 axis = (Axis2)0; axis < Axis2_COUNT; axis++) {
        UI_LayoutSolveIndependentSizes(ui_state->root, axis);
        UI_LayoutSolveUpwardDependentSizes(ui_state->root, axis);
        UI_LayoutSolveDownwardDependentSizes(ui_state->root, axis);
        UI_LayoutCalculatePositions(ui_state->root, axis);
    }
    UI_LayoutFinalizeRects(ui_state->root);
}

void UI_EndBuild(void) {
    UI_PopParent();
    UI_Layout();
    
    if(!ui_state->mouse_down) {
        ui_state->active_key = UI_KEY_NULL;
    }
    ui_state->hot_key = UI_KEY_NULL;
}

/*=============================================================================
 * BASIC WIDGETS
 *===========================================================================*/

UI_Signal UI_Button(String8 label) {
    UI_BoxFlags flags = UI_BoxFlag_Clickable | UI_BoxFlag_DrawBorder | UI_BoxFlag_DrawBackground | UI_BoxFlag_DrawText | UI_BoxFlag_HotAnimation | UI_BoxFlag_ActiveAnimation;
    
    UI_Box *box = 0;
    UI_Width(UI_TextContent(16.0f))
    UI_Height(UI_TextContent(8.0f))
    {
        box = UI_BoxMake(flags, label);
    }
    return UI_SignalFromBox(box);
}

void UI_Label(String8 label) {
    UI_BoxFlags flags = UI_BoxFlag_DrawText;
    UI_Width(UI_TextContent(0.0f))
    UI_Height(UI_TextContent(0.0f))
    {
        UI_BoxMake(flags, label);
    }
}

#endif // UI_CORE_H
