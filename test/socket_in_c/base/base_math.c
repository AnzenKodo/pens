fn F32 lerp_f32(F32 a, F32 b, F32 t) { return a + (b - a)*t; }
fn I32 round_f32_to_i32(F32 a) { I32 result = (I32)(a + 0.5f); return result; }
fn U32 round_f32_to_u32(F32 a) { U32 result = (U32)(a + 0.5f); return result; }

//// Scalar Ops
////==================================================================

fn F32 round_f32(F32 x) { return (F32)((x >= 0.0f) ? floor_f32(x + 0.5f) : ceil_f32(x - 0.5f)); }
fn F32 floor_f32(F32 x) { return (F32)((x >= 0.0f) ? (int)x : (int)(x-0.9999999999999999f)); }
fn F32 ceil_f32(F32 x)  { return (F32)((x < 0) ? (int)x : ((int)x)+1); }

fn F32 sqrt_f32(F32 number)
{
    F32 Result;

#ifdef SIMD_SSE
    #ifdef COMPILER_TCC
        simde__m128 In = simde_mm_set_ss(number);
        simde__m128 Out = simde_mm_sqrt_ss(In);
        Result = simde_mm_cvtss_f32(Out);
    #else
        __m128 In = _mm_set_ss(number);
        __m128 Out = _mm_sqrt_ss(In);
        Result = _mm_cvtss_f32(Out);
    #endif
#elif defined(SIMD_NEON)
    float32x4_t In = vdupq_n_f32(number);
    float32x4_t Out = vsqrtq_f32(In);
    Result = vgetq_lane_f32(Out, 0);
#endif

    return Result;
}

fn F32 sin_f32(F32 a)
{
    local_persist F32 const a0 = +1.91059300966915117e-31f;
    local_persist F32 const a1 = +1.00086760103908896f;
    local_persist F32 const a2 = -1.21276126894734565e-2f;
    local_persist F32 const a3 = -1.38078780785773762e-1f;
    local_persist F32 const a4 = -2.67353392911981221e-2f;
    local_persist F32 const a5 = +2.08026600266304389e-2f;
    local_persist F32 const a6 = -3.03996055049204407e-3f;
    local_persist F32 const a7 = +1.38235642404333740e-4f;
    return a0 + a*(a1 + a*(a2 + a*(a3 + a*(a4 + a*(a5 + a*(a6 + a*a7))))));
}

fn F32 cos_f32(F32 a)
{
    local_persist F32 const a0 = +1.00238601909309722f;
    local_persist F32 const a1 = -3.81919947353040024e-2f;
    local_persist F32 const a2 = -3.94382342128062756e-1f;
    local_persist F32 const a3 = -1.18134036025221444e-1f;
    local_persist F32 const a4 = +1.07123798512170878e-1f;
    local_persist F32 const a5 = -1.86637164165180873e-2f;
    local_persist F32 const a6 = +9.90140908664079833e-4f;
    local_persist F32 const a7 = -5.23022132118824778e-14f;
    return a0 + a*(a1 + a*(a2 + a*(a3 + a*(a4 + a*(a5 + a*(a6 + a*a7))))));
}

fn F32 tan_f32(F32 radians)
{
    F32 rr = radians*radians;
    F32 a = 9.5168091e-03f;
    a *= rr;
    a += 2.900525e-03f;
    a *= rr;
    a += 2.45650893e-02f;
    a *= rr;
    a += 5.33740603e-02f;
    a *= rr;
    a += 1.333923995e-01f;
    a *= rr;
    a += 3.333314036e-01f;
    a *= rr;
    a += 1.0f;
    a *= radians;
    return a;
}

fn F32 pow_f32(F32 a, F32 b)
{
    I32 flipped = 0, e;
    F32 f, r = 1.0f;
    if (b < 0) {
        flipped = 1;
        b = -b;
    }

    e = (I32)b;
    f = exp_f32(b - e);

    while (e) {
        if (e & 1) r *= a;
        a *= a;
        e >>= 1;
    }

    r *= f;
    return flipped ? 1.0f/r : r;
}

fn F32 exp_f32(F32 a)
{
    union { F32 f; I32 i; } u, v;
    u.i = (I32)(6051102 * a + 1056478197);
    v.i = (I32)(1056478197 - 6051102 * a);
    return u.f / v.f;
}


fn F32 log_f32(F32 a)
{
  union { F32 f; I32 i; } u = {a};
  return (u.i - 1064866805) * 8.262958405176314e-8f; /* 1 / 12102203.0; */
}

