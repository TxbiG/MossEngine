//                        MIT License
//
//                  Copyright (c) 2024 Toby
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

////////////////////////////////////////////////
/*                  Variants.h

          Variants handle all variants
*/
////////////////////////////////////////////////

#ifndef VARIANTS_H
#define VARIANTS_H

#include "Math.h"

// Add these v
typedef struct Basis;
typedef struct Matrix;
typedef struct Matrix2;
typedef struct Matrix3;
typedef struct Matrix4;
typedef struct Projection;
typedef struct Quaternion;
//////////////////////////////////

#ifdef USE_BGRA_PACKED_COLOR
#define COL32_R_SHIFT    16
#define COL32_G_SHIFT    8
#define COL32_B_SHIFT    0
#define COL32_A_SHIFT    24
#define COL32_A_MASK     0xFF000000
#else
#define COL32_R_SHIFT    0
#define COL32_G_SHIFT    8
#define COL32_B_SHIFT    16
#define COL32_A_SHIFT    24
#define COL32_A_MASK     0xFF000000
#endif  // USE_BGRA_PACKED_COLOR
#endif  // COL32_R_SHIFT
#define COL32(R,G,B,A)    (((uint32)(A)<<COL32_A_SHIFT) | ((uint32)(B)<<COL32_B_SHIFT) | ((uint32)(G)<<COL32_G_SHIFT) | ((uint32)(R)<<COL32_R_SHIFT))
#define COL32_WHITE       COL32(255,255,255,255)  // Opaque white = 0xFFFFFFFF
#define COL32_BLACK       COL32(0,0,0,255)        // Opaque black
#define COL32_TRANSPARENT COL32(0,0,0,0)          // Transparent black = 0x00000000

