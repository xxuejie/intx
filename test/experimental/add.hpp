// intx: extended precision integer library.
// Copyright 2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#pragma once

#include <intx/intx.hpp>

namespace intx
{
inline uint64_t add(uint64_t x, uint64_t y) noexcept
{
    asm("add %1, %0" : "+r"(x) : "r"(y) :);
    return x;
}

inline uint64_t adc(uint64_t x, uint64_t y) noexcept
{
    asm("adc %1, %0" : "+r"(x) : "r"(y));
    return x;
}

inline uint256 add_asm(const uint256& x, const uint256& y) noexcept
{
    auto a = add(x.lo.lo, y.lo.lo);
    auto b = adc(x.lo.hi, y.lo.hi);
    auto c = adc(x.hi.lo, y.hi.lo);
    auto d = adc(x.hi.hi, y.hi.hi);
    return {{d, c}, {b, a}};
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
}  // namespace intx