fn F32 arctan_f32(F32 a)
{
    F32 u  = a*a;
    F32 u2 = u*u;
    F32 u3 = u2*u;
    F32 u4 = u3*u;
    F32 f  = 1.0f+0.33288950512027f*u-0.08467922817644f*u2+0.03252232640125f*u3-0.00749305860992f*u4;
    return a/f;
}

fn F32 arctan2_f32(F32 y, F32 x)
{
    if (Abs(x) > Abs(y)) {
        F32 a = arctan_f32(y/x);
        if (x > 0.0f) {
            return a;
        } else {
            return y > 0.0f ? a+MATH_TAU_OVER_2:a-MATH_TAU_OVER_2;
        }
    } else {
        F32 a = arctan_f32(x/y);
        if (x > 0.0f) {
            return y > 0.0f ? MATH_TAU_OVER_4-a:-MATH_TAU_OVER_4-a;
        } else {
            return y > 0.0f ? MATH_TAU_OVER_4+a:-MATH_TAU_OVER_4+a;
        }
    }
}

fn F32 arcsin_f32(F32 a) { return arctan2_f32(a, sqrt_f32((1.0f + a) * (1.0f - a))); }
fn F32 arccos_f32(F32 a) { return arctan2_f32(sqrt_f32((1.0f + a) * (1.0 - a)), a); }
fn F64 mix_1f64(F64 a, F64 b, F64 t) { F64 c = (a + (b-a) * Clamp(0.0, t, 1.0)); return c; }
fn F32 mix_1f32(F32 a, F32 b, F32 t) { F32 c = (a + (b-a) * Clamp(0.f, t, 1.f)); return c; }

//// Vector Ops
////==================================================================

fn Vec2F32 vec_2f32(F32 x, F32 y)                {Vec2F32 v = {x, y}; return v;}
fn Vec2F32 add_2f32(Vec2F32 a, Vec2F32 b)        {Vec2F32 c = {a.x+b.x, a.y+b.y}; return c;}
fn Vec2F32 sub_2f32(Vec2F32 a, Vec2F32 b)        {Vec2F32 c = {a.x-b.x, a.y-b.y}; return c;}
fn Vec2F32 mul_2f32(Vec2F32 a, Vec2F32 b)        {Vec2F32 c = {a.x*b.x, a.y*b.y}; return c;}
fn Vec2F32 div_2f32(Vec2F32 a, Vec2F32 b)        {Vec2F32 c = {a.x/b.x, a.y/b.y}; return c;}
fn Vec2F32 scale_2f32(Vec2F32 v, F32 s)          {Vec2F32 c = {v.x*s, v.y*s}; return c;}
fn F32 dot_2f32(Vec2F32 a, Vec2F32 b)            {F32 c = a.x*b.x + a.y*b.y; return c;}
fn F32 length_squared_2f32(Vec2F32 v)            {F32 c = v.x*v.x + v.y*v.y; return c;}
fn F32 length_2f32(Vec2F32 v)                    {F32 c = sqrt_f32(v.x*v.x + v.y*v.y); return c;}
fn Vec2F32 normalize_2f32(Vec2F32 v)             {v = scale_2f32(v, 1.f/length_2f32(v)); return v;}
fn Vec2F32 mix_2f32(Vec2F32 a, Vec2F32 b, F32 t)
{
    Vec2F32 c = {
        mix_1f32(a.x, b.x, t),
        mix_1f32(a.y, b.y, t)
    };
    return c;
}

fn Vec2I64 vec_2i64(I64 x, I64 y)                {Vec2I64 v = {x, y}; return v;}
fn Vec2I64 add_2i64(Vec2I64 a, Vec2I64 b)        {Vec2I64 c = {a.x+b.x, a.y+b.y}; return c;}
fn Vec2I64 sub_2i64(Vec2I64 a, Vec2I64 b)        {Vec2I64 c = {a.x-b.x, a.y-b.y}; return c;}
fn Vec2I64 mul_2i64(Vec2I64 a, Vec2I64 b)        {Vec2I64 c = {a.x*b.x, a.y*b.y}; return c;}
fn Vec2I64 div_2i64(Vec2I64 a, Vec2I64 b)        {Vec2I64 c = {a.x/b.x, a.y/b.y}; return c;}
fn Vec2I64 scale_2i64(Vec2I64 v, I64 s)          {Vec2I64 c = {v.x*s, v.y*s}; return c;}
fn I64 dot_2i64(Vec2I64 a, Vec2I64 b)            {I64 c = a.x*b.x + a.y*b.y; return c;}
fn I64 length_squared_2i64(Vec2I64 v)            {I64 c = v.x*v.x + v.y*v.y; return c;}
fn Vec2I64 mix_2i64(Vec2I64 a, Vec2I64 b, F32 t)
{
    Vec2I64 c = {
        (I64)mix_1f32((F32)a.x,
        (F32)b.x, t), (I64)mix_1f32((F32)a.y, (F32)b.y, t)
    };
    return c;
}