// - Misc maths helpers
static inline Vector2 Min(const Vector2& lhs, const Vector2& rhs)                { return Vector2(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y); }
static inline Vector2 Max(const Vector2& lhs, const Vector2& rhs)                { return Vector2(lhs.x >= rhs.x ? lhs.x : rhs.x, lhs.y >= rhs.y ? lhs.y : rhs.y); }
static inline Vector2 Clamp(const Vector2& v, const Vector2& mn, const Vector2& mx) { return Vector2((v.x < mn.x) ? mn.x : (v.x > mx.x) ? mx.x : v.x, (v.y < mn.y) ? mn.y : (v.y > mx.y) ? mx.y : v.y); }
static inline Vector2 Lerp(const Vector2& a, const Vector2& b, float t)          { return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t); }
static inline Vector2 Lerp(const Vector2& a, const Vector2& b, const Vector2& t)  { return Vector2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y); }
static inline Vector4 Lerp(const Vector4& a, const Vector4& b, float t)          { return Vector4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t); }
static inline float  Saturate(float f)                                        { return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
static inline float  LengthSqr(const Vector2& lhs)                             { return (lhs.x * lhs.x) + (lhs.y * lhs.y); }
static inline float  LengthSqr(const Vector4& lhs)                             { return (lhs.x * lhs.x) + (lhs.y * lhs.y) + (lhs.z * lhs.z) + (lhs.w * lhs.w); }
static inline float  InvLength(const Vector2& lhs, float fail_value)           { float d = (lhs.x * lhs.x) + (lhs.y * lhs.y); if (d > 0.0f) return Rsqrt(d); return fail_value; }
static inline float  Trunc(float f)                                           { return (float)(int)(f); }
static inline Vector2 Trunc(const Vector2& v)                                   { return Vector2((float)(int)(v.x), (float)(int)(v.y)); }
static inline float  Floor(float f)                                           { return (float)((f >= 0 || (float)(int)f == f) ? (int)f : (int)f - 1); } // Decent replacement for floorf()
static inline Vector2 Floor(const Vector2& v)                                   { return Vector2(Floor(v.x), Floor(v.y)); }
static inline int    ModPositive(int a, int b)                                { return (a + b) % b; }
//static inline float  Dot(const Vector2 a, const Vector2 b)                    { return a.x * b.x + a.y * b.y; }
static inline Vector2 Rotate(const Vector2& v, float cos_a, float sin_a)        { return Vector2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a); }
static inline float  LinearSweep(float current, float target, float speed)    { if (current < target) return Min(current + speed, target); if (current > target) return Max(current - speed, target); return current; }
static inline float  LinearRemapClamp(float s0, float s1, float d0, float d1, float x) { return Saturate((x - s0) / (s1 - s0)) * (d1 - d0) + d0; }
static inline Vector2 Mul(const Vector2& lhs, const Vector2& rhs)                { return Vector2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline bool   IsFloatAboveGuaranteedIntegerPrecision(float f)          { return f <= -16777216 || f >= 16777216; }
static inline float  ExponentialMovingAverage(float avg, float sample, int n) { avg -= avg / n; avg += sample / n; return avg; }


static inline Vector3 Min(const Vector3& lhs, const Vector3& rhs) { return Vector3(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y, lhs.z < rhs.z ? lhs.z : rhs.z); }
static inline Vector3 Max(const Vector3& lhs, const Vector3& rhs) { return Vector3(lhs.x >= rhs.x ? lhs.x : rhs.x, lhs.y >= rhs.y ? lhs.y : rhs.y, lhs.z >= rhs.z ? lhs.z : rhs.z); }
static inline Vector3 Clamp(const Vector3& v, const Vector3& mn, const Vector3& mx) { return Vector3((v.x < mn.x) ? mn.x : (v.x > mx.x) ? mx.x : v.x, (v.y < mn.y) ? mn.y : (v.y > mx.y) ? mx.y : v.y, (v.z < mn.z) ? mn.z : (v.z > mx.z) ? mx.z : v.z); }
static inline Vector4 Min(const Vector4& lhs, const Vector4& rhs) {return Vector4(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y, lhs.z < rhs.z ? lhs.z : rhs.z, lhs.w < rhs.w ? lhs.w : rhs.w); }
static inline Vector4 Max(const Vector4& lhs, const Vector4& rhs) { return Vector4(lhs.x >= rhs.x ? lhs.x : rhs.x, lhs.y >= rhs.y ? lhs.y : rhs.y, lhs.z >= rhs.z ? lhs.z : rhs.z, lhs.w >= rhs.w ? lhs.w : rhs.w); }
static inline Vector4 Clamp(const Vector4& v, const Vector4& mn, const Vector4& mx) { return Vector4((v.x < mn.x) ? mn.x : (v.x > mx.x) ? mx.x : v.x, (v.y < mn.y) ? mn.y : (v.y > mx.y) ? mx.y : v.y, (v.z < mn.z) ? mn.z : (v.z > mx.z) ? mx.z : v.z,(v.w < mn.w) ? mn.w : (v.w > mx.w) ? mx.w : v.w); }


struct Variant;
struct Object;

struct Tween : public Variant
{
    // Constructor
    Tween() : elapsedTime(0.0f), duration(0.0f), playing(false), currentValue(0.0f) {}
    Tween tween_callback(Callable callback);
    Tween tween_interval(float time);
    Tween tween_method(Callable method, Variant from, Variant to, float duration);
    Tween tween_property(Object: object, NodePath property, Variant final_val, float duration);

    //bind_node(node: Node);

    //Tween chain();

    //bool custom_step(delta: float);

    //int get_loops_left() const;

    //float get_total_elapsed_time() const;

    Variant interpolate_value(Variant initial_value, Variant delta_value, float elapsed_time, float duration, TransitionType trans_type, EaseType ease_type) static;

    //bool is_running();

    //bool is_valid();

    //void kill();

    //Tween parallel();

    void pause();

    void play();

    Tween set_ease(ease: EaseType);

    //Tween set_loops(loops: int = 0);

    //Tween set_parallel(parallel: bool = true);

    //Tween set_pause_mode(TweenPauseMode);

    //Tween set_process_mode(TweenProcessMode);

    //Tween set_speed_scale(speed: float);

    //Tween set_trans(trans: TransitionType);

    void stop();
};

struct Vector2 : public Variant
{
    float x, y;

    constexpr Vector2() : x(0.0f), y(0.0f) {}
    constexpr Vector2(float value) : x(value), y(value) {}
    constexpr Vector2(Vector2i vec2) : x((float)vec2.x), y((float)vec2.y) {}
    constexpr Vector2(int x, int y) : x((float) x), y((float) y) {}
    constexpr Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const { return Vector2{ x + other.x, y + other.y }; }
    Vector2 operator-(const Vector2& other) const { return Vector2{ x - other.x, y - other.y }; }
    Vector2 operator*(const Vector2& other) const { return Vector2{ x * other.x, y * other.y }; }
    Vector2 operator/(const Vector2& other) const { return Vector2{ x / other.x, y / other.y }; }

    Vector2 operator+(float scalar) const { return Vector2{ x + scalar, y + scalar }; }
    Vector2 operator-(float scalar) const { return Vector2{ x - scalar, y - scalar }; }
    Vector2 operator*(float scalar) const { return Vector2{ x * scalar, y * scalar }; }
    Vector2 operator/(float scalar) const { return Vector2{ x / scalar, y / scalar }; }

    Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
    Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
    Vector2& operator*=(const Vector2& other) { x *= other.x; y *= other.y; return *this; }
    Vector2& operator/=(const Vector2& other) { x /= other.x; y /= other.y; return *this; }

    Vector2& operator+=(float scalar) { x += scalar; y += scalar; return *this; }
    Vector2& operator-=(float scalar) { x -= scalar; y -= scalar; return *this; }
    Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    Vector2 operator-() const { return Vector2(-x, -y); }
    Vector2 operator+() const { return Vector2(+x, +y); }

    bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Vector2& other) const { return x != other.x || y != other.y; }
    bool operator>=(const Vector2& other) const { return x >= other.x && y >= other.y; }
    bool operator<=(const Vector2& other) const { return x <= other.x && y <= other.y; }
    bool operator>(const Vector2& other) const { return x > other.x && y > other.y; };
    bool operator<(const Vector2& other) const { return x < other.x && y < other.y; };

    //float operator[](float index) const {};

    static Vector2 ZERO() { return Vector2(0.0f, 0.0f); }
    static Vector2 ONE() { return Vector2(1.0f, 1.0f); }
    static Vector2 LEFT() { return Vector2(-1.0f, 0.0f); }
    static Vector2 RIGHT() { return Vector2(1.0f, 0.0f); }
    static Vector2 UP() { return Vector2(0.0f, 1.0f); }
    static Vector2 DOWN() { return Vector2(0.0f, -1.0f); }

    float radians(float degrees) { return degrees * (PI / 180.0f); }

    float normalize() {
        float length = magnitude();
        if (length != 0) { x /= length; y /= length; }
        return length;
    }

    float magnitude() const { return sqrt(x * x + y * y); }
    float magnitudeSquared() const { return x * x + y * y; }

    float dot(const Vector2& other) const { return (x * other.x) + (y * other.y); }

    static float cross(const Vector2& vector1, const Vector2& vector2) { return vector1.x * vector2.y - vector1.y * vector2.x; }

    Vector2 rotate(const Vector2& vector, float angleInRadians)
    {
        float cosTheta = cos(angleInRadians);
        float sinTheta = sin(angleInRadians);
        return Vector2(cosTheta * vector.x - sinTheta * vector.y, sinTheta * vector.x + cosTheta * vector.y);
    }

    Vector2 rotate(float angleInRadians) const {
        float cosTheta = cos(angleInRadians);
        float sinTheta = sin(angleInRadians);
        return Vector2( cosTheta * x - sinTheta * y, sinTheta * x + cosTheta * y);
    }

    float angle(const Vector2& vec1, const Vector2& vec2) {
        // Calculate the dot product of the two vectors
        float dot = vec1.dot(vec2);

        // Calculate the magnitudes of the vectors
        float mag1 = vec1.magnitude();
        float mag2 = vec1.magnitude();

        // Ensure that the magnitudes are not zero to avoid division by zero
        if (mag1 == 0.0f || mag2 == 0.0f) {
            // Return 0 if either magnitude is zero
            return 0.0f;
        }

        // Calculate the cosine of the angle using the dot product formula
        float cosTheta = dot / (mag1 * mag2);

        // Clamp the value to [-1, 1] to avoid floating-point inaccuracies
        cosTheta = Min(Max(cosTheta, -1.0f), 1.0f);

        // Calculate the angle in radians using the arccosine function
        float angleRad = acos(cosTheta);

        // Convert the angle from radians to degrees
        float angleDeg = angleRad * (180.0f / PI);

        return angleDeg;
    }


    // Distance between two vectors
    static float distance(const Vector2& vec1, const Vector2& vec2) { return (vec1 - vec2).magnitude(); }
};
inline Vector2 operator+(float scalar, const Vector2& vector) { return Vector2(scalar + vector.x, scalar + vector.y); }
inline Vector2 operator-(float scalar, const Vector2& vector) { return Vector2(scalar - vector.x, scalar - vector.y); }
inline Vector2 operator*(float scalar, const Vector2& vector) { return Vector2(scalar * vector.x, scalar * vector.y); }
inline Vector2 operator/(float scalar, const Vector2& vector) { return Vector2(scalar / vector.x, scalar / vector.y); }

struct Vector2i : public Variant
{
    int x, y;

    constexpr Vector2i() : x(0.0f), y(0.0f) {}
    constexpr Vector2i(int value) : x(value), y(value) {}
    //constexpr Vector2i(Vector2& vec2) : x((int) vec2.x), y((int) vec2.y) {}
    constexpr Vector2i(int x, int y) : x(x), y(y) {}

    Vector2i operator+(const Vector2i& other) const { return Vector2i{ x + other.x, y + other.y }; }
    Vector2i operator-(const Vector2i& other) const { return Vector2i{ x - other.x, y - other.y }; }
    Vector2i operator*(const Vector2i& other) const { return Vector2i{ x * other.x, y * other.y }; }
    Vector2i operator/(const Vector2i& other) const { return Vector2i{ x / other.x, y / other.y }; }
    Vector2i operator%(const Vector2i& other) const { return Vector2i{ x % other.x, y % other.y }; }

    Vector2i operator+(int scalar) const { return Vector2i{ x + scalar, y + scalar }; }
    Vector2i operator-(int scalar) const { return Vector2i{ x - scalar, y - scalar }; }
    Vector2i operator*(int scalar) const { return Vector2i{ x * scalar, y * scalar }; }
    Vector2i operator/(int scalar) const { return Vector2i{ x / scalar, y / scalar }; }
    Vector2i operator%(int scalar) const { return Vector2i{ x % scalar, y % scalar }; }

    Vector2i& operator+=(const Vector2i& other) { x += other.x; y += other.y; return *this; }
    Vector2i& operator-=(const Vector2i& other) { x -= other.x; y -= other.y; return *this; }
    Vector2i& operator*=(const Vector2i& other) { x *= other.x; y *= other.y; return *this; }
    Vector2i& operator/=(const Vector2i& other) { x /= other.x; y /= other.y; return *this; }

