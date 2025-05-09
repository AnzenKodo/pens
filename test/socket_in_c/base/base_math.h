#ifndef BASE_MATH_H
#define BASE_MATH_H

// Vector Types
//====================================================================

//// 2-Vectors
////==================================================================

typedef union Vec2F32 Vec2F32;
union Vec2F32
{
    struct
    {
        F32 x;
        F32 y;
    };
    F32 v[2];
};

typedef union Vec2I64 Vec2I64;
union Vec2I64
{
    struct
    {
        I64 x;
        I64 y;
    };
    I64 v[2];
};

typedef union Vec2I32 Vec2I32;
union Vec2I32
{
    struct
    {
        I32 x;
        I32 y;
    };
    I32 v[2];
};

typedef union Vec2I16 Vec2I16;
union Vec2I16
{
    struct
    {
        I16 x;
        I16 y;
    };
    I16 v[2];
};

//// 3-vectors
////==================================================================

typedef union Vec3F32 Vec3F32;
union Vec3F32
{
    struct
    {
        F32 x;
        F32 y;
        F32 z;
    };
    struct
    {
        Vec2F32 xy;
        F32 _z0;
    };
    struct
    {
        F32 _x0;
        Vec2F32 yz;
    };
    F32 v[3];
};

typedef union Vec3I32 Vec3I32;
union Vec3I32
{
    struct
    {
        I32 x;
        I32 y;
        I32 z;
    };
    struct
    {
        Vec2I32 xy;
        I32 _z0;
    };
    struct
    {
        I32 _x0;
        Vec2I32 yz;
    };
    I32 v[3];
};

//// 4-vectors
////==================================================================

typedef union Vec4F32 Vec4F32;
union Vec4F32
{
    struct
    {
        F32 x;
        F32 y;
        F32 z;
        F32 w;
    };
    struct
    {
        Vec2F32 xy;
        Vec2F32 zw;
    };
    struct
    {
        Vec3F32 xyz;
        F32 _z0;
    };
    struct
    {
        F32 _x0;
        Vec3F32 yzw;
    };
    F32 v[4];
};

typedef union Vec4I32 Vec4I32;
union Vec4I32
{
    struct
    {
        I32 x;
        I32 y;
        I32 z;
        I32 w;
    };
    struct
    {
        Vec2I32 xy;
        Vec2I32 zw;
    };
    struct
    {
        Vec3I32 xyz;
        I32 _z0;
    };
    struct
    {
        I32 _x0;
        Vec3I32 yzw;
    };
    I32 v[4];
};

//// Matrix Types
////==================================================================

typedef struct Mat3x3F32 Mat3x3F32;
struct Mat3x3F32
{
    F32 v[3][3];
};

typedef struct Mat4x4F32 Mat4x4F32;
struct Mat4x4F32
{
    F32 v[4][4];
};

// Range Types
//====================================================================

//// 1-range
////==================================================================

typedef union Rng1U32 Rng1U32;
union Rng1U32
{
    struct
    {
        U32 min;
        U32 max;
    };
    U32 v[2];
};

typedef union Rng1I32 Rng1I32;
union Rng1I32
{
    struct
    {
        I32 min;
        I32 max;
    };
    I32 v[2];
};

typedef union Rng1U64 Rng1U64;
union Rng1U64
{
    struct
    {
        U64 min;
        U64 max;
    };
    U64 v[2];
};

typedef union Rng1I64 Rng1I64;
union Rng1I64
{
    struct
    {
        I64 min;
        I64 max;
    };
    I64 v[2];
};

typedef union Rng1F32 Rng1F32;
union Rng1F32
{
    struct
    {
        F32 min;
        F32 max;
    };
    F32 v[2];
};

//// 2-range (rectangles)
////==================================================================

typedef union Rng2I16 Rng2I16;
union Rng2I16
{
  struct
  {
    Vec2I16 min;
    Vec2I16 max;
  };
  struct
  {
    Vec2I16 p0;
    Vec2I16 p1;
  };
  struct
  {
    I16 x0;
    I16 y0;
    I16 x1;
    I16 y1;
  };
  Vec2I16 v[2];
};

