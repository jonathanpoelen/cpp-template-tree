Print a tree for templates

# Sample

test.cpp:

```cpp
template<class> struct S1 {};
template<class, class> struct S2 {};

int main() {
  S2<int, S1<const double> >()=1;
}
```

Possible output with a normal compilation (`g++ test.cpp`):

```cpp
test.cpp: In function ‘int main()’:
test.cpp:5:31: error: no match for ‘operator=’ (operand types are ‘S2<int, S1<const double> >’ and ‘int’)
   S2<int, S1<const double> >()=1;
                               ^
test.cpp:2:31: note: candidate: S2<int, S1<const double> >& S2<int, S1<const double> >::operator=(const S2<int, S1<const double> >&)
 template<class, class> struct S2 {};
                               ^
test.cpp:2:31: note:   no known conversion for argument 1 from ‘int’ to ‘const S2<int, S1<const double> >&’
```

Possible output with c++-template-tree (`g++ test.cpp |& c++-template-tree`)

```cpp
test.cpp: In function ‘int main()’:
test.cpp:5:31: error: no match for ‘operator=’ (operand types are 
‘S2<
  int,
  S1<const double> 
>’ and ‘int’)
   
S2<
  int,
  S1<const double> 
>()=1;
                               ^
test.cpp:2:31: note: candidate: 
S2<
  int,
  S1<const double> 
>& S2
<
  int,
  S1<const double> 
>::operator=(const S2
<
  int,
  S1<const double> 
>&)
 
template<
  class,
  class
> struct S2 {};
                               ^
test.cpp:2:31: note:   no known conversion for argument 1 from ‘int’ to ‘const 
S2<
  int,
  S1<const double> 
>&’
```