    Vector2i& operator+=(int scalar) { x += scalar; y += scalar; return *this; }
    Vector2i& operator-=(int scalar) { x -= scalar; y -= scalar; return *this; }
    Vector2i& operator*=(int scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2i& operator/=(int scalar) { x /= scalar; y /= scalar; return *this; }

    Vector2i operator-() const { return Vector2i(-x, -y); }
    Vector2i operator+() const { return Vector2i(+x, +y); }

    bool operator==(const Vector2i& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Vector2i& other) const { return x != other.x || y != other.y; }
    bool operator>=(const Vector2i& other) const { return x >= other.x && y >= other.y; }
    bool operator<=(const Vector2i& other) const { return x <= other.x && y <= other.y; }
    bool operator>(const Vector2i& other) const { return x > other.x && y > other.y; };
    bool operator<(const Vector2i& other) const { return x < other.x && y < other.y; };

    //int operator[](int index) const {};
};
inline Vector2i operator+(int scalar, const Vector2i& vector) { return Vector2i(scalar + vector.x, scalar + vector.y); }
inline Vector2i operator-(int scalar, const Vector2i& vector) { return Vector2i(scalar - vector.x, scalar - vector.y); }
inline Vector2i operator*(int scalar, const Vector2i& vector) { return Vector2i(scalar * vector.x, scalar * vector.y); }
inline Vector2i operator/(int scalar, const Vector2i& vector) { return Vector2i(scalar / vector.x, scalar / vector.y); }
inline Vector2i operator%(int scalar, const Vector2i& vector) { return Vector2i(scalar % vector.x, scalar % vector.y); }

struct Vector3 : public Variant
{
    float x, y, z;

    constexpr Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    constexpr Vector3(float value) : x(value), y(value), z(value) {}
    constexpr Vector3(Vector3i vector3i) : x((float) vector3i.x), y((float)vector3i.y), z((float)vector3i.z) {}
    constexpr Vector3(int x, int y, int z) : x((float) x), y((float) y), z((float) z) {}
    constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const { return Vector3{ x + other.x, y + other.y, z + other.z }; }
    Vector3 operator-(const Vector3& other) const { return Vector3{ x - other.x, y - other.y, z - other.z }; }
    Vector3 operator*(const Vector3& other) const { return Vector3{ x * other.x, y * other.y, z * other.z }; }
    Vector3 operator/(const Vector3& other) const { return Vector3{ x / other.x, y / other.y, z / other.z }; }