typedef union Rng2I32 Rng2I32;
union Rng2I32
{
  struct
  {
    Vec2I32 min;
    Vec2I32 max;
  };
  struct
  {
    Vec2I32 p0;
    Vec2I32 p1;
  };
  struct
  {
    I32 x0;
    I32 y0;
    I32 x1;
    I32 y1;
  };
  Vec2I32 v[2];
};

typedef union Rng2F32 Rng2F32;
union Rng2F32
{
  struct
  {
    Vec2F32 min;
    Vec2F32 max;
  };
  struct
  {
    Vec2F32 p0;
    Vec2F32 p1;
  };
  struct
  {
    F32 x0;
    F32 y0;
    F32 x1;
    F32 y1;
  };
  Vec2F32 v[2];
};

typedef union Rng2I64 Rng2I64;
union Rng2I64
{
  struct
  {
    Vec2I64 min;
    Vec2I64 max;
  };
  struct
  {
    Vec2I64 p0;
    Vec2I64 p1;
  };
  struct
  {
    I64 x0;
    I64 y0;
    I64 x1;
    I64 y1;
  };
  Vec2I64 v[2];
};


// Constants
//====================================================================

#define MATH_EPSILON      1.19209290e-7f
#define MATH_ZERO         0.0f
#define MATH_ONE          1.0f
#define MATH_TWO_THIRDS   0.666666666666666666666666666666666666667f

#define MATH_TAU          6.28318530717958647692528676655900576f
#define MATH_PI           3.14159265358979323846264338327950288f
#define MATH_ONE_OVER_TAU 0.159154943091895335768883763372514362f
#define MATH_ONE_OVER_PI  0.318309886183790671537767526745028724f

#define MATH_TAU_OVER_2   3.14159265358979323846264338327950288f
#define MATH_TAU_OVER_4   1.570796326794896619231321691639751442f
#define MATH_TAU_OVER_8   0.785398163397448309615660845819875721f

#define MATH_E            2.7182818284590452353602874713526625f
#define MATH_SQRT_TWO     1.41421356237309504880168872420969808f
#define MATH_SQRT_THREE   1.73205080756887729352744634150587236f
#define MATH_SQRT_FIVE    2.23606797749978969640917366873127623f

#define MATH_LOG_TWO      0.693147180559945309417232121458176568f
#define MATH_LOG_TEN      2.30258509299404568401799145468436421f

// Micros
//====================================================================

#define Abs(x) ((x) > 0 ? (x) : -(x))
#define Swap(T,a,b) do{T t__ = a; a = b; b = t__;}while(0)

fn F32 lerp_f32(F32 a, F32 b, F32 t);
fn I32 round_f32_to_i32(F32 a);
fn U32 round_f32_to_u32(F32 a);

//// Scalar Ops
////==================================================================

#define radians_from_turns_f32(v) ((v)*2*3.1415926535897f)
#define turns_from_radians_f32(v) ((v)/2*3.1415926535897f)
#define degrees_from_turns_f32(v) ((v)*360.f)
#define turns_from_degrees_f32(v) ((v)/360.f)
#define degrees_from_radians_f32(v) (degrees_from_turns_f32(turns_from_radians_f32(v)))
#define radians_from_degrees_f32(v) (radians_from_turns_f32(turns_from_degrees_f32(v)))

fn F32 round_f32(F32 x);
fn F32 floor_f32(F32 x);
fn F32 ceil_f32(F32 x);

fn F32 sqrt_f32(F32 number);
fn F32 cos_f32(F32 a);
fn F32 sin_f32(F32 a);
fn F32 tan_f32(F32 radians);
fn F32 pow_f32(F32 a, F32 b);
fn F32 exp_f32(F32 a);
fn F32 log_f32(F32 a);
fn F32 arctan_f32(F32 a);
fn F32 arctan2_f32(F32 y, F32 x);
fn F32 arcsin_f32(F32 a);
fn F32 arccos_f32(F32 a);
fn F32 round_f32(F32 a);
fn F64 mix_1f64(F64 a, F64 b, F64 t);
fn F32 mix_1f32(F32 a, F32 b, F32 t);

// Vector Ops
//====================================================================

