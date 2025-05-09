#ifndef BASE_MEM_H
#define BASE_MEM_H

// ak: Memory Operation Functions
//====================================================================

fn inline void *mem_set(void *dest, U8 c, ISize n);
fn inline I32 mem_cmp(void const *s1, void const *s2, ISize size);
fn inline void *mem_copy(void *dest, void const *source, ISize n);
fn inline void *mem_move(void *dest, void const *source, ISize n);

// ak: Memory Operation Macros
//====================================================================

#define MemZero(s,z)       mem_set((s),0,(z))
#define MemZeroStruct(s)   MemZero((s),sizeof(*(s)))
#define MemZeroArray(a)    MemZero((a),sizeof(a))
#define MemZeroTyped(m,c)  MemZero((m),sizeof(*(m))*(c))

#define MemMatch(a,b,z)         (mem_cmp((a),(b),(z)) == 0)
#define MemMatchStruct(a,b)     MemMatch((a),(b),sizeof(*(a)))
#define MemMatchArray(a,b)      MemMatch((a),(b),sizeof(a))

#define MemCopy(dst, src, size)    mem_copy((dst), (src), (size))
#define MemMove(dst, src, size)    mem_move((dst), (src), (size))

#endif // BASE_MEM_H
