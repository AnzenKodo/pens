// ak: Memory Operation Functions
//====================================================================

fn inline void *mem_set(void *dest, U8 c, ISize n) {
    U8 *s = cast(U8 *)dest;
    ISize k;
    U32 c32 = ((U32)-1)/255 * c;

    if (dest == NULL) {
        return NULL;
    }

    if (n == 0) { return dest; }
    s[0] = s[n-1] = c;
    if (n < 3) { return dest; }
    s[1] = s[n-2] = c;
    s[2] = s[n-3] = c;
    if (n < 7) { return dest; }
    s[3] = s[n-4] = c;
    if (n < 9) { return dest; }

    k = -cast(IPtr)s & 3;
    s += k;
    n -= k;
    n &= -4;

    *cast(U32 *)(s+0) = c32;
    *cast(U32 *)(s+n-4) = c32;
    if (n < 9) { return dest; }
    *cast(U32 *)(s +  4)    = c32;
    *cast(U32 *)(s +  8)    = c32;
    *cast(U32 *)(s+n-12) = c32;
    *cast(U32 *)(s+n- 8) = c32;
    if (n < 25) { return dest; }
    *cast(U32 *)(s + 12) = c32;
    *cast(U32 *)(s + 16) = c32;
    *cast(U32 *)(s + 20) = c32;
    *cast(U32 *)(s + 24) = c32;
    *cast(U32 *)(s+n-28) = c32;
    *cast(U32 *)(s+n-24) = c32;
    *cast(U32 *)(s+n-20) = c32;
    *cast(U32 *)(s+n-16) = c32;

    k = 24 + (cast(UPtr)s & 4);
    s += k;
    n -= k;

    {
        U64 c64 = (cast(U64)c32 << 32) | c32;
        while (n > 31) {
            *cast(U64 *)(s+0) = c64;
            *cast(U64 *)(s+8) = c64;
            *cast(U64 *)(s+16) = c64;
            *cast(U64 *)(s+24) = c64;

            n -= 32;
            s += 32;
        }
    }

    return dest;
}

fn inline I32 mem_cmp(void const *s1, void const *s2, ISize size)
{
    U8 const *s1p8 = cast(U8 const *)s1;
    U8 const *s2p8 = cast(U8 const *)s2;

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    while (size--) {
        if (*s1p8 != *s2p8) {
            return (*s1p8 - *s2p8);
        }
        s1p8++, s2p8++;
    }
    return 0;
}