fn Vec2F32 vec_2f32(F32 x, F32 y);
fn Vec2F32 add_2f32(Vec2F32 a, Vec2F32 b);
fn Vec2F32 sub_2f32(Vec2F32 a, Vec2F32 b);
fn Vec2F32 mul_2f32(Vec2F32 a, Vec2F32 b);
fn Vec2F32 div_2f32(Vec2F32 a, Vec2F32 b);
fn Vec2F32 scale_2f32(Vec2F32 v, F32 s);
fn F32 dot_2f32(Vec2F32 a, Vec2F32 b);
fn F32 length_squared_2f32(Vec2F32 v);
fn F32 length_2f32(Vec2F32 v);
fn Vec2F32 normalize_2f32(Vec2F32 v);
fn Vec2F32 mix_2f32(Vec2F32 a, Vec2F32 b, F32 t);

fn Vec2I64 vec_2i64(I64 x, I64 y);
fn Vec2I64 add_2i64(Vec2I64 a, Vec2I64 b);
fn Vec2I64 sub_2i64(Vec2I64 a, Vec2I64 b);
fn Vec2I64 mul_2i64(Vec2I64 a, Vec2I64 b);
fn Vec2I64 div_2i64(Vec2I64 a, Vec2I64 b);
fn Vec2I64 scale_2i64(Vec2I64 v, I64 s);
fn I64 dot_2i64(Vec2I64 a, Vec2I64 b);
fn I64 length_squared_2i64(Vec2I64 v);
fn I64 length_2i64(Vec2I64 v);
fn Vec2I64 normalize_2i64(Vec2I64 v);
fn Vec2I64 mix_2i64(Vec2I64 a, Vec2I64 b, F32 t);

fn Vec2I32 vec_2i32(I32 x, I32 y);
fn Vec2I32 add_2i32(Vec2I32 a, Vec2I32 b);
fn Vec2I32 sub_2i32(Vec2I32 a, Vec2I32 b);
fn Vec2I32 mul_2i32(Vec2I32 a, Vec2I32 b);
fn Vec2I32 div_2i32(Vec2I32 a, Vec2I32 b);
fn Vec2I32 scale_2i32(Vec2I32 v, I32 s);
fn I32 dot_2i32(Vec2I32 a, Vec2I32 b);
fn I32 length_squared_2i32(Vec2I32 v);
fn I32 length_2i32(Vec2I32 v);
fn Vec2I32 normalize_2i32(Vec2I32 v);
fn Vec2I32 mix_2i32(Vec2I32 a, Vec2I32 b, F32 t);

fn Vec2I16 vec_2i16(I16 x, I16 y);
fn Vec2I16 add_2i16(Vec2I16 a, Vec2I16 b);
fn Vec2I16 sub_2i16(Vec2I16 a, Vec2I16 b);
fn Vec2I16 mul_2i16(Vec2I16 a, Vec2I16 b);
fn Vec2I16 div_2i16(Vec2I16 a, Vec2I16 b);
fn Vec2I16 scale_2i16(Vec2I16 v, I16 s);
fn I16 dot_2i16(Vec2I16 a, Vec2I16 b);
fn I16 length_squared_2i16(Vec2I16 v);
fn I16 length_2i16(Vec2I16 v);
fn Vec2I16 normalize_2I16(Vec2I16 v);
fn Vec2I16 mix_2i16(Vec2I16 a, Vec2I16 b, F32 t);

fn Vec3F32 vec_3f32(F32 x, F32 y, F32 z);
fn Vec3F32 add_3f32(Vec3F32 a, Vec3F32 b);
fn Vec3F32 sub_3f32(Vec3F32 a, Vec3F32 b);
fn Vec3F32 mul_3f32(Vec3F32 a, Vec3F32 b);
fn Vec3F32 div_3f32(Vec3F32 a, Vec3F32 b);
fn Vec3F32 scale_3f32(Vec3F32 v, F32 s);
fn F32 dot_3f32(Vec3F32 a, Vec3F32 b);
fn F32 length_squared_3f32(Vec3F32 v);
fn F32 length_3f32(Vec3F32 v);
fn Vec3F32 normalize_3f32(Vec3F32 v);
fn Vec3F32 mix_3f32(Vec3F32 a, Vec3F32 b, F32 t);
fn Vec3F32 cross_3f32(Vec3F32 a, Vec3F32 b);

