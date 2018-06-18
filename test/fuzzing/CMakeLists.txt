# intx: extended precision integer library.
# Copyright 2017 Pawel Bylica.
# Licensed under the Apache License, Version 2.0. See the LICENSE file.

string(REPLACE "-fsanitize=fuzzer-no-link" "-fsanitize=fuzzer" CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})

add_executable(intx-safe-fuzzer safe_fuzzer.cpp)
target_link_libraries(intx-safe-fuzzer PRIVATE intx)
set_target_properties(intx-safe-fuzzer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ..)