    Vector3 operator+(float scalar) const { return Vector3{ x + scalar, y + scalar, z + scalar }; }
    Vector3 operator-(float scalar) const { return Vector3{ x - scalar, y - scalar, z - scalar }; }
    Vector3 operator*(float scalar) const { return Vector3{ x * scalar, y * scalar, z * scalar }; }
    Vector3 operator/(float scalar) const { return Vector3{ x / scalar, y / scalar, z / scalar }; }

    Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    Vector3& operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    Vector3& operator*=(const Vector3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
    Vector3& operator/=(const Vector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

    Vector3& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; return *this; }
    Vector3& operator-=(float scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
    Vector3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    Vector3& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    Vector3 operator+() const { return Vector3(+x, +y, +z); }

    bool operator==(const Vector3& other) const { return x == other.x && y == other.y && z == other.z; }
    bool operator!=(const Vector3& other) const { return x != other.x || y != other.y || z != other.z; }
    bool operator>=(const Vector3& other) const { return x >= other.x && y >= other.y && z >= other.z; }
    bool operator<=(const Vector3& other) const { return x <= other.x && y <= other.y && z <= other.z; }
    bool operator>(const Vector3& other) const { return x > other.x && y > other.y && z > other.z; };
    bool operator<(const Vector3& other) const { return x < other.x && y < other.y && z < other.z; };

    //float operator[](float index) const {};


    static Vector3 ZERO() { return Vector3(0.0f, 0.0f, 0.0f); }
    static Vector3 ONE() { return Vector3(1.0f, 1.0f, 0.0f); }
    static Vector3 LEFT() { return Vector3(-1.0f, 0.0f, 0.0f); }
    static Vector3 RIGHT() { return Vector3(1.0f, 0.0f, 0.0f); }
    static Vector3 UP() { return Vector3(0.0f, 1.0f, 0.0f); }
    static Vector3 DOWN() { return Vector3(0.0f, -1.0f, 0.0f); }
    static Vector3 FORWARD() { return Vector3(0.0f, 0.0f, -1.0f); }
    static Vector3 BACK() { return Vector3(0.0f, 0.0f, 1.0f); }

    // Magnitude operator
    float magnitude() const { return sqrt(x * x + y * y + z * z); }
    float magnitudeSquared() const { return x * x + y * y + z * z; }

    // Dot-Product operator
    float dotProduct(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }

    // Normalize operator
    Vector3 normalize() const {
        float mag = sqrt(this->x * x + y * y + z * z);
        if (mag != 0.0f)
            return { x / mag, y / mag, z / mag };
        else
            return { 0.0f, 0.0f, 0.0f }; // Return zero vector if magnitude is zero
    }

    // Cross-Product operator
    Vector3 cross(const Vector3& other) const { return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }

    // Distance between two vectors
    static float distance(const Vector3& vec1, const Vector3& vec2) { return (vec1 - vec2).magnitude(); }
};
inline Vector3 operator+(float scalar, const Vector3& vector) { return Vector3(scalar + vector.x, scalar + vector.y, scalar + vector.z); }
inline Vector3 operator-(float scalar, const Vector3& vector) { return Vector3(scalar - vector.x, scalar - vector.y, scalar - vector.z); }
inline Vector3 operator*(float scalar, const Vector3& vector) { return Vector3(scalar * vector.x, scalar * vector.y, scalar * vector.z); }
inline Vector3 operator/(float scalar, const Vector3& vector) { return Vector3(scalar / vector.x, scalar / vector.y, scalar / vector.z); }

struct Vector3i : public Variant
{
    int x, y, z;

    constexpr Vector3i() : x(0), y(0), z(0) {}
    constexpr Vector3i(int value) : x(value), y(value), z(value) {}
    //constexpr Vector3i(Vector3& vector3) : x((int) vector3.x), y((int) vector3.y), z((int) vector3.z) {}
    constexpr Vector3i(int x, int y, int z) : x(x), y(y), z(z) {}

    Vector3i operator+(const Vector3i& other) const { return Vector3i{ x + other.x, y + other.y, z + other.z }; }
    Vector3i operator-(const Vector3i& other) const { return Vector3i{ x - other.x, y - other.y, z - other.z }; }
    Vector3i operator*(const Vector3i& other) const { return Vector3i{ x * other.x, y * other.y, z * other.z }; }
    Vector3i operator/(const Vector3i& other) const { return Vector3i{ x / other.x, y / other.y, z / other.z }; }
    Vector3i operator%(const Vector3i& other) const { return Vector3i{ x % other.x, y % other.y, z % other.z }; }

    Vector3i operator+(int scalar) const { return Vector3i{ x + scalar, y + scalar, z + scalar }; }
    Vector3i operator-(int scalar) const { return Vector3i{ x - scalar, y - scalar, z - scalar }; }
    Vector3i operator*(int scalar) const { return Vector3i{ x * scalar, y * scalar, z * scalar }; }
    Vector3i operator/(int scalar) const { return Vector3i{ x / scalar, y / scalar, z / scalar }; }
    Vector3i operator%(int scalar) const { return Vector3i{ x % scalar, y % scalar, z % scalar }; }

    Vector3i& operator+=(const Vector3i& other) { x += other.x; y += other.y; z += other.z; return *this; }
    Vector3i& operator-=(const Vector3i& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    Vector3i& operator*=(const Vector3i& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
    Vector3i& operator/=(const Vector3i& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

    Vector3i& operator+=(int scalar) { x += scalar; y += scalar; z += scalar; return *this; }
    Vector3i& operator-=(int scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
    Vector3i& operator*=(int scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    Vector3i& operator/=(int scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    Vector3i operator-() const { return Vector3i(-x, -y, -z); }
    Vector3i operator+() const { return Vector3i(+x, +y, +z); }

    bool operator==(const Vector3i& other) const { return x == other.x && y == other.y && z == other.z; }
    bool operator!=(const Vector3i& other) const { return x != other.x || y != other.y || z != other.z; }
    bool operator>=(const Vector3i& other) const { return x >= other.x && y >= other.y && z >= other.z; }
    bool operator<=(const Vector3i& other) const { return x <= other.x && y <= other.y && z <= other.z; }
    bool operator>(const Vector3i& other) const { return x > other.x && y > other.y && z > other.z; };
    bool operator<(const Vector3i& other) const { return x < other.x && y < other.y && z < other.z; };

    //int operator[](int index) const {};

};
inline Vector3i operator+(int scalar, const Vector3i& vector) { return Vector3i(scalar + vector.x, scalar + vector.y, scalar + vector.z); }
inline Vector3i operator-(int scalar, const Vector3i& vector) { return Vector3i(scalar - vector.x, scalar - vector.y, scalar - vector.z); }
inline Vector3i operator*(int scalar, const Vector3i& vector) { return Vector3i(scalar * vector.x, scalar * vector.y, scalar * vector.z); }
inline Vector3i operator/(int scalar, const Vector3i& vector) { return Vector3i(scalar / vector.x, scalar / vector.y, scalar / vector.z); }
inline Vector3i operator%(int scalar, const Vector3i& vector) { return Vector3i(scalar % vector.x, scalar % vector.y, scalar % vector.z); }

struct Vector4 : public Variant
{
    float x, y, z, w;

    constexpr Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr Vector4(float value) : x(value), y(value), z(value), w(value) {}
    constexpr Vector4(Vector4i vector4i) : x((float) vector4i.x), y((float) vector4i.y), z((float) vector4i.z), w((float) vector4i.w) {}
    constexpr Vector4(int x, int y, int z, int w) : x((int) x), y((int) y), z((int) z), w((int) w) {}
    constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vector4 operator+(const Vector4& other) const { return Vector4{ x + other.x, y + other.y, z + other.z, w + other.w }; }
    Vector4 operator-(const Vector4& other) const { return Vector4{ x - other.x, y - other.y, z - other.z, w - other.w }; }
    Vector4 operator*(const Vector4& other) const { return Vector4{ x * other.x, y * other.y, z * other.z, w * other.w }; }
    Vector4 operator/(const Vector4& other) const { return Vector4{ x / other.x, y / other.y, z / other.z, w / other.w }; }

    Vector4 operator+(float scalar) const { return Vector4{ x + scalar, y + scalar, z + scalar, w + scalar }; }
    Vector4 operator-(float scalar) const { return Vector4{ x - scalar, y - scalar, z + scalar, w + scalar }; }
    Vector4 operator*(float scalar) const { return Vector4{ x * scalar, y * scalar, z + scalar, w + scalar }; }
    Vector4 operator/(float scalar) const { return Vector4{ x / scalar, y / scalar, z + scalar, w + scalar }; }

    Vector4& operator+=(const Vector4& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
    Vector4& operator-=(const Vector4& other) { x -= other.x; y -= other.y; z += other.z; w += other.w; return *this; }
    Vector4& operator*=(const Vector4& other) { x *= other.x; y *= other.y; z += other.z; w += other.w; return *this; }
    Vector4& operator/=(const Vector4& other) { x /= other.x; y /= other.y; z += other.z; w += other.w; return *this; }

    Vector4& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
    Vector4& operator-=(float scalar) { x -= scalar; y -= scalar; z += scalar; w += scalar; return *this; }
    Vector4& operator*=(float scalar) { x *= scalar; y *= scalar; z += scalar; w += scalar; return *this; }
    Vector4& operator/=(float scalar) { x /= scalar; y /= scalar; z += scalar; w += scalar; return *this; }

    Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }
    Vector4 operator+() const { return Vector4(+x, +y, +z, +w); }

    // Comparison operators
    bool operator==(const Vector4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
    bool operator!=(const Vector4& other) const { return x != other.x || y != other.y && z != other.z && w != other.w; }
    bool operator>=(const Vector4& other) const { return x >= other.x && y >= other.y && z >= other.z && w >= other.w; }
    bool operator<=(const Vector4& other) const { return x <= other.x && y <= other.y && z <= other.z && w <= other.w; }
    bool operator>(const Vector4& other) const { return x > other.x && y > other.y && z > other.z && w > other.w; };
    bool operator<(const Vector4& other) const { return x < other.x && y < other.y && z < other.z && w < other.w; };

    //float operator[](float index) const {};

    static Vector4 ZERO() { return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
    static Vector4 ONE() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
};
inline Vector4 operator+(float scalar, const Vector4& vector) { return Vector4(scalar + vector.x, scalar + vector.y, scalar + vector.z, scalar + vector.w); }
inline Vector4 operator-(float scalar, const Vector4& vector) { return Vector4(scalar - vector.x, scalar - vector.y, scalar - vector.z, scalar - vector.w); }
inline Vector4 operator*(float scalar, const Vector4& vector) { return Vector4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w); }
inline Vector4 operator/(float scalar, const Vector4& vector) { return Vector4(scalar / vector.x, scalar / vector.y, scalar / vector.z, scalar / vector.w); }

struct Vector4i : public Variant
{
    int x, y, z, w;

    constexpr Vector4i() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr Vector4i(int value) : x(value), y(value), z(value), w(value) {}
    //constexpr Vector4i(Vector4& vector4) : x((int) vector4.x), y((int) vector4.y), z((int) vector4.z), w((int) vector4.w) {}
    constexpr Vector4i(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}

    Vector4i operator+(const Vector4i& other) const { return Vector4i{ x + other.x, y + other.y, z + other.z, w + other.w }; }
    Vector4i operator-(const Vector4i& other) const { return Vector4i{ x - other.x, y - other.y, z - other.z, w - other.w }; }
    Vector4i operator*(const Vector4i& other) const { return Vector4i{ x * other.x, y * other.y, z * other.z, w * other.w }; }
    Vector4i operator/(const Vector4i& other) const { return Vector4i{ x / other.x, y / other.y, z / other.z, w / other.w }; }
    Vector4i operator%(const Vector4i& other) const { return Vector4i{ x % other.x, y % other.y, z % other.z, w % other.w }; }

    Vector4i operator+(int scalar) const { return Vector4i{ x + scalar, y + scalar, z + scalar, w + scalar }; }
    Vector4i operator-(int scalar) const { return Vector4i{ x - scalar, y - scalar, z - scalar, w - scalar }; }
    Vector4i operator*(int scalar) const { return Vector4i{ x * scalar, y * scalar, z * scalar, w * scalar }; }
    Vector4i operator/(int scalar) const { return Vector4i{ x / scalar, y / scalar, z / scalar, w / scalar }; }
    Vector4i operator%(int scalar) const { return Vector4i{ x % scalar, y % scalar, z % scalar, w % scalar }; }

    Vector4i& operator+=(const Vector4i& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
    Vector4i& operator-=(const Vector4i& other) { x -= other.x; y -= other.y; z += other.z; w += other.w; return *this; }
    Vector4i& operator*=(const Vector4i& other) { x *= other.x; y *= other.y; z += other.z; w += other.w; return *this; }
    Vector4i& operator/=(const Vector4i& other) { x /= other.x; y /= other.y; z += other.z; w += other.w; return *this; }

    Vector4i& operator+=(int scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
    Vector4i& operator-=(int scalar) { x -= scalar; y -= scalar; z += scalar; w += scalar; return *this; }
    Vector4i& operator*=(int scalar) { x *= scalar; y *= scalar; z += scalar; w += scalar; return *this; }
    Vector4i& operator/=(int scalar) { x /= scalar; y /= scalar; z += scalar; w += scalar; return *this; }

    Vector4i operator-() const { return Vector4i(-x, -y, -z, -w); }
    Vector4i operator+() const { return Vector4i(+x, +y, +z, +w); }

    bool operator==(const Vector4i& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
    bool operator!=(const Vector4i& other) const { return x != other.x || y != other.y && z != other.z && w != other.w; }
    bool operator>=(const Vector4i& other) const { return x >= other.x && y >= other.y && z >= other.z && w >= other.w; }
    bool operator<=(const Vector4i& other) const { return x <= other.x && y <= other.y && z <= other.z && w <= other.w; }
    bool operator>(const Vector4i& other) const { return x > other.x && y > other.y && z > other.z && w > other.w; };
    bool operator<(const Vector4i& other) const { return x < other.x && y < other.y && z < other.z && w < other.w; };

    //int operator[](int index) const {};
    static Vector4i ZERO() { return Vector4i(0, 0, 0, 0); }
    static Vector4i ONE() { return Vector4i(1, 1, 1, 1); }
};
inline Vector4i operator+(int scalar, const Vector4i& vector) { return Vector4i(scalar + vector.x, scalar + vector.y, scalar + vector.z, scalar + vector.w); }
inline Vector4i operator-(int scalar, const Vector4i& vector) { return Vector4i(scalar - vector.x, scalar - vector.y, scalar - vector.z, scalar - vector.w); }
inline Vector4i operator*(int scalar, const Vector4i& vector) { return Vector4i(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w); }
inline Vector4i operator/(int scalar, const Vector4i& vector) { return Vector4i(scalar / vector.x, scalar / vector.y, scalar / vector.z, scalar / vector.w); }
inline Vector4i operator%(int scalar, const Vector4i& vector) { return Vector4i(scalar % vector.x, scalar % vector.y, scalar % vector.z, scalar % vector.w); }

template<typename KeyType, typename ValueType>
class TMap : public Variant{
public:
    // Add a key-value pair to the dictionary
    void add(const KeyType& key, const ValueType& value) {
        dict[key] = value;
    }

    // Get the value associated with the key
    bool get(const KeyType& key, ValueType& value) const {
        auto it = dict.find(key);
        if (it != dict.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    // Remove a key-value pair from the dictionary
    bool remove(const KeyType& key) {
        auto it = dict.find(key);
        if (it != dict.end()) {
            dict.erase(it);
            return true;
        }
        return false;
    }

    // Check if the dictionary contains a key
    bool contains(const KeyType& key) const {
        return dict.find(key) != dict.end();
    }

    // Print all key-value pairs
    void print() const {
        for (const auto& pair : dict) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }
    }

private:
    std::unordered_map<KeyType, ValueType> dict;
};

template<typename T>
class TArray : public Variant
{
public:
    typedef T value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;

    Vector() : Size(0), Capacity(0), Data(nullptr) {}

    Vector(const Vector<T>& src) : Size(0), Capacity(0), Data(nullptr) {
        operator=(src);
    }

    Vector(Vector<T>&& src) noexcept : Size(src.Size), Capacity(src.Capacity), Data(src.Data) {
        src.Size = 0;
        src.Capacity = 0;
        src.Data = nullptr;
    }

    Vector<T>& operator=(const Vector<T>& src) {
        if (this != &src) {
            clear();
            resize(src.Size);
            if (src.Data) {
                for (int i = 0; i < Size; ++i) {
                    new(&Data[i]) T(src.Data[i]);
                }
            }
        }
        return *this;
    }

    Vector<T>& operator=(Vector<T>&& src) noexcept {
        if (this != &src) {
            clear();
            Size = src.Size;
            Capacity = src.Capacity;
            Data = src.Data;
            src.Size = 0;
            src.Capacity = 0;
            src.Data = nullptr;
        }
        return *this;
    }

    ~Vector() {
        clear();
    }

    void clear() {
        if (Data) {
            for (int i = 0; i < Size; ++i) {
                Data[i].~T();
            }
            free(Data);
            Data = nullptr;
            Size = Capacity = 0;
        }
    }

    bool empty() const {
        return Size == 0;
    }

    int size() const {
        return Size;
    }

    int size_in_bytes() const {
        return Size * sizeof(T);
    }

    int max_size() const {
        return (int)((size_t)-1 / sizeof(T));
    }

    int capacity() const {
        return Capacity;
    }

    T& operator[](int i) {
        assert(i >= 0 && i < Size);
        return Data[i];
    }

    const T& operator[](int i) const {
        assert(i >= 0 && i < Size);
        return Data[i];
    }

    T* begin() {
        return Data;
    }

    const T* begin() const {
        return Data;
    }

    T* end() {
        return Data + Size;
    }

    const T* end() const {
        return Data + Size;
    }

    T& front() {
        assert(Size > 0);
        return Data[0];
    }

    const T& front() const {
        assert(Size > 0);
        return Data[0];
    }

    T& back() {
        assert(Size > 0);
        return Data[Size - 1];
    }

    const T& back() const {
        assert(Size > 0);
        return Data[Size - 1];
    }

    void swap(Vector<T>& rhs) {
        T* tmp_data = rhs.Data;
        rhs.Data = Data;
        Data = tmp_data;

        int tmp_size = rhs.Size;
        rhs.Size = Size;
        Size = tmp_size;

        int tmp_capacity = rhs.Capacity;
        rhs.Capacity = Capacity;
        Capacity = tmp_capacity;
    }

    void resize(int new_size) {
        if (new_size > Capacity) {
            reserve(_grow_capacity(new_size));
        }
        for (int i = Size; i < new_size; ++i) {
            new(&Data[i]) T();
        }
        for (int i = new_size; i < Size; ++i) {
            Data[i].~T();
        }
        Size = new_size;
    }

    void resize(int new_size, const T& v) {
        if (new_size > Capacity) {
            reserve(_grow_capacity(new_size));
        }
        for (int i = Size; i < new_size; ++i) {
            new(&Data[i]) T(v);
        }
        for (int i = new_size; i < Size; ++i) {
            Data[i].~T();
        }
        Size = new_size;
    }

    void shrink(int new_size) {
        assert(new_size <= Size);
        for (int i = new_size; i < Size; ++i) {
            Data[i].~T();
        }
        Size = new_size;
    }

    /**/
    void reserve(int new_capacity) {
        if (new_capacity <= Capacity) return;
        T* new_data = (T*)malloc(new_capacity * sizeof(T));
        if (Data) {
            for (int i = 0; i < Size; ++i) {
                new(&new_data[i]) T(std::move(Data[i]));
                Data[i].~T();
            }
            free(Data);
        }
        Data = new_data;
        Capacity = new_capacity;
    }

    void reserve_discard(int new_capacity) {
        if (new_capacity <= Capacity) return;
        if (Data) {
            free(Data);
        }
        Data = (T*)malloc(new_capacity * sizeof(T));
        Capacity = new_capacity;
    }

    void push_back(const T& v) {
        if (Size == Capacity) {
            reserve(_grow_capacity(Size + 1));
        }
        new(&Data[Size]) T(v);
        Size++;
    }

    void push_back(T&& v) {
        if (Size == Capacity) {
            reserve(_grow_capacity(Size + 1));
        }
        new(&Data[Size]) T(std::move(v));
        Size++;
    }

    void pop_back() {
        assert(Size > 0);
        Data[Size - 1].~T();
        Size--;
    }

    void push_front(const T& v) {
        if (Size == 0) {
            push_back(v);
        }
        else {
            insert(Data, v);
        }
    }

    T* erase(const T* it) {
        assert(it >= Data && it < Data + Size);
        const ptrdiff_t off = it - Data;
        Data[off].~T();
        memmove(Data + off, Data + off + 1, (Size - off - 1) * sizeof(T));
        Size--;
        return Data + off;
    }

    T* erase(const T* it, const T* it_last) {
        assert(it >= Data && it < Data + Size && it_last >= it && it_last <= Data + Size);
        const ptrdiff_t count = it_last - it;
        const ptrdiff_t off = it - Data;
        for (ptrdiff_t i = 0; i < count; ++i) {
            Data[off + i].~T();
        }
        memmove(Data + off, Data + off + count, (Size - off - count) * sizeof(T));
        Size -= (int)count;
        return Data + off;
    }

    T* erase_unsorted(const T* it) {
        assert(it >= Data && it < Data + Size);
        const ptrdiff_t off = it - Data;
        Data[off].~T();
        if (it < Data + Size - 1) {
            new(&Data[off]) T(std::move(Data[Size - 1]));
            Data[Size - 1].~T();
        }
        Size--;
        return Data + off;
    }

    T* insert(const T* it, const T& v) {
        assert(it >= Data && it <= Data + Size);
        const ptrdiff_t off = it - Data;
        if (Size == Capacity) {
            reserve(_grow_capacity(Size + 1));
        }
        if (off < Size) {
            memmove(Data + off + 1, Data + off, (Size - off) * sizeof(T));
        }
        new(&Data[off]) T(v);
        Size++;
        return Data + off;
    }

    bool contains(const T& v) const {
        return find(v) != end();
    }

    T* find(const T& v) {
        for (int i = 0; i < Size; ++i) {
            if (Data[i] == v) return &Data[i];
        }
        return end();
    }

    const T* find(const T& v) const {
        for (int i = 0; i < Size; ++i) {
            if (Data[i] == v) return &Data[i];
        }
        return end();
    }

    int find_index(const T& v) const {
        const_iterator it = find(v);
        if (it == end()) return -1;
        return it - Data;
    }

    bool find_erase(const T& v) {
        const T* it = find(v);
        if (it < Data + Size) {
            erase(it);
            return true;
        }
        return false;
    }

    bool find_erase_unsorted(const T& v) {
        const T* it = find(v);
        if (it < Data + Size) {
            erase_unsorted(it);
            return true;
        }
        return false;
    }

    int index_from_ptr(const T* it) const {
        assert(it >= Data && it < Data + Size);
        return it - Data;
    }

private:
    int _grow_capacity(int sz) const {
        int new_capacity = Capacity ? (Capacity + Capacity / 2) : 8;
        return new_capacity > sz ? new_capacity : sz;
    }

    int Size;
    int Capacity;
    T* Data;
};

struct Rect : public Variant
{
    //float x, y, w, h;
    Vector2      min;    // Upper-left
    Vector2      max;    // Lower-right

    constexpr Rect()                                        : min(0.0f, 0.0f), max(0.0f, 0.0f)  {}
    constexpr Rect(const Vector2& min, const Vector2& max)  : min(min), max(max)                {}
    constexpr Rect(const Vector4& v)                        : min(v.x, v.y), max(v.z, v.w)      {}
    constexpr Rect(float x1, float y1, float x2, float y2)  : min(x1, y1), max(x2, y2)          {}

    float   GetWidth() const { return max.x - min.x; }
    float   GetHeight() const { return max.y - min.y; }
    float   GetArea() const { return (max.x - min.x) * (max.y - min.y); }
    bool    Contains(const Vector2& p) const    { return p.x     >= min.x && p.y     >= min.y && p.x     < max.x && p.y     < max.y; }
    bool    Contains(const Rect& r) const       { return r.min.x >= min.x && r.min.y >= min.y && r.max.x <= max.x && r.max.y <= max.y; }
    bool    ContainsWithPad(const Vector2& p, const Vector2& pad) const { return p.x >= min.x - pad.x && p.y >= min.y - pad.y && p.x < max.x + pad.x && p.y < max.y + pad.y; }
    bool    Overlaps(const Rect& r) const       { return r.min.y <  max.y && r.max.y >  min.y && r.min.x <  max.x && r.max.x >  min.x; }
    void    Add(const Vector2& p)               { if (min.x > p.x)     min.x = p.x;     if (min.y > p.y)     min.y = p.y;     if (max.x < p.x)     max.x = p.x;     if (max.y < p.y)     max.y = p.y; }
    void    Add(const Rect& r)                  { if (min.x > r.min.x) min.x = r.min.x; if (min.y > r.min.y) min.y = r.min.y; if (max.x < r.max.x) max.x = r.max.x; if (max.y < r.max.y) max.y = r.max.y; }
    void    Expand(const float amount)          { min.x -= amount;   min.y -= amount;   max.x += amount;   max.y += amount; }
    void    Expand(const Vector2& amount)       { min.x -= amount.x; min.y -= amount.y; max.x += amount.x; max.y += amount.y; }
    void    Translate(const Vector2& d)         { min.x += d.x; min.y += d.y; max.x += d.x; max.y += d.y; }
    void    TranslateX(float dx)                { min.x += dx; max.x += dx; }
    void    TranslateY(float dy)                { min.y += dy; max.y += dy; }
    void    ClipWith(const Rect& r)             { min = Max(min, r.min); max = Min(max, r.max); }
    void    ClipWithFull(const Rect& r)         { min = Clamp(min, r.min, r.max); max = Clamp(max, r.min, r.max); }
    void    Floor()                             { min.x = trunc(min.x); min.y = trunc(min.y); max.x = trunc(max.x); max.y = trunc(max.y); }
    bool    IsInverted() const                  { return min.x > max.x || min.y > max.y; }
    Vector2 GetCenter() const                   { return Vector2((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f); }
    Vector2 GetSize() const                     { return Vector2(max.x - min.x, max.y - min.y); }
    Vector2 GetTL() const                       { return min; }                   // Top-left
    Vector2 GetTR() const                       { return Vector2(max.x, min.y); } // Top-right
    Vector2 GetBL() const                       { return Vector2(min.x, max.y); } // Bottom-left
    Vector2 GetBR() const                       { return max; }                   // Bottom-right
    Vector4 ToVec4() const                      { return Vector4(min.x, min.y, max.x, max.y); }
};

struct Recti : public Variant
{
    //int x, y, w, h;
    Vector2i      min;    // Upper-left
    Vector2i      max;    // Lower-right

    constexpr Recti()                                        : min(0.0f, 0.0f), max(0.0f, 0.0f)  {}
    constexpr Recti(const Vector2i& min, const Vector2i& max)  : min(min), max(max)                {}
    constexpr Recti(const Vector4i& v)                        : min(v.x, v.y), max(v.z, v.w)      {}
    constexpr Recti(float x1, float y1, float x2, float y2)  : min(x1, y1), max(x2, y2)          {}

    float   GetWidth() const { return max.x - min.x; }
    float   GetHeight() const { return max.y - min.y; }
    float   GetArea() const { return (max.x - min.x) * (max.y - min.y); }
    bool    Contains(const Vector2& p) const    { return p.x     >= min.x && p.y     >= min.y && p.x     < max.x && p.y     < max.y; }
    bool    Contains(const Recti& r) const       { return r.min.x >= min.x && r.min.y >= min.y && r.max.x <= max.x && r.max.y <= max.y; }
    bool    ContainsWithPad(const Vector2& p, const Vector2& pad) const { return p.x >= min.x - pad.x && p.y >= min.y - pad.y && p.x < max.x + pad.x && p.y < max.y + pad.y; }
    bool    Overlaps(const Recti& r) const       { return r.min.y <  max.y && r.max.y >  min.y && r.min.x <  max.x && r.max.x >  min.x; }
    void    Add(const Vector2i& p)               { if (min.x > p.x)     min.x = p.x;     if (min.y > p.y)     min.y = p.y;     if (max.x < p.x)     max.x = p.x;     if (max.y < p.y)     max.y = p.y; }
    void    Add(const Recti& r)                  { if (min.x > r.min.x) min.x = r.min.x; if (min.y > r.min.y) min.y = r.min.y; if (max.x < r.max.x) max.x = r.max.x; if (max.y < r.max.y) max.y = r.max.y; }
    void    Expand(const float amount)          { min.x -= amount;   min.y -= amount;   max.x += amount;   max.y += amount; }
    void    Expand(const Vector2& amount)       { min.x -= amount.x; min.y -= amount.y; max.x += amount.x; max.y += amount.y; }
    void    Translate(const Vector2& d)         { min.x += d.x; min.y += d.y; max.x += d.x; max.y += d.y; }
    void    TranslateX(float dx)                { min.x += dx; max.x += dx; }
    void    TranslateY(float dy)                { min.y += dy; max.y += dy; }
    void    ClipWith(const Recti& r)             { min = Max(min, r.min); max = Min(max, r.max); }
    void    ClipWithFull(const Recti& r)         { min = Clamp(min, r.min, r.max); max = Clamp(max, r.min, r.max); }
    void    Floor()                             { min.x = trunc(min.x); min.y = trunc(min.y); max.x = trunc(max.x); max.y = trunc(max.y); }
    bool    IsInverted() const                  { return min.x > max.x || min.y > max.y; }
    Vector2i GetCenter() const                  { return Vector2i((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f); }
    Vector2i GetSize() const                    { return Vector2i(max.x - min.x, max.y - min.y); }
    Vector2i GetTL() const                      { return min; }                   // Top-left
    Vector2i GetTR() const                      { return Vector2i(max.x, min.y); } // Top-right
    Vector2i GetBL() const                      { return Vector2i(min.x, max.y); } // Bottom-left
    Vector2i GetBR() const                      { return max; }                   // Bottom-right
    Vector4i ToVec4() const                     { return Vector4i(min.x, min.y, max.x, max.y); }
};

struct Color : public Variant
{
    float r, g, b, a;

    // Default constructor
    constexpr Color()                                               : r(0.0f), g(0.0f), b(0.0f), a(255.0f) {}
    constexpr Color(float r, float g, float b, float a = 255.0f)    : r(r), g(g), b(b), a(a) {}
    constexpr Color(uint32 r, uint32 g, uint32 b, uint32 a = 255)   : r((float)r * (1.0f / 255.0f)), g((float)g * (1.0f / 255.0f)), b((float)b * (1.0f / 255.0f)), a((float)a* (1.0f / 255.0f)) {}
    constexpr Color(const Vector4& col)                             : r(col.x), g(col.y), b(col.z), a(col.w) {}

    // Color operations
    Color operator+(const Color& other) const { return Color{ r + other.r, g + other.g, b + other.b, a }; }
    Color operator-(const Color& other) const { return Color{ r - other.r, g - other.g, b - other.b, a }; }
    Color operator*(const Color& other) const { return Color{ r * other.r, g * other.g, b * other.b, a }; }
    Color operator/(const Color& other) const { return Color{ r / other.r, g / other.g, b / other.b, a }; }

    Color operator+(float scalar) const { return Color{ r + scalar, g + scalar, b + scalar, a }; }
    Color operator-(float scalar) const { return Color{ r - scalar, g - scalar, b - scalar, a }; }
    Color operator*(float scalar) const { return Color{ r * scalar, g * scalar, b * scalar, a }; }
    Color operator/(float scalar) const { return Color{ r / scalar, g / scalar, b / scalar, a }; }

    Color& operator+=(const Color& other) { r += other.r; g += other.g; b += other.b; return *this; }
    Color& operator-=(const Color& other) { r -= other.r; g -= other.g; b -= other.b; return *this; }
    Color& operator*=(const Color& other) { r *= other.r; g *= other.g; b *= other.b; return *this; }
    Color& operator/=(const Color& other) { r /= other.r; g /= other.g; b /= other.b; return *this; }

    Color& operator+=(float scalar) { r += scalar; g += scalar; b += scalar; return *this; }
    Color& operator-=(float scalar) { r -= scalar; g -= scalar; b -= scalar; return *this; }
    Color& operator*=(float scalar) { r *= scalar; g *= scalar; b *= scalar; return *this; }
    Color& operator/=(float scalar) { r /= scalar; g /= scalar; b /= scalar; return *this; }

    // Comparison operators
    bool operator==(const Color& other) const { return r == other.r && g == other.g && b == other.b && a == other.a; }
    bool operator!=(const Color& other) const { return !(*this == other); }

    // Static colors
    static Color RED()      { return Color(1.0f, 0.0f, 0.0f); }
    static Color GREEN()    { return Color(0.0f, 1.0f, 0.0f); }
    static Color BLUE()     { return Color(0.0f, 0.0f, 1.0f); }
    static Color WHITE()    { return Color(1.0f, 1.0f, 1.0f); }
    static Color BLACK()    { return Color(0.0f, 0.0f, 0.0f); }
    static Color YELLOW()   { return Color(1.0f, 1.0f, 0.0f); }
    static Color CYAN()     { return Color(0.0f, 1.0f, 1.0f); }
    static Color MAGENTA()  { return Color(1.0f, 0.0f, 1.0f); }


    void toHSV(float& h, float& s, float& v) const {
        float max = std::max({ r, g, b });
        float min = std::min({ r, g, b });
        v = max;

        float delta = max - min;
        if (max == 0) {
            s = 0;
            h = 0;
            return;
        }

        s = delta / max;

        if (r == max) {
            h = (g - b) / delta + (g < b ? 6 : 0);
        }
        else if (g == max) {
            h = (b - r) / delta + 2;
        }
        else {
            h = (r - g) / delta + 4;
        }

        h /= 6;
    }

    void toRGB(float h, float s, float v) {
        int i = static_cast<int>(h * 6);
        float f = h * 6 - i;
        float p = v * (1 - s);
        float q = v * (1 - f * s);
        float t = v * (1 - (1 - f) * s);

        switch (i % 6) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
        }
    }
};

// Color Utilities
    Color        ColorConvertU32ToFloat4(uint32 in);
    uint32         ColorConvertFloat4ToU32(const Color& in);
    void          ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
    void          ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);


struct Curve : public Variant{
    TArray<Vector2> values;

    static const int MIN_X = 0.f;
    static const int MAX_X = 1.f;

    float m_bake_interval;
    int m_pointCount;
    int bake_resolution = 100;




    struct Point {
        Vector2 position;
        float left_tangent = 0.0;
        float right_tangent = 0.0;
        TangentMode left_mode = TANGENT_FREE;
        TangentMode right_mode = TANGENT_FREE;

        Point() {
        }

        Point(const Vector2& p_position,
            real_t p_left = 0.0,
            real_t p_right = 0.0,
            TangentMode p_left_mode = TANGENT_FREE,
            TangentMode p_right_mode = TANGENT_FREE) {
            position = p_position;
            left_tangent = p_left;
            right_tangent = p_right;
            left_mode = p_left_mode;
            right_mode = p_right_mode;
        }
    };
    // Add a value to the curve
    void add_value(float value) {
        values.push_back(value);
    }

    void add_point(Vector2 position, float left_tangent = 0, float right_tangent = 0, TangentMode left_mode = 0, TangentMode right_mode = 0);

    // Linear interpolation
    Vector2 interpolate_linear(float t) const {
        if (values.size() < 2) {
            return Vector2::ZERO();
        }

        size_t segment = static_cast<size_t>(t * (values.size() - 1));
        float local_t = (t * (values.size() - 1)) - segment;

        float v0 = values[segment];
        float v1 = values[segment + 1];

        return v0 + local_t * (v1 - v0);
    }

    // Add a method to clear values
    void clear() {
        values.clear();
    }

    float get_point_left_tangent(int index) const {}

    Vector2 get_point_position(int index) const {}

    TangentMode get_point_right_mode(int index) const {}

    float get_point_right_tangent(int index) const {}

    void remove_point(int index) {}

    void set_point_left_mode(int index, TangentMode mode) {}

    void set_point_left_tangent(int index, float tangent) {}

    int set_point_offset(int index, float offset) {}

    void set_point_right_mode(int index, TangentMode mode) {}

    void set_point_right_tangent(int index, float tangent) {}

    void set_point_value(int index, float y) {}
};

struct Curve2D : public Variant
{
    // Add a point to the curve
    void add_point(const Vector2& point) {
        points.push_back(point);
    }
    void add_point(Vector2 position, Vector2 in = Vector2(0, 0), Vector2 out = Vector2(0, 0), int index = -1);

    // Linear interpolation
    Vector2 interpolate_linear(float t) const {
        if (points.size() < 2) {
            return Vector2(0.0f, 0.0f);
        }

        size_t segment = static_cast<size_t>(t * (points.size() - 1));
        float local_t = (t * (points.size() - 1)) - segment;

        const Vector2& p0 = points[segment];
        const Vector2& p1 = points[segment + 1];

        return Vector2(p0.x + local_t * (p1.x - p0.x), p0.y + local_t * (p1.y - p0.y));
    }

    // Add a method to clear points
    void clear() {
        points.clear();
    }


    float get_baked_length() const;

    TArray<Vector2> get_baked_points() const;

    float get_closest_offset(Vector2 to_point) const;

    Vector2  get_closest_point(Vector2 to_point) const;

    Vector2 get_point_in(int idx) const;

    Vector2 get_point_out(int idx) const;
    
    Vector2 get_point_position(int idx) const;

    void remove_point(int idx);

    Vector2 sample(int idx, float t) const;

    Vector2 sample_baked(float offset = 0.0, bool cubic = false) const;

    Transform2D sample_baked_with_rotation(float offset = 0.0, bool cubic = false) const;

    Vector2 samplef(float fofs) const;

    void set_point_in(int idx, Vector2 position);

    void set_point_out(int idx, Vector2 position);

    void set_point_position(int idx, Vector2 position);

    TArray<Vector2> tessellate(int max_stages = 5, float tolerance_degrees = 4) const;

    TArray<Vector2> tessellate_even_length(int max_stages = 5, float tolerance_length = 20.0) const;

    TArray<Vector2> points;
    float bake_interval;
    int m_pointCount;
};

struct Curve3D : public Variant
{
    // Add a point to the curve
    void add_point(const Vector3& point) {
        points.push_back(point);
    }

    add_point(Vector3 position, Vector3 in = Vector3(0, 0, 0), Vector3 out = Vector3(0, 0, 0), int index = -1)

    // Linear interpolation
    Vector3 interpolate_linear(float t) const {
        if (points.size() < 2) {
            return Vector3(0.0f, 0.0f, 0.0f);
        }

        size_t segment = static_cast<size_t>(t * (points.size() - 1));
        float local_t = (t * (points.size() - 1)) - segment;

        const Vector3& p0 = points[segment];
        const Vector3& p1 = points[segment + 1];

        return Vector3(p0.x + local_t * (p1.x - p0.x), p0.y + local_t * (p1.y - p0.y), p0.z + local_t * (p1.z - p0.z));
    }

    // Add a method to clear points
    void clear() {
        points.clear();
    }

    float get_baked_length() const;

    TArray<Vector3> get_baked_points() const;

    TArray<Vector3> get_baked_tilts() const;

    TArray<Vector3> get_baked_up_vectors() const;

    float get_closest_offset(Vector3 to_point) const;

    Vector3 get_closest_point(Vector3 to_point) const;

    Vector3 get_point_in(int idx) const;

    Vector3 get_point_out(int idx) const;

    Vector3 get_point_position(int idx) const;

    float get_point_tilt(int idx) const;

    void remove_point(int idx);

    Vector3 sample(int idx, float t) const;

    Vector3 sample_baked(float offset = 0.0, bool cubic = false) const;

    Vector3 sample_baked_up_vector(float offset, bool apply_tilt = false) const;

    Transform3D sample_baked_with_rotation(float offset = 0.0, bool cubic = false, bool apply_tilt = false) const;

    Vector3 samplef(float fofs) const;

    void set_point_in(int idx, Vector3 position);

    void set_point_out(int idx, Vector3 position);

    void set_point_position(int idx, Vector3 position);

    void set_point_tilt(int idx, float tilt);

    TArray<Vector3> tessellate(int max_stages = 5, float tolerance_degrees = 4) const;

    TArray<Vector3> tessellate_even_length(int max_stages = 5, float tolerance_length = 0.2) const;

    TArray<Vector3> points;
    float bake_interval;
    int m_pointCount;
    bool up_vector_enabled;
};

struct AABB2 : public Variant
{
    Vector2 position;
	Vector2 size;
} AABB2;

struct AABB3 : public Variant
{
    Vector3 position;
	Vector3 size;
} AABB3;

struct Transform2D : public Variant
{
	Vector2 position;
	Vector2 rotate;
	Vector2 scale;
} Transform;

struct Transform3D
{
	Vector3 position;
	Vector3 rotate;
	Vector3 scale;
} Transform;

#endif VARIANTS_H