fn Vec3I32 vec_3i32(I32 x, I32 y, I32 z);
fn Vec3I32 add_3i32(Vec3I32 a, Vec3I32 b);
fn Vec3I32 sub_3i32(Vec3I32 a, Vec3I32 b);
fn Vec3I32 mul_3i32(Vec3I32 a, Vec3I32 b);
fn Vec3I32 div_3i32(Vec3I32 a, Vec3I32 b);
fn Vec3I32 scale_3i32(Vec3I32 v, I32 s);
fn I32 dot_3i32(Vec3I32 a, Vec3I32 b);
fn I32 length_squared_3i32(Vec3I32 v);
fn I32 length_3i32(Vec3I32 v);
fn Vec3I32 normalize_3i32(Vec3I32 v);
fn Vec3I32 mix_3i32(Vec3I32 a, Vec3I32 b, F32 t);
fn Vec3I32 cross_3i32(Vec3I32 a, Vec3I32 b);

fn Vec4F32 vec_4f32(F32 x, F32 y, F32 z, F32 w);
fn Vec4F32 add_4f32(Vec4F32 a, Vec4F32 b);
fn Vec4F32 sub_4f32(Vec4F32 a, Vec4F32 b);
fn Vec4F32 mul_4f32(Vec4F32 a, Vec4F32 b);
fn Vec4F32 div_4f32(Vec4F32 a, Vec4F32 b);
fn Vec4F32 scale_4f32(Vec4F32 v, F32 s);
fn F32 dot_4f32(Vec4F32 a, Vec4F32 b);
fn F32 length_squared_4f32(Vec4F32 v);
fn F32 length_4f32(Vec4F32 v);
fn Vec4F32 normalize_4f32(Vec4F32 v);
fn Vec4F32 mix_4f32(Vec4F32 a, Vec4F32 b, F32 t);

fn Vec4I32 vec_4i32(I32 x, I32 y, I32 z, I32 w);
fn Vec4I32 add_4i32(Vec4I32 a, Vec4I32 b);
fn Vec4I32 sub_4i32(Vec4I32 a, Vec4I32 b);
fn Vec4I32 mul_4i32(Vec4I32 a, Vec4I32 b);
fn Vec4I32 div_4i32(Vec4I32 a, Vec4I32 b);
fn Vec4I32 scale_4i32(Vec4I32 v, I32 s);
fn I32 dot_4i32(Vec4I32 a, Vec4I32 b);
fn I32 length_squared_4i32(Vec4I32 v);
fn I32 length_4i32(Vec4I32 v);
fn Vec4I32 normalize_4i32(Vec4I32 v);
fn Vec4I32 mix_4i32(Vec4I32 a, Vec4I32 b, F32 t);

// Range Ops
////==================================================================

fn Rng1U32 rng_1u32(U32 min, U32 max);
fn Rng1U32 shift_1u32(Rng1U32 r, U32 x);
fn Rng1U32 pad_1u32(Rng1U32 r, U32 x);
fn U32 center_1u32(Rng1U32 r);
fn I32 contains_1u32(Rng1U32 r, U32 x);
fn U32 dim_1u32(Rng1U32 r);
fn Rng1U32 union_1u32(Rng1U32 a, Rng1U32 b);
fn Rng1U32 intersect_1u32(Rng1U32 a, Rng1U32 b);
fn U32 clamp_1u32(Rng1U32 r, U32 v);

fn Rng1I32 rng_1s32(I32 min, I32 max);
fn Rng1I32 shift_1s32(Rng1I32 r, I32 x);

fn Rng1I32 pad_1s32(Rng1I32 r, I32 x);
fn I32 center_1s32(Rng1I32 r);
fn I32 contains_1s32(Rng1I32 r, I32 x);
fn I32 dim_1s32(Rng1I32 r);
fn Rng1I32 union_1s32(Rng1I32 a, Rng1I32 b);
fn Rng1I32 intersect_1s32(Rng1I32 a, Rng1I32 b);
fn I32 clamp_1s32(Rng1I32 r, I32 v);

fn Rng1U64 rng_1u64(U64 min, U64 max);
fn Rng1U64 shift_1u64(Rng1U64 r, U64 x);
fn Rng1U64 pad_1u64(Rng1U64 r, U64 x);
fn U64 center_1u64(Rng1U64 r);
fn I32 contains_1u64(Rng1U64 r, U64 x);
fn U64 dim_1u64(Rng1U64 r);
fn Rng1U64 union_1u64(Rng1U64 a, Rng1U64 b);
fn Rng1U64 intersect_1u64(Rng1U64 a, Rng1U64 b);
fn U64 clamp_1u64(Rng1U64 r, U64 v);