fn Vec2I32 vec_2i32(I32 x, I32 y)                {Vec2I32 v = {x, y}; return v;}
fn Vec2I32 add_2i32(Vec2I32 a, Vec2I32 b)        {Vec2I32 c = {a.x+b.x, a.y+b.y}; return c;}
fn Vec2I32 sub_2i32(Vec2I32 a, Vec2I32 b)        {Vec2I32 c = {a.x-b.x, a.y-b.y}; return c;}
fn Vec2I32 mul_2i32(Vec2I32 a, Vec2I32 b)        {Vec2I32 c = {a.x*b.x, a.y*b.y}; return c;}
fn Vec2I32 div_2i32(Vec2I32 a, Vec2I32 b)        {Vec2I32 c = {a.x/b.x, a.y/b.y}; return c;}
fn Vec2I32 scale_2i32(Vec2I32 v, I32 s)          {Vec2I32 c = {v.x*s, v.y*s}; return c;}
fn I32 dot_2i32(Vec2I32 a, Vec2I32 b)            {I32 c = a.x*b.x + a.y*b.y; return c;}
fn I32 length_squared_2i32(Vec2I32 v)            {I32 c = v.x*v.x + v.y*v.y; return c;}
fn Vec2I32 normalize_2i32(Vec2I32 v)             {v = scale_2i32(v, (I32)(1.f/length_2i32(v))); return v;}
fn I32 length_2i32(Vec2I32 v)
{
    I32 c = cast(I32)sqrt_f32(cast(F32)v.x*cast(F32)v.x + cast(F32)v.y*cast(F32)v.y);
    return c;
}
fn Vec2I32 mix_2i32(Vec2I32 a, Vec2I32 b, F32 t)
{
    Vec2I32 c = {
        (I32)mix_1f32((F32)a.x, (F32)b.x, t),
        (I32)mix_1f32((F32)a.y, (F32)b.y, t)
    };
    return c;
}

fn Vec2I16 vec_2i16(I16 x, I16 y)                {Vec2I16 v = {x, y}; return v;}
fn Vec2I16 add_2i16(Vec2I16 a, Vec2I16 b)        {Vec2I16 c = {(I16)(a.x+b.x), (I16)(a.y+b.y)}; return c;}
fn Vec2I16 sub_2i16(Vec2I16 a, Vec2I16 b)        {Vec2I16 c = {(I16)(a.x-b.x), (I16)(a.y-b.y)}; return c;}
fn Vec2I16 mul_2i16(Vec2I16 a, Vec2I16 b)        {Vec2I16 c = {(I16)(a.x*b.x), (I16)(a.y*b.y)}; return c;}
fn Vec2I16 div_2i16(Vec2I16 a, Vec2I16 b)        {Vec2I16 c = {(I16)(a.x/b.x), (I16)(a.y/b.y)}; return c;}
fn Vec2I16 scale_2i16(Vec2I16 v, I16 s)          {Vec2I16 c = {(I16)(v.x*s), (I16)(v.y*s)}; return c;}
fn I16 dot_2i16(Vec2I16 a, Vec2I16 b)            {I16 c = a.x*b.x + a.y*b.y; return c;}
fn I16 length_squared_2i16(Vec2I16 v)            {I16 c = v.x*v.x + v.y*v.y; return c;}
fn I16 length_2i16(Vec2I16 v)                    {I16 c = (I16)sqrt_f32((F32)(v.x*v.x + v.y*v.y)); return c;}
fn Vec2I16 normalize_2I16(Vec2I16 v)             {v = scale_2i16(v, (I16)(1.f/length_2i16(v))); return v;}
fn Vec2I16 mix_2i16(Vec2I16 a, Vec2I16 b, F32 t) {
    Vec2I16 c = {
        (I16)mix_1f32((F32)a.x, (F32)b.x, t),
        (I16)mix_1f32((F32)a.y, (F32)b.y, t)
    };
    return c;
}

