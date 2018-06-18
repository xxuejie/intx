// intx: extended precision integer library.
// Copyright 2018 Pawel Bylica.
// Licensed under the Apache License, Version 2.0. See the LICENSE file.

#include <intx/safe.hpp>

#include <iostream>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* input, size_t size)
{
    static constexpr size_t num_args = 4;
    static constexpr size_t num_ops = num_args - 1;
    static constexpr size_t required_size = num_args * sizeof(int) + num_ops;

    if (size != required_size)
        return 0;

    const int* args = reinterpret_cast<const int*>(input);
    const uint8_t* ops = input + (num_args * sizeof(int));

    __int128 native_result = args[0];
    intx::safe<int> safe_result = args[0];

    for (size_t i = 0; i < num_ops; ++i)
    {
        const int arg = args[i + 1];
        switch (ops[i])
        {
        case '+':
            native_result = native_result + arg;
            safe_result = safe_result + arg;
            break;
            //        case '-':
            //            native_result = native_result - arg;
            //            safe_result = safe_result - arg;
            //            break;
            //        case '*':
            //            native_result = native_result * arg;
            //            safe_result = safe_result * arg;
            //            break;
            //        case '/':
            //            if (arg != 0)
            //            {
            //                native_result = native_result / arg;
            //                safe_result = safe_result / arg;
            //            }
            //            break;
            //        case '%':
            //            if (arg != 0)
            //            {
            //                native_result = native_result % arg;
            //                safe_result = safe_result % arg;
            //            }
            //            break;
        default:
            break;
        }
    }

    switch (safe_result.get_status())
    {
    case intx::status::normal:
        if (safe_result.value() != native_result)
        {
            std::cerr << "1~~~~~~~~~~~~~~\n";
            __builtin_trap();
        }
        break;
    case intx::status::plus_infinity:
        if (native_result <= safe_result.max_value)
        {
            std::cerr << "2~~~~~~~~~~~~~~\n";
            __builtin_trap();
        }
        break;
    case intx::status::minus_infinity:
        if (native_result >= safe_result.min_value)
        {
            std::cerr << "3~~~~~~~~~~~~~~\n";
            __builtin_trap();
        }
        break;
    case intx::status::invalid:
        break;
    }

    return 0;
}
