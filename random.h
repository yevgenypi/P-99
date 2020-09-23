#pragma once

#include <cstdint>
#include <numeric>

// see:
// Random number generator for C++ template metaprograms [Szűgyi Cséri Porkoláb 2013]

constexpr uint32_t generate_seed() {
    constexpr char inits[] = __TIME__;

    return  (inits[0] - '0') * 100000 +
            (inits[1] - '0') * 10000 +
            (inits[3] - '0') * 1000 +
            (inits[4] - '0') * 100 +
            (inits[6] - '0') * 10 +
            (inits[7] - '0');
}

static constexpr uint32_t defaultseed = generate_seed();

template<typename UIntType,
        UIntType seed = defaultseed,
        UIntType a = 16807,
        UIntType c = 0,
        UIntType m = 2147483647>
struct linear_congruential_engine
{
    static const UIntType value = seed;
    static const UIntType maxvalue = m-1;
};

template <typename Engine>
struct init;

template <typename Engine>
struct eval;

template<typename UIntType,
        UIntType seed,
        UIntType a,
        UIntType c,
        UIntType m>
struct init<linear_congruential_engine<UIntType, seed, a, c, m>>
{
    typedef typename eval<linear_congruential_engine<UIntType, seed, a, c, m>>::type type;
    static const UIntType value = type::value;
};

template<typename UIntType, UIntType seed,
        UIntType a, UIntType c, UIntType m>
struct eval<linear_congruential_engine<UIntType, seed, a, c, m>>
{
    static const UIntType value = (a * seed + c) % m;
    typedef linear_congruential_engine<
            UIntType,
            (a * seed + c) % m,
            a,
            c,
            m
    > type;
};

template<typename Engine>
struct Random
{
    typedef typename init<Engine>::type type;
    static const decltype(type::value) value = type::value;
};

template<typename R>
struct Next
{
    typedef typename eval<R>::type type;
    static const decltype(type::value) value = type::value;
};
