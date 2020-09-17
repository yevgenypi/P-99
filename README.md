# P-99
Compiled time List with C++ templates + some useful functions inspired by 
[Ninety-Nine Prolog Problems](https://www.ic.unicamp.br/~meidanis/courses/mc336/2009s2/prolog/problemas/)

## List definition
```
struct Nil {
};

template<int Value, typename Tail>
struct Cons {
    static constexpr int value = Value;
    typedef Tail tail;
};
```