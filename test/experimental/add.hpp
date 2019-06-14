// intx: extended precision integer library.
// Copyright 2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#pragma once

#include <intx/intx.hpp>

namespace intx
{
inline uint256 add_asm(const uint256& x, const uint256& y) noexcept
{
    auto r = x;
    asm("add %4, %0\n"
        "adc %5, %1\n"
        "adc %6, %2\n"
        "adc %7, %3\n"
        : "+rm"(r.lo.lo), "+rm"(r.lo.hi), "+rm"(r.hi.lo), "+rm"(r.hi.hi)
        : "rm"(y.lo.lo), "rm"(y.lo.hi), "rm"(y.hi.lo), "rm"(y.hi.hi));
    return r;
}

inline uint256 add_c1(const uint256& x, const uint256& y) noexcept
{
    auto a = x.lo.lo + y.lo.lo;
    auto k1 = a < x.lo.lo;
    auto b = x.lo.hi + y.lo.hi + k1;
    auto k2 = (b < x.lo.hi) | (b < y.lo.hi);
    auto c = x.hi.lo + y.hi.lo + k2;
    auto k3 = (c < x.hi.lo) | (c < y.hi.lo);
    auto d = x.hi.hi + y.hi.hi + k3;
    return {{d, c}, {b, a}};
}

inline uint256 add_c2(const uint256& x, const uint256& y) noexcept
{
    auto a = x.lo.lo + y.lo.lo;
    auto k1 = a < x.lo.lo;
    auto b = x.lo.hi + y.lo.hi + k1;
    bool k2 = (b < x.lo.hi) | (b < k1);
    auto c = x.hi.lo + y.hi.lo + k2;
    auto k3 = (c < x.hi.lo) | (c < k2);
    auto d = x.hi.hi + y.hi.hi + k3;
    return {{d, c}, {b, a}};
}

inline uint256 add_c3(const uint256& x, const uint256& y) noexcept
{
    auto a = x.lo.lo + y.lo.lo;
    auto k1 = a < x.lo.lo;

    auto b = x.lo.hi + y.lo.hi;
    auto k2 = b < x.lo.hi;
    b += k1;
    auto k3 = b < k1;

    auto c = x.hi.lo + y.hi.lo;
    auto k4 = c < x.hi.lo;
    c += k2;
    auto k5 = c < k2;
    c += k3;
    auto k6 = c < k3;

    auto d = x.hi.hi + y.hi.hi + k4 + k5 + k6;
    return {{d, c}, {b, a}};
}

inline uint256 add_c4(const uint256& x, const uint256& y) noexcept
{
    auto a = x.lo.lo + y.lo.lo;
    auto k1 = a < x.lo.lo;

    auto b = x.lo.hi + y.lo.hi;
    auto k2 = b < x.lo.hi;
    b += k1;
    k2 += b < k1;

    auto c = x.hi.lo + y.hi.lo;
    auto k3 = c < x.hi.lo;
    c += k2;
    k3 += c < k2;

    auto d = x.hi.hi + y.hi.hi + k3;
    return {{d, c}, {b, a}};
}
}  // namespace intx

using uint64 = unsigned long;

struct uint192
{
    uint64 l;
    uint64 m;
    uint64 h;
};

uint192 add(uint64 xl, uint64 xm, uint64 xh, uint64 yl, uint64 ym, uint64 yh)
{
    auto l = xl + yl;
    auto k1 = l < xl;
    auto m = xm + ym + k1;
    auto k2 = (m < xm) | (m < ym);
    auto h = xh + yh + k2;
    return {l, m, h};
}

uint192 add2(uint64 xl, uint64 xm, uint64 xh, uint64 yl, uint64 ym, uint64 yh)
{
    auto l = xl + yl;
    auto k1 = l < xl;
    auto m = xm + ym + k1;
    auto k2 = (m < xm) | (m < k1);
    auto h = xh + yh + k2;
    return {l, m, h};
}

uint192 add3(uint64 xl, uint64 xm, uint64 xh, uint64 yl, uint64 ym, uint64 yh)
{
    auto l = xl + yl;
    auto k1 = l < xl;
    auto m = xm + ym;
    auto k2 = m < xm;
    m += k1;
    auto k3 = m < k1;
    auto k = k2 + k3;
    auto h = xh + yh + k;
    return {l, m, h};
}
