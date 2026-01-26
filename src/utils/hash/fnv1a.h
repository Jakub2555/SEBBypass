#pragma once

#include <stdint.h>

/*
*   FNV1A hashing, modified by me but I dont remember who originaly wrote this.
*/

constexpr uint64_t val_64_const = 0xcbf29ce484222325;
constexpr uint64_t prime_64_const = 0x100000001b3;

namespace fnv1a
{
    template<typename CharT>
    __forceinline const uint64_t hash(const CharT* key)
    {
        const CharT* data = key;
        uint64_t hash = val_64_const;

        while (*data)
        {
            hash = hash ^ static_cast<uint64_t>(*data++);
            hash *= prime_64_const;
        }

        return hash;
    }

    template<typename CharT>
    __forceinline constexpr uint64_t chash(const CharT* str, const uint64_t value = val_64_const) noexcept
    {
        return (str[0] == '\0') ? value : chash(str + 1, (value ^ static_cast<uint64_t>(*str)) * prime_64_const);
    }
}