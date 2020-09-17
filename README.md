# P-99
Compiled time List with C++ templates + some useful functions inspired by 
[Ninety-Nine Prolog Problems](https://www.ic.unicamp.br/~meidanis/courses/mc336/2009s2/prolog/problemas/)

#### List definition
```
struct Nil {
};

template<int Value, typename Tail>
struct Cons {
    static constexpr int value = Value;
    typedef Tail tail;
};
```

#### Example of list
##### []
```
Nil
```
##### [1,2,3] 
```
Cons<1, Cons<2, Cons <3, Nil>>>
```
or
```
CreateList<1,2,3>::list
```

#### Examples of usage
##### Reverse [1,2,3] -> [3,2,1]
```
Reverse<CreateList<1,2,3>::list>::list
```

##### Duplicate [1,2,3] -> [1,1,2,2,3,3]
```
Duplicate<CreateList<1,2,3>::list>::list
```
