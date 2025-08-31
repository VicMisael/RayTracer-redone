#pragma once
#include <Types.h>
#include <ColorVec.h>
#include <xsimd/xsimd.hpp>

struct ColorVec_SoA {
    batch_type r, g, b, a;

    ColorVec_SoA()
        : r(batch_type(0.0f)),
          g(batch_type(0.0f)),
          b(batch_type(0.0f)),
          a(batch_type(1.0f)) {}

    ColorVec_SoA(float rr, float gg, float bb, float aa = 1.0f)
        : r(batch_type(rr)),
          g(batch_type(gg)),
          b(batch_type(bb)),
          a(batch_type(aa)) {}

    explicit ColorVec_SoA(const ColorVec& c)
        : r(batch_type(c.r)),
          g(batch_type(c.g)),
          b(batch_type(c.b)),
          a(batch_type(c.a)) {}

    ColorVec_SoA(batch_type rr, batch_type gg, batch_type bb, batch_type aa)
        : r(rr), g(gg), b(bb), a(aa) {}

    ColorVec_SoA operator+(const ColorVec_SoA& other) const {
        return { r + other.r, g + other.g, b + other.b, a + other.a };
    }

    ColorVec_SoA& operator+=(const ColorVec_SoA& other) {
        r += other.r; g += other.g; b += other.b; a += other.a;
        return *this;
    }

    ColorVec_SoA operator*(float s) const {
        batch_type bs(s);
        return { r * bs, g * bs, b * bs, a * bs };
    }

    ColorVec_SoA operator*(const batch_type& s) const {
        return { r * s, g * s, b * s, a * s };
    }

    void clamp_to_x_if_bigger_than(float x, float val) {
        batch_type bx(x), bval(val);
        r = xsimd::select(r > bx, bval, r);
        g = xsimd::select(g > bx, bval, g);
        b = xsimd::select(b > bx, bval, b);
        a = xsimd::select(a > bx, bval, a);
    }

    ColorVec_SoA powc(float power) const {
        batch_type bp(power);
        return { xsimd::pow(r, bp), xsimd::pow(g, bp), xsimd::pow(b, bp), xsimd::pow(a, bp) };
    }

    ColorVec lane(size_t i) const {
        alignas(batch_type) float r_arr[batch_type::size];
        alignas(batch_type) float g_arr[batch_type::size];
        alignas(batch_type) float b_arr[batch_type::size];
        alignas(batch_type) float a_arr[batch_type::size];

        r.store_aligned(r_arr);
        g.store_aligned(g_arr);
        b.store_aligned(b_arr);
        a.store_aligned(a_arr);

        return ColorVec(r_arr[i], g_arr[i], b_arr[i], a_arr[i]);
    }
};
