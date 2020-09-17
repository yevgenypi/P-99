#pragma once

#include <iostream>
#include <type_traits>

namespace ct_list {

// List
    struct Nil {
    };

    template<int Value, typename Tail>
    struct Cons {
        static constexpr int value = Value;
        typedef Tail tail;
    };


// Helpers
    template<typename L>
    void PrintList() {
        std::cout << L::value << " ";
        PrintList<typename L::tail>();
    }

    template<>
    void PrintList<Nil>() {
        std::cout << std::endl;
    }


    template<int Head, int... Tail>
    struct CreateList {
        typedef Cons<Head, typename CreateList<Tail...>::list> list;
    };

    template<int Head>
    struct CreateList<Head> {
        typedef Cons<Head, Nil> list;
    };


// Functions
    template<typename Left, typename Right>
    struct IsSame {
        static constexpr bool value =
                (Left::value == Right::value) && IsSame<typename Left::tail, typename Right::tail>::value;
    };

    template<typename Left>
    struct IsSame<Left, Nil> : std::false_type {
    };

    template<typename Right>
    struct IsSame<Nil, Right> : std::false_type {
    };

    template<>
    struct IsSame<Nil, Nil> : std::true_type {
    };


    template<typename List>
    struct Sum {
        static constexpr int value = List::value + Sum<typename List::tail>::value;
    };

    template<>
    struct Sum<Nil> {
        static constexpr int value = 0;
    };


    template<typename List, template<int A, int B> typename Func, int init = 0>
    struct FoldR {
        static constexpr int value = Func<List::value, FoldR<typename List::tail, Func, init>::value>::value;
    };

    template<template<int A, int B> typename Func, int init>
    struct FoldR<Nil, Func, init> {
        static constexpr int value = init;
    };


    template<typename List, template<int A, int B> typename Func, int init>
    struct FoldL {
        static constexpr int value = FoldL<typename List::tail, Func, Func<init, List::value>::value>::value;
    };

    template<template<int A, int B> typename Func, int init>
    struct FoldL<Nil, Func, init> {
        static constexpr int value = init;
    };


    template<int A, int B>
    struct MulFunc {
        static constexpr int value = A * B;
    };

    template<int A, int B>
    struct SumFunc {
        static constexpr int value = A + B;
    };

    template<int A, int B>
    struct Second {
        static constexpr int value = B;
    };


    template<typename List>
    struct SumFoldR {
        static constexpr int value = FoldR<List, SumFunc, 0>::value;
    };


    template<typename List>
    struct Last {
        static constexpr int value = FoldL<List, Second, List::value>::value;
    };

    template<>
    struct Last<Nil> {
    };


    template<typename List>
    struct LastButOne {
        static constexpr int value = LastButOne<typename List::tail>::value;
    };

    template<int N, int M>
    struct LastButOne<Cons<N, Cons<M, Nil>>> {
        static constexpr int value = N;
    };

    template<int N>
    struct LastButOne<Cons<N, Nil>> {
    };
    template<>
    struct LastButOne<Nil> {
    };


    template<typename List, int K, typename T = int>
    struct KthElement;

    template<typename List, int K>
    struct KthElement<List, K, typename std::enable_if<(K > 1), int>::type> {
        static constexpr int value = KthElement<typename List::tail, K - 1, int>::value;
    };

    template<typename List>
    struct KthElement<List, 1> {
        static constexpr int value = List::value;
    };

    template<typename List>
    struct KthElement<List, 0> {
    };

    template<int K>
    struct KthElement<Nil, K> {
    };


    template<typename List>
    struct Length {
        static constexpr int value = 1 + Length<typename List::tail>::value;
    };

    template<>
    struct Length<Nil> {
        static constexpr int value = 0;
    };


    template<typename List, typename Accu = Nil>
    struct Reverse {
        typedef typename Reverse<typename List::tail, Cons<List::value, Accu>>::list list;
    };

    template<typename Accu>
    struct Reverse<Nil, Accu> {
        typedef Accu list;
    };


    template<typename List>
    struct IsPalindrome : std::is_same<List, typename Reverse<List>::list> {
    };


    template<typename List, int Prev = List::value - 1, typename T = void>
    struct CompressHelper;

    template<typename List, int Prev>
    struct CompressHelper<List, Prev, typename std::enable_if<(List::value == Prev)>::type> {
        typedef typename CompressHelper<typename List::tail, Prev>::list list;
    };

    template<typename List, int Prev>
    struct CompressHelper<List, Prev, typename std::enable_if<(List::value != Prev)>::type> {
        typedef Cons<List::value, typename CompressHelper<typename List::tail, List::value>::list> list;
    };

    template<int Prev>
    struct CompressHelper<Nil, Prev> {
        typedef Nil list;
    };

    template<typename List>
    struct Compress {
        typedef typename CompressHelper<List>::list list;
    };

    template<>
    struct Compress<Nil> {
        typedef Nil list;
    };


