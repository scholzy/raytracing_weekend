#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
    // Public methods
    public:
        // Constructors
        vec3() : e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        // x-, y-, and z- getters
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // Negation
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

        // Access
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        // Plus-equals
        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        // Times-equals
        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        // Divide-equals
        vec3& operator/=(const double t) {
            return *this *= 1 / t;
        }

        // Vector norm / length
        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        inline static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        bool near_zero() const {
            const auto cutoff = 1e-8;
            return (std::fabs(e[0]) < cutoff) && (std::fabs(e[1]) < cutoff) && (std::fabs(e[2]) < cutoff);
        }

    public:
        double e[3];
};

using point3 = vec3;
using color = vec3;

// Print vec3 to output stream
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

// Element-wise add two vec3
inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// And element-wise subtract
inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Element-wise multiply
inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Multiply by a scalar (s * v and v * s)
inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

// Divide by a scalar
inline vec3 operator/(const vec3 &v, double t) {
    return (1 / t) * v;
}

// Dot product aka scalar product
inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// Cross product to get the normal vector
inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// Normalise vector to unit
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) {
            continue;
        }
        return p;
    }
}

inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

#endif
