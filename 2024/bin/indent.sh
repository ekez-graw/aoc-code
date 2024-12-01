#!/bin/bash

find . -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \) \
    $(git ls-files --exclude-standard | sed "s/^/-not -path '.\/&\/'/") | xargs clang-format -i