fn Vec3F32 vec_3f32(F32 x, F32 y, F32 z)         {Vec3F32 v = {x, y, z}; return v;}
fn Vec3F32 add_3f32(Vec3F32 a, Vec3F32 b)        {Vec3F32 c = {a.x+b.x, a.y+b.y, a.z+b.z}; return c;}
fn Vec3F32 sub_3f32(Vec3F32 a, Vec3F32 b)        {Vec3F32 c = {a.x-b.x, a.y-b.y, a.z-b.z}; return c;}
fn Vec3F32 mul_3f32(Vec3F32 a, Vec3F32 b)        {Vec3F32 c = {a.x*b.x, a.y*b.y, a.z*b.z}; return c;}
fn Vec3F32 div_3f32(Vec3F32 a, Vec3F32 b)        {Vec3F32 c = {a.x/b.x, a.y/b.y, a.z/b.z}; return c;}
fn Vec3F32 scale_3f32(Vec3F32 v, F32 s)          {Vec3F32 c = {v.x*s, v.y*s, v.z*s}; return c;}
fn F32 dot_3f32(Vec3F32 a, Vec3F32 b)            {F32 c = a.x*b.x + a.y*b.y + a.z*b.z; return c;}
fn F32 length_squared_3f32(Vec3F32 v)            {F32 c = v.x*v.x + v.y*v.y + v.z*v.z; return c;}
fn F32 length_3f32(Vec3F32 v)                    {F32 c = sqrt_f32(v.x*v.x + v.y*v.y + v.z*v.z); return c;}
fn Vec3F32 normalize_3f32(Vec3F32 v)             {v = scale_3f32(v, 1.f/length_3f32(v)); return v;}
fn Vec3F32 cross_3f32(Vec3F32 a, Vec3F32 b)
{
    Vec3F32 c = {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
    return c;
}
fn Vec3F32 mix_3f32(Vec3F32 a, Vec3F32 b, F32 t)
{
    Vec3F32 c = {
        mix_1f32(a.x, b.x, t),
        mix_1f32(a.y, b.y, t),
        mix_1f32(a.z, b.z, t)
    };
    return c;
}

fn Vec3I32 vec_3i32(I32 x, I32 y, I32 z)         {Vec3I32 v = {x, y, z}; return v;}
fn Vec3I32 add_3i32(Vec3I32 a, Vec3I32 b)        {Vec3I32 c = {a.x+b.x, a.y+b.y, a.z+b.z}; return c;}
fn Vec3I32 sub_3i32(Vec3I32 a, Vec3I32 b)        {Vec3I32 c = {a.x-b.x, a.y-b.y, a.z-b.z}; return c;}
fn Vec3I32 mul_3i32(Vec3I32 a, Vec3I32 b)        {Vec3I32 c = {a.x*b.x, a.y*b.y, a.z*b.z}; return c;}
fn Vec3I32 div_3i32(Vec3I32 a, Vec3I32 b)        {Vec3I32 c = {a.x/b.x, a.y/b.y, a.z/b.z}; return c;}
fn Vec3I32 scale_3i32(Vec3I32 v, I32 s)          {Vec3I32 c = {v.x*s, v.y*s, v.z*s}; return c;}
fn I32 dot_3i32(Vec3I32 a, Vec3I32 b)            {I32 c = a.x*b.x + a.y*b.y + a.z*b.z; return c;}
fn I32 length_squared_3i32(Vec3I32 v)            {I32 c = v.x*v.x + v.y*v.y + v.z*v.z; return c;}
fn Vec3I32 normalize_3i32(Vec3I32 v)             {v = scale_3i32(v, (I32)(1.f/length_3i32(v))); return v;}
fn I32 length_3i32(Vec3I32 v)
{
    I32 c = (I32)sqrt_f32((F32)(v.x*v.x + v.y*v.y + v.z*v.z));
    return c;
}
fn Vec3I32 mix_3i32(Vec3I32 a, Vec3I32 b, F32 t) {
    Vec3I32 c = {
        (I32)mix_1f32((F32)a.x, (F32)b.x, t),
        (I32)mix_1f32((F32)a.y, (F32)b.y, t),
        (I32)mix_1f32((F32)a.z, (F32)b.z, t)
    };
    return c;
}
fn Vec3I32 cross_3i32(Vec3I32 a, Vec3I32 b)
{
    Vec3I32 c = {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
    return c;
}

fn Vec4F32 vec_4f32(F32 x, F32 y, F32 z, F32 w)  {Vec4F32 v = {x, y, z, w}; return v;}
fn Vec4F32 add_4f32(Vec4F32 a, Vec4F32 b)        {Vec4F32 c = {a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w}; return c;}
fn Vec4F32 sub_4f32(Vec4F32 a, Vec4F32 b)        {Vec4F32 c = {a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w}; return c;}
fn Vec4F32 mul_4f32(Vec4F32 a, Vec4F32 b)        {Vec4F32 c = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w}; return c;}
fn Vec4F32 div_4f32(Vec4F32 a, Vec4F32 b)        {Vec4F32 c = {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w}; return c;}
fn Vec4F32 scale_4f32(Vec4F32 v, F32 s)          {Vec4F32 c = {v.x*s, v.y*s, v.z*s, v.w*s}; return c;}
fn F32 dot_4f32(Vec4F32 a, Vec4F32 b)            {F32 c = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; return c;}
fn F32 length_squared_4f32(Vec4F32 v)            {F32 c = v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w; return c;}
fn Vec4F32 normalize_4f32(Vec4F32 v)             {v = scale_4f32(v, 1.f/length_4f32(v)); return v;}
fn F32 length_4f32(Vec4F32 v)                    {
    F32 c = sqrt_f32(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
    return c;
}
fn Vec4F32 mix_4f32(Vec4F32 a, Vec4F32 b, F32 t) {
    Vec4F32 c = {
        mix_1f32(a.x, b.x, t),
        mix_1f32(a.y, b.y, t),
        mix_1f32(a.z, b.z, t),
        mix_1f32(a.w, b.w, t)
    };
    return c;
}

fn Vec4I32 vec_4i32(I32 x, I32 y, I32 z, I32 w)  {Vec4I32 v = {x, y, z, w}; return v;}
fn Vec4I32 add_4i32(Vec4I32 a, Vec4I32 b)        {Vec4I32 c = {a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w}; return c;}
fn Vec4I32 sub_4i32(Vec4I32 a, Vec4I32 b)        {Vec4I32 c = {a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w}; return c;}
fn Vec4I32 mul_4i32(Vec4I32 a, Vec4I32 b)        {Vec4I32 c = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w}; return c;}
fn Vec4I32 div_4i32(Vec4I32 a, Vec4I32 b)        {Vec4I32 c = {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w}; return c;}
fn Vec4I32 scale_4i32(Vec4I32 v, I32 s)          {Vec4I32 c = {v.x*s, v.y*s, v.z*s, v.w*s}; return c;}
fn I32 dot_4i32(Vec4I32 a, Vec4I32 b)            {I32 c = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; return c;}
fn I32 length_squared_4i32(Vec4I32 v)            {I32 c = v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w; return c;}
fn Vec4I32 normalize_4i32(Vec4I32 v)             {v = scale_4i32(v, (I32)(1.f/length_4i32(v))); return v;}
fn I32 length_4i32(Vec4I32 v)                    {
    I32 c = (I32)sqrt_f32((F32)(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w));
    return c;
}
fn Vec4I32 mix_4i32(Vec4I32 a, Vec4I32 b, F32 t) {
    Vec4I32 c = {
        (I32)mix_1f32((F32)a.x, (F32)b.x, t),
        (I32)mix_1f32((F32)a.y, (F32)b.y, t),
        (I32)mix_1f32((F32)a.z, (F32)b.z, t),
        (I32)mix_1f32((F32)a.w, (F32)b.w, t)
    };
    return c;
}

// Range Ops
////==================================================================

fn Rng1U32 rng_1u32(U32 min, U32 max)                     {Rng1U32 r = {min, max}; if(r.min > r.max) { Swap(U32, r.min, r.max); } return r;}
fn Rng1U32 shift_1u32(Rng1U32 r, U32 x)                   {r.min += x; r.max += x; return r;}
fn Rng1U32 pad_1u32(Rng1U32 r, U32 x)                     {r.min -= x; r.max += x; return r;}
fn U32 center_1u32(Rng1U32 r)                             {U32 c = (r.min+r.max)/2; return c;}
fn I32 contains_1u32(Rng1U32 r, U32 x)                    {I32 c = (r.min <= x && x < r.max); return c;}
fn U32 dim_1u32(Rng1U32 r)                                {U32 c = ((r.max > r.min) ? (r.max - r.min) : 0); return c;}
fn Rng1U32 union_1u32(Rng1U32 a, Rng1U32 b)               {Rng1U32 c = {Min(a.min, b.min), Max(a.max, b.max)}; return c;}
fn Rng1U32 intersect_1u32(Rng1U32 a, Rng1U32 b)           {Rng1U32 c = {Max(a.min, b.min), Min(a.max, b.max)}; return c;}
fn U32 clamp_1u32(Rng1U32 r, U32 v)                       {v = Clamp(r.min, v, r.max); return v;}

fn Rng1I32 rng_1s32(I32 min, I32 max)                     {Rng1I32 r = {min, max}; if(r.min > r.max) { Swap(I32, r.min, r.max); } return r;}
fn Rng1I32 shift_1s32(Rng1I32 r, I32 x)                   {r.min += x; r.max += x; return r;}

fn Rng1I32 pad_1s32(Rng1I32 r, I32 x)                     {r.min -= x; r.max += x; return r;}
fn I32 center_1s32(Rng1I32 r)                             {I32 c = (r.min+r.max)/2; return c;}
fn I32 contains_1s32(Rng1I32 r, I32 x)                    {I32 c = (r.min <= x && x < r.max); return c;}
fn I32 dim_1s32(Rng1I32 r)                                {I32 c = ((r.max > r.min) ? (r.max - r.min) : 0); return c;}
fn Rng1I32 union_1s32(Rng1I32 a, Rng1I32 b)               {Rng1I32 c = {Min(a.min, b.min), Max(a.max, b.max)}; return c;}
fn Rng1I32 intersect_1s32(Rng1I32 a, Rng1I32 b)           {Rng1I32 c = {Max(a.min, b.min), Min(a.max, b.max)}; return c;}
fn I32 clamp_1s32(Rng1I32 r, I32 v)                       {v = Clamp(r.min, v, r.max); return v;}

fn Rng1U64 rng_1u64(U64 min, U64 max)                     {Rng1U64 r = {min, max}; if(r.min > r.max) { Swap(U64, r.min, r.max); } return r;}
fn Rng1U64 shift_1u64(Rng1U64 r, U64 x)                   {r.min += x; r.max += x; return r;}
fn Rng1U64 pad_1u64(Rng1U64 r, U64 x)                     {r.min -= x; r.max += x; return r;}
fn U64 center_1u64(Rng1U64 r)                             {U64 c = (r.min+r.max)/2; return c;}
fn I32 contains_1u64(Rng1U64 r, U64 x)                    {I32 c = (r.min <= x && x < r.max); return c;}
fn U64 dim_1u64(Rng1U64 r)                                {U64 c = ((r.max > r.min) ? (r.max - r.min) : 0); return c;}
fn Rng1U64 union_1u64(Rng1U64 a, Rng1U64 b)               {Rng1U64 c = {Min(a.min, b.min), Max(a.max, b.max)}; return c;}
fn Rng1U64 intersect_1u64(Rng1U64 a, Rng1U64 b)           {Rng1U64 c = {Max(a.min, b.min), Min(a.max, b.max)}; return c;}
fn U64 clamp_1u64(Rng1U64 r, U64 v)                       {v = Clamp(r.min, v, r.max); return v;}

fn Rng1I64 rng_1s64(I64 min, I64 max)                     {Rng1I64 r = {min, max}; if(r.min > r.max) { Swap(I64, r.min, r.max); } return r;}
fn Rng1I64 shift_1s64(Rng1I64 r, I64 x)                   {r.min += x; r.max += x; return r;}
fn Rng1I64 pad_1s64(Rng1I64 r, I64 x)                     {r.min -= x; r.max += x; return r;}
fn I64 center_1s64(Rng1I64 r)                             {I64 c = (r.min+r.max)/2; return c;}
fn I32 contains_1s64(Rng1I64 r, I64 x)                    {I32 c = (r.min <= x && x < r.max); return c;}
fn I64 dim_1s64(Rng1I64 r)                                {I64 c = ((r.max > r.min) ? (r.max - r.min) : 0); return c;}
fn Rng1I64 union_1s64(Rng1I64 a, Rng1I64 b)               {Rng1I64 c = {Min(a.min, b.min), Max(a.max, b.max)}; return c;}
fn Rng1I64 intersect_1s64(Rng1I64 a, Rng1I64 b)           {Rng1I64 c = {Max(a.min, b.min), Min(a.max, b.max)}; return c;}
fn I64 clamp_1s64(Rng1I64 r, I64 v)                       {v = Clamp(r.min, v, r.max); return v;}

fn Rng1F32 rng_1f32(F32 min, F32 max)                     {Rng1F32 r = {min, max}; if(r.min > r.max) { Swap(F32, r.min, r.max); } return r;}
fn Rng1F32 shift_1f32(Rng1F32 r, F32 x)                   {r.min += x; r.max += x; return r;}
fn Rng1F32 pad_1f32(Rng1F32 r, F32 x)                     {r.min -= x; r.max += x; return r;}
fn F32 center_1f32(Rng1F32 r)                             {F32 c = (r.min+r.max)/2; return c;}
fn I32 contains_1f32(Rng1F32 r, F32 x)                    {I32 c = (r.min <= x && x < r.max); return c;}
fn F32 dim_1f32(Rng1F32 r)                                {F32 c = ((r.max > r.min) ? (r.max - r.min) : 0); return c;}
fn Rng1F32 union_1f32(Rng1F32 a, Rng1F32 b)               {Rng1F32 c = {Min(a.min, b.min), Max(a.max, b.max)}; return c;}
fn Rng1F32 intersect_1f32(Rng1F32 a, Rng1F32 b)           {Rng1F32 c = {Max(a.min, b.min), Min(a.max, b.max)}; return c;}
fn F32 clamp_1f32(Rng1F32 r, F32 v)                       {v = Clamp(r.min, v, r.max); return v;}

fn Rng2I16 rng_2s16(Vec2I16 min, Vec2I16 max)             {Rng2I16 r = {min, max}; return r;}
fn Rng2I16 shift_2s16(Rng2I16 r, Vec2I16 x)               {r.min = add_2i16(r.min, x); r.max = add_2i16(r.max, x); return r;}
fn Rng2I16 pad_2s16(Rng2I16 r, I16 x)                     {Vec2I16 xv = {x, x}; r.min = sub_2i16(r.min, xv); r.max = add_2i16(r.max, xv); return r;}
fn Vec2I16 center_2s16(Rng2I16 r)                         {Vec2I16 c = {(I16)((r.min.x+r.max.x)/2), (I16)((r.min.y+r.max.y)/2)}; return c;}
fn I32 contains_2s16(Rng2I16 r, Vec2I16 x)                {I32 c = (r.min.x <= x.x && x.x < r.max.x && r.min.y <= x.y && x.y < r.max.y); return c;}
fn Vec2I16 dim_2s16(Rng2I16 r)                            {Vec2I16 dim = {(I16)(((r.max.x > r.min.x) ? (r.max.x - r.min.x) : 0)), (I16)(((r.max.y > r.min.y) ? (r.max.y - r.min.y) : 0))}; return dim;}
fn Rng2I16 union_2s16(Rng2I16 a, Rng2I16 b)               {Rng2I16 c; c.p0.x = Min(a.min.x, b.min.x); c.p0.y = Min(a.min.y, b.min.y); c.p1.x = Max(a.max.x, b.max.x); c.p1.y = Max(a.max.y, b.max.y); return c;}
fn Rng2I16 intersect_2s16(Rng2I16 a, Rng2I16 b)           {Rng2I16 c; c.p0.x = Max(a.min.x, b.min.x); c.p0.y = Max(a.min.y, b.min.y); c.p1.x = Min(a.max.x, b.max.x); c.p1.y = Min(a.max.y, b.max.y); return c;}
fn Vec2I16 clamp_2s16(Rng2I16 r, Vec2I16 v)               {v.x = Clamp(r.min.x, v.x, r.max.x); v.y = Clamp(r.min.y, v.y, r.max.y); return v;}

fn Rng2I32 rng_2s32(Vec2I32 min, Vec2I32 max)             {Rng2I32 r = {min, max}; return r;}
fn Rng2I32 shift_2s32(Rng2I32 r, Vec2I32 x)               {r.min = add_2i32(r.min, x); r.max = add_2i32(r.max, x); return r;}
fn Rng2I32 pad_2s32(Rng2I32 r, I32 x)                     {Vec2I32 xv = {x, x}; r.min = sub_2i32(r.min, xv); r.max = add_2i32(r.max, xv); return r;}
fn Vec2I32 center_2s32(Rng2I32 r)                         {Vec2I32 c = {(r.min.x+r.max.x)/2, (r.min.y+r.max.y)/2}; return c;}
fn I32 contains_2s32(Rng2I32 r, Vec2I32 x)                {I32 c = (r.min.x <= x.x && x.x < r.max.x && r.min.y <= x.y && x.y < r.max.y); return c;}
fn Vec2I32 dim_2s32(Rng2I32 r)                            {Vec2I32 dim = {((r.max.x > r.min.x) ? (r.max.x - r.min.x) : 0), ((r.max.y > r.min.y) ? (r.max.y - r.min.y) : 0)}; return dim;}
fn Rng2I32 union_2s32(Rng2I32 a, Rng2I32 b)               {Rng2I32 c; c.p0.x = Min(a.min.x, b.min.x); c.p0.y = Min(a.min.y, b.min.y); c.p1.x = Max(a.max.x, b.max.x); c.p1.y = Max(a.max.y, b.max.y); return c;}
fn Rng2I32 intersect_2s32(Rng2I32 a, Rng2I32 b)           {Rng2I32 c; c.p0.x = Max(a.min.x, b.min.x); c.p0.y = Max(a.min.y, b.min.y); c.p1.x = Min(a.max.x, b.max.x); c.p1.y = Min(a.max.y, b.max.y); return c;}
fn Vec2I32 clamp_2s32(Rng2I32 r, Vec2I32 v)               {v.x = Clamp(r.min.x, v.x, r.max.x); v.y = Clamp(r.min.y, v.y, r.max.y); return v;}

fn Rng2I64 rng_2s64(Vec2I64 min, Vec2I64 max)             {Rng2I64 r = {min, max}; return r;}
fn Rng2I64 shift_2s64(Rng2I64 r, Vec2I64 x)               {r.min = add_2i64(r.min, x); r.max = add_2i64(r.max, x); return r;}
fn Rng2I64 pad_2s64(Rng2I64 r, I64 x)                     {Vec2I64 xv = {x, x}; r.min = sub_2i64(r.min, xv); r.max = add_2i64(r.max, xv); return r;}
fn Vec2I64 center_2s64(Rng2I64 r)                         {Vec2I64 c = {(r.min.x+r.max.x)/2, (r.min.y+r.max.y)/2}; return c;}
fn I32 contains_2s64(Rng2I64 r, Vec2I64 x)                {I32 c = (r.min.x <= x.x && x.x < r.max.x && r.min.y <= x.y && x.y < r.max.y); return c;}
fn Vec2I64 dim_2s64(Rng2I64 r)                            {Vec2I64 dim = {((r.max.x > r.min.x) ? (r.max.x - r.min.x) : 0), ((r.max.y > r.min.y) ? (r.max.y - r.min.y) : 0)}; return dim;}
fn Rng2I64 union_2s64(Rng2I64 a, Rng2I64 b)               {Rng2I64 c; c.p0.x = Min(a.min.x, b.min.x); c.p0.y = Min(a.min.y, b.min.y); c.p1.x = Max(a.max.x, b.max.x); c.p1.y = Max(a.max.y, b.max.y); return c;}
fn Rng2I64 intersect_2s64(Rng2I64 a, Rng2I64 b)           {Rng2I64 c; c.p0.x = Max(a.min.x, b.min.x); c.p0.y = Max(a.min.y, b.min.y); c.p1.x = Min(a.max.x, b.max.x); c.p1.y = Min(a.max.y, b.max.y); return c;}
fn Vec2I64 clamp_2s64(Rng2I64 r, Vec2I64 v)               {v.x = Clamp(r.min.x, v.x, r.max.x); v.y = Clamp(r.min.y, v.y, r.max.y); return v;}

fn Rng2F32 rng_2f32(Vec2F32 min, Vec2F32 max)             {Rng2F32 r = {min, max}; return r;}
fn Rng2F32 shift_2f32(Rng2F32 r, Vec2F32 x)               {r.min = add_2f32(r.min, x); r.max = add_2f32(r.max, x); return r;}
fn Rng2F32 pad_2f32(Rng2F32 r, F32 x)                     {Vec2F32 xv = {x, x}; r.min = sub_2f32(r.min, xv); r.max = add_2f32(r.max, xv); return r;}
fn Vec2F32 center_2f32(Rng2F32 r)                         {Vec2F32 c = {(r.min.x+r.max.x)/2, (r.min.y+r.max.y)/2}; return c;}
fn I32 contains_2f32(Rng2F32 r, Vec2F32 x)                {I32 c = (r.min.x <= x.x && x.x < r.max.x && r.min.y <= x.y && x.y < r.max.y); return c;}
fn Vec2F32 dim_2f32(Rng2F32 r)                            {Vec2F32 dim = {((r.max.x > r.min.x) ? (r.max.x - r.min.x) : 0), ((r.max.y > r.min.y) ? (r.max.y - r.min.y) : 0)}; return dim;}
fn Rng2F32 union_2f32(Rng2F32 a, Rng2F32 b)               {Rng2F32 c; c.p0.x = Min(a.min.x, b.min.x); c.p0.y = Min(a.min.y, b.min.y); c.p1.x = Max(a.max.x, b.max.x); c.p1.y = Max(a.max.y, b.max.y); return c;}
fn Rng2F32 intersect_2f32(Rng2F32 a, Rng2F32 b)           {Rng2F32 c; c.p0.x = Max(a.min.x, b.min.x); c.p0.y = Max(a.min.y, b.min.y); c.p1.x = Min(a.max.x, b.max.x); c.p1.y = Min(a.max.y, b.max.y); return c;}
fn Vec2F32 clamp_2f32(Rng2F32 r, Vec2F32 v)               {v.x = Clamp(r.min.x, v.x, r.max.x); v.y = Clamp(r.min.y, v.y, r.max.y); return v;}
