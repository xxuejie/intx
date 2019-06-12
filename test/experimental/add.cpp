// intx: extended precision integer library.
// Copyright 2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#include <experimental/add.hpp>

namespace intx
{
uint256 _add_asm(const uint256& x, const uint256& y) noexcept
{
    return add_asm(x, y);
}

uint256 _add_c1(const uint256& x, const uint256& y) noexcept
{
    return add_c1(x, y);
}

uint256 _add_c2(const uint256& x, const uint256& y) noexcept
{
    return add_c2(x, y);
}

uint256 _add(const uint256& x, const uint256& y) noexcept
{
    return x + y;
}
}