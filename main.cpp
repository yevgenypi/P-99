#include <iostream>

#include "list.h"

using namespace ct_list;

int main() {
    static_assert(IsSame<Cons<1, Cons<2, Cons<3, Nil>>>, Cons<1, Cons<2, Cons<3, Nil>>>>::value);

    PrintList<CreateList<1, 2, 3, 4, 5>::list>();
    static_assert(IsSame<CreateList<1, 2, 3>::list, Cons<1, Cons<2, Cons<3, Nil>>>>::value);

    static_assert(Sum<Nil>::value == 0);
    static_assert(Sum<CreateList<1, 2, 3, 4, 5>::list>::value == 1 + 2 + 3 + 4 + 5);

    static_assert(FoldL<Nil, MulFunc, 1>::value == 1);
    static_assert(FoldL<CreateList<1, 2, 3, 4, 5>::list, MulFunc, 1>::value == 1 * 2 * 3 * 4 * 5);

    static_assert(FoldR<Nil, MulFunc, 1>::value == 1);
    static_assert(FoldR<CreateList<1, 2, 3, 4, 5>::list, MulFunc, 1>::value == 1 * 2 * 3 * 4 * 5);

    static_assert(SumFoldR<Nil>::value == 0);
    static_assert(SumFoldR<CreateList<1, 2, 3, 4, 5>::list>::value == 1 + 2 + 3 + 4 + 5);

    static_assert(Last<CreateList<1, 2, 3, 4, 5>::list>::value == 5);

    static_assert(LastButOne<CreateList<1, 2, 3, 4, 5>::list>::value == 4);

    static_assert(KthElement<CreateList<1, 2, 3, 4, 5>::list, 1>::value == 1);
    static_assert(KthElement<CreateList<1, 2, 3, 4, 5>::list, 3>::value == 3);

    static_assert(Length<Nil>::value == 0);
    static_assert(Length<CreateList<1, 2, 3, 4, 5>::list>::value == 5);

    PrintList<Reverse<CreateList<1, 2, 3, 4, 5>::list>::list>();
    static_assert(IsSame<Reverse<Nil>::list, Nil>::value);
    static_assert(IsSame<Reverse<CreateList<1, 2, 3, 4, 5>::list>::list, CreateList<5, 4, 3, 2, 1>::list>::value);

    static_assert(IsPalindrome<CreateList<1, 2, 3>::list>::value == false);
    static_assert(IsPalindrome<CreateList<1, 2, 3, 2, 1>::list>::value == true);

    PrintList<Compress<CreateList<1, 1, 2, 2, 3, 4, 4, 4, 5, 5>::list>::list>();
    static_assert(IsSame<Compress<Nil>::list, Nil>::value);
    static_assert(IsSame<Compress<CreateList<1, 1, 1, 2, 2, 3, 4, 4, 4, 5, 5>::list>::list, CreateList<1, 2, 3, 4, 5>::list>::value);

    static_assert(IsSame<Duplicate<Nil>::list, Nil>::value);
    static_assert(IsSame<Duplicate<CreateList<1, 2, 3>::list>::list, CreateList<1, 1, 2, 2, 3, 3>::list>::value);
    PrintList<Duplicate<CreateList<1, 2, 3, 4, 5>::list>::list>();

    static_assert(IsSame<DuplicateN<Nil, 5>::list, Nil>::value);
    static_assert(IsSame<DuplicateN<CreateList<1, 2, 3>::list, 3>::list, CreateList<1, 1, 1, 2, 2, 2, 3, 3, 3>::list>::value);
    PrintList<DuplicateN<CreateList<1, 2, 3, 4, 5>::list, 3>::list>();

    static_assert(IsSame<DropEveryN<Nil, 3>::list, Nil>::value);
    static_assert(IsSame<DropEveryN<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 3>::list, CreateList<1, 2, 4, 5, 7, 8, 10>::list>::value);
    PrintList<DropEveryN<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 3>::list>();

    static_assert(IsSame<ExtractSlice<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 3, 7>::list, CreateList<3, 4, 5, 6, 7>::list>::value);
    PrintList<ExtractSlice<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 3, 7>::list>();

    static_assert(IsSame<SplitList<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 4>::first, CreateList<1, 2, 3, 4>::list>::value);
    static_assert(IsSame<SplitList<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 4>::second, CreateList<5, 6, 7, 8, 9, 10>::list>::value);
    PrintList<SplitList<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 4>::first>();
    PrintList<SplitList<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 4>::second>();


    static_assert(IsSame<Rotate<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 3>::list, CreateList<4, 5, 6, 7, 8, 9, 10, 1, 2, 3>::list>::value);
    static_assert(IsSame<Rotate<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, -2>::list, CreateList<9, 10, 1, 2, 3, 4, 5, 6, 7, 8>::list>::value);
    PrintList<Rotate<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, 3>::list>();
    PrintList<Rotate<CreateList<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::list, -2>::list>();

    static_assert(IsSame<RemoveKth<CreateList<1, 2, 3, 4, 5>::list, 1>::list, CreateList<2, 3, 4, 5>::list>::value);
    static_assert(IsSame<RemoveKth<CreateList<1, 2, 3, 4, 5>::list, 5>::list, CreateList<1, 2, 3, 4>::list>::value);
    PrintList<RemoveKth<CreateList<1, 2, 3, 4, 5>::list, 1>::list>();

    static_assert(IsSame<InsertAt<CreateList<1, 2, 3, 4, 5>::list, 5, 4>::list, CreateList<1, 2, 3, 5, 4, 5>::list>::value);
    PrintList<InsertAt<CreateList<1, 2, 3, 4, 5>::list, 5, 4>::list>();

    static_assert(IsSame<Range<4, 9>::list, CreateList<4, 5, 6, 7, 8, 9>::list>::value);
    static_assert(IsSame<Range<5, 5>::list, CreateList<5>::list>::value);
    PrintList<Range<4, 9>::list>();

    static_assert(Least<CreateList<1, 2, 3, 4, 5>::list>::value == 1);
    static_assert(Least<CreateList<5, 4, 3, 2, 1>::list>::value == 1);

    static_assert(IsSame<Extract<CreateList<5, 4, 3, 2, 1>::list, 1>::list, CreateList<5, 4, 3, 2>::list>::value);
    static_assert(IsSame<Extract<CreateList<5, 4, 3, 2, 1>::list, 5>::list, CreateList<4, 3, 2, 1>::list>::value);
    PrintList<Extract<CreateList<5, 4, 3, 2, 1>::list, 3>::list>();

    static_assert(IsSame<Sort<CreateList<5, 4, 3, 2, 1>::list>::list, CreateList<1, 2, 3, 4, 5>::list>::value);
    static_assert(IsSame<Sort<CreateList<5, 5, 3, 3, 1>::list>::list, CreateList<1, 3, 3, 5, 5>::list>::value);
    PrintList<Sort<CreateList<5, 5, 5, 3, 2, 1>::list>::list>();

    return 0;
}