    template<typename List>
    struct Duplicate {
        typedef Cons<List::value, Cons<List::value, typename Duplicate<typename List::tail>::list>> list;
    };

    template<>
    struct Duplicate<Nil> {
        typedef Nil list;
    };


    template<typename List, unsigned N, unsigned C = N>
    struct DuplicateN {
        typedef Cons<List::value, typename DuplicateN<List, N, C - 1>::list> list;
    };

    template<typename List, unsigned N>
    struct DuplicateN<List, N, 0> {
        typedef typename DuplicateN<typename List::tail, N, N>::list list;
    };

    template<unsigned N, unsigned C>
    struct DuplicateN<Nil, N, C> {
        typedef Nil list;
    };


    template<typename List, unsigned N, unsigned C = N>
    struct DropEveryN {
        typedef Cons<List::value, typename DropEveryN<typename List::tail, N, C - 1>::list> list;
    };

    template<typename List, unsigned N>
    struct DropEveryN<List, N, 1> {
        typedef typename DropEveryN<typename List::tail, N, N>::list list;
    };

    template<unsigned N, unsigned C>
    struct DropEveryN<Nil, N, C> {
        typedef Nil list;
    };

    template<typename List, unsigned C>
    struct DropEveryN<List, 0, C> {
        typedef Nil list;
    };

    template<typename List, unsigned C>
    struct DropEveryN<List, 1, C> {
        typedef Nil list;
    };


    template<typename List, unsigned I, unsigned K, typename T = void>
    struct ExtractSlice;

    template<typename List, unsigned I, unsigned K>
    struct ExtractSlice<List, I, K, typename std::enable_if<(I > K) or (K == 0), void>::type> {
        typedef Nil list;
    };

    template<typename List, unsigned I, unsigned K>
    struct ExtractSlice<List, I, K, typename std::enable_if<(I < K) and (I > 1), void>::type> {
        typedef typename ExtractSlice<typename List::tail, I - 1, K - 1>::list list;
    };

    template<typename List, unsigned K>
    struct ExtractSlice<List, 1, K, typename std::enable_if<(K > 0), void>::type> {
        typedef Cons<List::value, typename ExtractSlice<typename List::tail, 1, K - 1>::list> list;
    };

    template<unsigned I, unsigned K>
    struct ExtractSlice<Nil, I, K> {
        typedef Nil list;
    };

    template<typename List>
    struct ExtractSlice<List, 0, 0> {
        typedef Nil list;
    };


    template<typename List, unsigned N>
    struct SplitList {
        typedef Cons<List::value, typename SplitList<typename List::tail, N - 1>::first> first;
        typedef typename SplitList<typename List::tail, N - 1>::second second;
    };

    template<typename List>
    struct SplitList<List, 0> {
        typedef Nil first;
        typedef List second;
    };

    template<unsigned N>
    struct SplitList<Nil, N> {
        typedef Nil first;
        typedef Nil second;
    };


    template<typename Left, typename Right>
    struct Append {
        typedef Cons<Left::value, typename Append<typename Left::tail, Right>::list> list;
    };

    template<typename Right>
    struct Append<Nil, Right> {
        typedef Right list;
    };


    template<typename List, int N, typename T = void>
    struct Rotate;

    template<typename List, int N>
    struct Rotate<List, N, typename std::enable_if<(N > 0), void>::type> {
        typedef typename Append<typename SplitList<List, N>::second, typename SplitList<List, N>::first>::list list;
    };

    template<typename List, int N>
    struct Rotate<List, N, typename std::enable_if<(N < 0), void>::type> {
        typedef typename Append<typename SplitList<List, Length<List>::value + N>::second, typename SplitList<List,
                Length<List>::value + N>::first>::list list;
    };

    template<typename List>
    struct Rotate<List, 0> {
        typedef List list;
    };


    template<typename List, unsigned K>
    struct RemoveKth {
        typedef Cons<List::value, typename RemoveKth<typename List::tail, K - 1>::list> list;
    };

    template<typename List>
    struct RemoveKth<List, 1> {
        typedef typename List::tail list;
    };

    template<typename List>
    struct RemoveKth<List, 0> {
    };

    template<unsigned K>
    struct RemoveKth<Nil, K> {
        typedef Nil list;
    };


    template<typename List, unsigned Value, int K>
    struct InsertAt {
        typedef Cons<List::value, typename InsertAt<typename List::tail, Value, K - 1>::list> list;
    };

    template<typename List, unsigned Value>
    struct InsertAt<List, Value, 1> {
        typedef Cons<Value, List> list;
    };

    template<typename List, unsigned Value>
    struct InsertAt<List, Value, 0> {
        typedef List list;
    };


    template<unsigned A, unsigned B, typename T = void>
    struct Range;

    template<unsigned A, unsigned B>
    struct Range<A, B, typename std::enable_if<(A < B), void>::type> {
        typedef Cons<A, typename Range<A + 1, B>::list> list;
    };

    template<unsigned A>
    struct Range<A, A> {
        typedef Cons<A, Nil> list;
    };

}