fn Rng1I64 rng_1s64(I64 min, I64 max);
fn Rng1I64 shift_1s64(Rng1I64 r, I64 x);
fn Rng1I64 pad_1s64(Rng1I64 r, I64 x);
fn I64 center_1s64(Rng1I64 r);
fn I32 contains_1s64(Rng1I64 r, I64 x);
fn I64 dim_1s64(Rng1I64 r);
fn Rng1I64 union_1s64(Rng1I64 a, Rng1I64 b);
fn Rng1I64 intersect_1s64(Rng1I64 a, Rng1I64 b);
fn I64 clamp_1s64(Rng1I64 r, I64 v);

fn Rng1F32 rng_1f32(F32 min, F32 max);
fn Rng1F32 shift_1f32(Rng1F32 r, F32 x);
fn Rng1F32 pad_1f32(Rng1F32 r, F32 x);
fn F32 center_1f32(Rng1F32 r);
fn I32 contains_1f32(Rng1F32 r, F32 x);
fn F32 dim_1f32(Rng1F32 r);
fn Rng1F32 union_1f32(Rng1F32 a, Rng1F32 b);
fn Rng1F32 intersect_1f32(Rng1F32 a, Rng1F32 b);
fn F32 clamp_1f32(Rng1F32 r, F32 v);

fn Rng2I16 rng_2s16(Vec2I16 min, Vec2I16 max);
fn Rng2I16 shift_2s16(Rng2I16 r, Vec2I16 x);
fn Rng2I16 pad_2s16(Rng2I16 r, I16 x);
fn Vec2I16 center_2s16(Rng2I16 r);
fn I32 contains_2s16(Rng2I16 r, Vec2I16 x);
fn Vec2I16 dim_2s16(Rng2I16 r);
fn Rng2I16 union_2s16(Rng2I16 a, Rng2I16 b);
fn Rng2I16 intersect_2s16(Rng2I16 a, Rng2I16 b);
fn Vec2I16 clamp_2s16(Rng2I16 r, Vec2I16 v);

fn Rng2I32 rng_2s32(Vec2I32 min, Vec2I32 max);
fn Rng2I32 shift_2s32(Rng2I32 r, Vec2I32 x);
fn Rng2I32 pad_2s32(Rng2I32 r, I32 x);
fn Vec2I32 center_2s32(Rng2I32 r);
fn I32 contains_2s32(Rng2I32 r, Vec2I32 x);
fn Vec2I32 dim_2s32(Rng2I32 r);
fn Rng2I32 union_2s32(Rng2I32 a, Rng2I32 b);
fn Rng2I32 intersect_2s32(Rng2I32 a, Rng2I32 b);
fn Vec2I32 clamp_2s32(Rng2I32 r, Vec2I32 v);

fn Rng2I64 rng_2s64(Vec2I64 min, Vec2I64 max);
fn Rng2I64 shift_2s64(Rng2I64 r, Vec2I64 x);
fn Rng2I64 pad_2s64(Rng2I64 r, I64 x);
fn Vec2I64 center_2s64(Rng2I64 r);
fn I32 contains_2s64(Rng2I64 r, Vec2I64 x);
fn Vec2I64 dim_2s64(Rng2I64 r);
fn Rng2I64 union_2s64(Rng2I64 a, Rng2I64 b);
fn Rng2I64 intersect_2s64(Rng2I64 a, Rng2I64 b);
fn Vec2I64 clamp_2s64(Rng2I64 r, Vec2I64 v);

fn Rng2F32 rng_2f32(Vec2F32 min, Vec2F32 max);
fn Rng2F32 shift_2f32(Rng2F32 r, Vec2F32 x);
fn Rng2F32 pad_2f32(Rng2F32 r, F32 x);
fn Vec2F32 center_2f32(Rng2F32 r);
fn I32 contains_2f32(Rng2F32 r, Vec2F32 x);
fn Vec2F32 dim_2f32(Rng2F32 r);
fn Rng2F32 union_2f32(Rng2F32 a, Rng2F32 b);
fn Rng2F32 intersect_2f32(Rng2F32 a, Rng2F32 b);
fn Vec2F32 clamp_2f32(Rng2F32 r, Vec2F32 v);

#endif // BASE_MATH_H
