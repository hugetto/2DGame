//==============================================================================
/*
    Vector 2D Class
    Hug Beneit
*/
//==============================================================================

#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>

namespace hugGameEngine
{
    template <class T>
    class vec2 {
    public:
        /*The x and y values are public to give easier access for
        outside funtions. Accessors and mutators are not really
        necessary*/
        T x, y;

        //always initialize class members in the constructor
        vec2() :x(0), y(0) {}
        vec2(T x, T y) : x(x), y(y) {}
        vec2(const vec2& v) : x(v.x), y(v.y) {}

        inline vec2&    operator=   (const vec2& v)         { x = v.x; y = v.y; return *this; }
        inline vec2     operator+   (const vec2& v) const   { return vec2(x + v.x, y + v.y); }
        inline vec2     operator-   (const vec2& v) const   { return vec2(x - v.x, y - v.y); }
        inline vec2     operator*   (const vec2& v) const   { return vec2(x * v.x, y * v.y); }
        inline vec2&    operator+=  (const vec2& v)         { x += v.x; y += v.y; return *this; }
        inline vec2&    operator-=  (const vec2& v)         { x -= v.x; y -= v.y; return *this; }
        
        //inline vec2&    operator*=  (const& vec2 s)         { x *= s; y *= s; return *this; }
        //inline vec2&    operator/=  (const& vec2 s)         { x /= s; y /= s; return *this; }

        inline vec2     operator+   (const T& s) const      { return vec2(x + s, y + s); }
        inline vec2     operator-   (const T& s) const      { return vec2(x - s, y - s); }
        inline vec2     operator*   (const T& s) const      { return vec2(x * s, y * s); }
        inline vec2     operator/   (const T& s) const      { return vec2(x / s, y / s); }

        //Check if the Vectors have the same values (uses pairwise comparison of 'std::tuple' on the x,y values of L and R.
        inline friend bool operator==(const vec2& L, const vec2& R) { return std::tie(L.x, L.y) == std::tie(R.x, R.y); }
        inline friend bool operator!=(const vec2& L, const vec2& R) { return !(L == R); }

        inline void     set         (T x, T y)              { this->x = x; this->y = y; }

        inline void rotate(double deg) {
            double theta = deg / 180.0 * M_PI;
            double c = cos(theta);
            double s = sin(theta);
            double tx = x * c - y * s;
            double ty = x * s + y * c;
            x = tx;
            y = ty;
        }

        inline vec2& normalize() {
            if (length() == 0) return *this;
            *this *= (1.0 / length());
            return *this;
        }

        inline float dist   (vec2 v)    const   { vec2 d(v.x - x, v.y - y); return d.length(); }
        inline float length ()          const   { return std::sqrt(x * x + y * y); }
        inline void truncate(double length) {
            double angle = atan2f(y, x);
            x = length * cos(angle);
            y = length * sin(angle);
        }

        inline vec2 ortho() const { return vec2(y, -x); }

        //Product functions
        inline static float        dot     ( vec2& v1, vec2& v2 )  { return v1.x * v2.x + v1.y * v2.y; }
        inline static float        cross   ( vec2& v1, vec2& v2 )  { return (v1.x * v2.y) - (v1.y * v2.x); }
        inline const float         cross   ( vec2& v2 ) const      { return (x * v2.y) - (y * v2.x); }
        inline const const float   dot     ( vec2& v2 ) const      { return dot(*this, v2); }

        inline const vec2   perpCCW() const { return vec2(-y, x); }
        inline const vec2   perpCW()  const { return vec2(y, -x); }

    };

    typedef vec2<float> Vec2;
    typedef vec2<double> Vec2d;
    typedef vec2<int> Vec2i;

#define PI 3.14159265359
    template <class T>
    inline const T min2(const T val1, const T val2) { return val1 < val2 ? val1 : val2; }

    template <class T>
    inline const T max2(const T val1, const T val2) { return val1 > val2 ? val1 : val2; }

    template <class T>
    inline float sign(const T val) { return val > 0 ? 1 : val < 0 ? -1 : 0; }

    template <class T>
    inline const T clamp(const T x, const T min, const T max) { x < min ? return min : x > max ? return max : return x; }
}
#endif