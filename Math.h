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
/*                  Math.h

          Handles all basic Math Functions
*/
////////////////////////////////////////////////

#define PI 3.14159265358979323846f
#define EPSILON 0.000001f
#define DEG2RAD (PI/180.0f)
#define RAD2DEG (180.0f/PI)
#define SQRT12 0.7071067811865475244008443621048490
#define SQRT2 1.4142135623730950488016887242
#define LN2 0.6931471805599453094172321215
#define TAU 6.2831853071795864769252867666
#define E 2.7182818284590452353602874714

#define Fabs(X)           fabsf(X)
#define Sqrt(X)           sqrtf(X)
#define Fmod(X, Y)        fmodf((X), (Y))
#define Cos(X)            cosf(X)
#define Sin(X)            sinf(X)
#define Acos(X)           acosf(X)
#define Atan2(Y, X)       atan2f((Y), (X))
#define Atof(STR)         atof(STR)
#define Ceil(X)           ceilf(X)
static inline float  Pow(float x, float y)    { return powf(x, y); }          // DragBehaviorT/SliderBehaviorT uses ImPow with either float/double and need the precision
static inline double Pow(double x, double y)  { return pow(x, y); }
static inline float  Log(float x)             { return logf(x); }             // DragBehaviorT/SliderBehaviorT uses ImLog with either float/double and need the precision
static inline double Log(double x)            { return log(x); }
static inline int    Abs(int x)               { return x < 0 ? -x : x; }
static inline float  Abs(float x)             { return fabsf(x); }
static inline double Abs(double x)            { return fabs(x); }
static inline float  Sign(float x)            { return (x < 0.0f) ? -1.0f : (x > 0.0f) ? 1.0f : 0.0f; } // Sign operator - returns -1, 0 or 1 based on sign of argument
static inline double Sign(double x)           { return (x < 0.0) ? -1.0 : (x > 0.0) ? 1.0 : 0.0; }
static inline float  Rsqrt(float x)           { return 1.0f / sqrtf(x); }
static inline double Rsqrt(double x)          { return 1.0 / sqrt(x); }

template<typename T> static inline T Min(T lhs, T rhs)                        { return lhs < rhs ? lhs : rhs; }
template<typename T> static inline T Max(T lhs, T rhs)                        { return lhs >= rhs ? lhs : rhs; }
template<typename T> static inline T Clamp(T v, T mn, T mx)                   { return (v < mn) ? mn : (v > mx) ? mx : v; }
template<typename T> static inline T Lerp(T a, T b, float t)                  { return (T)(a + (b - a) * t); }
template<typename T> static inline void Swap(T& a, T& b)                      { T tmp = a; a = b; b = tmp; }
template<typename T> static inline T AddClampOverflow(T a, T b, T mn, T mx)   { if (b < 0 && (a < mn - b)) return mn; if (b > 0 && (a > mx - b)) return mx; return a + b; }
template<typename T> static inline T SubClampOverflow(T a, T b, T mn, T mx)   { if (b > 0 && (a < mn + b)) return mn; if (b < 0 && (a > mx + b)) return mx; return a - b; }