fn inline void *mem_copy(void *dest, void const *source, ISize n)
{
#if defined(_MSC_VER)
    if (dest == NULL) {
        return NULL;
    }
    // TODO: Is this good enough?
    __movsb(cast(U8 *)dest, cast(U8 *)source, n);
// #elif defined(GB_SYSTEM_OSX) || defined(GB_SYSTEM_UNIX)
    // NOTE: I assume there's a reason this isn't being used elsewhere,
    //   but casting pointers as arguments to an __asm__ call is considered an
    //   error on MacOS and (I think) Linux
    // TODO: Figure out how to refactor the asm code so it works on MacOS,
    //   since this is probably not the way the author intended this to work.
    // memcpy(dest, source, n);
#elif defined(CPU_X86)
    if (dest == NULL) {
        return NULL;
    }

    void *dest_copy = dest;
    __asm__ __volatile__("rep movsb" : "+D"(dest_copy), "+S"(source), "+c"(n) : : "memory");
#else
    U8 *d = cast(U8 *)dest;
    U8 const *s = cast(U8 const *)source;
    U32 w, x;

    if (dest == NULL) {
        return NULL;
    }

    for (; cast(UPtr)s % 4 && n; n--) {
        *d++ = *s++;
    }

    if (cast(UPtr)d % 4 == 0) {
        for (; n >= 16;
             s += 16, d += 16, n -= 16) {
            *cast(U32 *)(d+ 0) = *cast(U32 *)(s+ 0);
            *cast(U32 *)(d+ 4) = *cast(U32 *)(s+ 4);
            *cast(U32 *)(d+ 8) = *cast(U32 *)(s+ 8);
            *cast(U32 *)(d+12) = *cast(U32 *)(s+12);
        }
        if (n & 8) {
            *cast(U32 *)(d+0) = *cast(U32 *)(s+0);
            *cast(U32 *)(d+4) = *cast(U32 *)(s+4);
            d += 8;
            s += 8;
        }
        if (n&4) {
            *cast(U32 *)(d+0) = *cast(U32 *)(s+0);
            d += 4;
            s += 4;
        }
        if (n&2) {
            *d++ = *s++; *d++ = *s++;
        }
        if (n&1) {
            *d = *s;
        }
        return dest;
    }

    if (n >= 32) {
    #if __BYTE_ORDER == __BIG_ENDIAN
    #define LS <<
    #define RS >>
    #else
    #define LS >>
    #define RS <<
    #endif
        switch (cast(UPtr)d % 4) {
        case 1: {
            w = *cast(U32 *)s;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            n -= 3;
            while (n > 16) {
                x = *cast(U32 *)(s+1);
                *cast(U32 *)(d+0)  = (w LS 24) | (x RS 8);
                w = *cast(U32 *)(s+5);
                *cast(U32 *)(d+4)  = (x LS 24) | (w RS 8);
                x = *cast(U32 *)(s+9);
                *cast(U32 *)(d+8)  = (w LS 24) | (x RS 8);
                w = *cast(U32 *)(s+13);
                *cast(U32 *)(d+12) = (x LS 24) | (w RS 8);

                s += 16;
                d += 16;
                n -= 16;
            }
        } break;
        case 2: {
            w = *cast(U32 *)s;
            *d++ = *s++;
            *d++ = *s++;
            n -= 2;
            while (n > 17) {
                x = *cast(U32 *)(s+2);
                *cast(U32 *)(d+0)  = (w LS 16) | (x RS 16);
                w = *cast(U32 *)(s+6);
                *cast(U32 *)(d+4)  = (x LS 16) | (w RS 16);
                x = *cast(U32 *)(s+10);
                *cast(U32 *)(d+8)  = (w LS 16) | (x RS 16);
                w = *cast(U32 *)(s+14);
                *cast(U32 *)(d+12) = (x LS 16) | (w RS 16);

                s += 16;
                d += 16;
                n -= 16;
            }
        } break;
        case 3: {
            w = *cast(U32 *)s;
            *d++ = *s++;
            n -= 1;
            while (n > 18) {
                x = *cast(U32 *)(s+3);
                *cast(U32 *)(d+0)  = (w LS 8) | (x RS 24);
                w = *cast(U32 *)(s+7);
                *cast(U32 *)(d+4)  = (x LS 8) | (w RS 24);
                x = *cast(U32 *)(s+11);
                *cast(U32 *)(d+8)  = (w LS 8) | (x RS 24);
                w = *cast(U32 *)(s+15);
                *cast(U32 *)(d+12) = (x LS 8) | (w RS 24);

                s += 16;
                d += 16;
                n -= 16;
            }
        } break;
        default: break; // NOTE: Do nowt!
        }
    #undef LS
    #undef RS
        if (n & 16) {
            *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
            *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
            *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
            *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
        }
        if (n & 8) {
            *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
            *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
        }
        if (n & 4) {
            *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
        }
        if (n & 2) {
            *d++ = *s++; *d++ = *s++;
        }
        if (n & 1) {
            *d = *s;
        }
    }

#endif
    return dest;
}

fn inline void *mem_move(void *dest, void const *source, ISize n)
{
    U8 *d = cast(U8 *)dest;
    U8 const *s = cast(U8 const *)source;

    if (dest == NULL) {
        return NULL;
    }

    if (d == s) {
        return d;
    }
    if (s+n <= d || d+n <= s) { // NOTE: Non-overlapping
        return mem_copy(d, s, n);
    }

    if (d < s) {
        if (cast(UPtr)s % sizeof(ISize) == cast(UPtr)d % sizeof(ISize)) {
            while (cast(UPtr)d % sizeof(ISize)) {
                if (!n--) return dest;
                *d++ = *s++;
            }
            while (n >= (ISize)sizeof(ISize)) {
                *cast(ISize *)d = *cast(ISize *)s;
                n -= sizeof(ISize);
                d += sizeof(ISize);
                s += sizeof(ISize);
            }
        }
        for (; n; n--) *d++ = *s++;
    } else {
        if ((cast(UPtr)s % sizeof(ISize)) == (cast(UPtr)d % sizeof(ISize))) {
            while (cast(UPtr)(d+n) % sizeof(ISize)) {
                if (!n--)
                    return dest;
                d[n] = s[n];
            }
            while (n >= (ISize)sizeof(ISize)) {
                n -= sizeof(ISize);
                *cast(ISize *)(d+n) = *cast(ISize *)(s+n);
            }
        }
        while (n) n--, d[n] = s[n];
    }

    return dest;
}
