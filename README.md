# ps.cpp
Algorithm and DataStructure library for problem-solving written in modern c++.

## Feature
  1. Balanced abstraction among flexibility, performance, code length, and readability.
  2. Resolve all headerfile dependancy and merge them into one file. (res/sumit.cpp)
  3. Header-only library

## Interface
  1. [s,e) half opened range
  2. 0-based-index
  3. Support negative index (same as python) (only suppoerted in Arr&lt;T&gt; as of now)

## Getting Started
  Requirements: ubuntu (20.04+), g++ (10.3.0+)
  1. git clone https://github.com/tuxedcat/ps.cpp
  2. cd ps.cpp
  3. cp src/tpl.cpp src/main.cpp
  4. source tool/build.sh src/main.cpp D #(Debug Build) generates res/mainD.out and res/submit.cpp
  5. source tool/build.sh src/main.cpp R #(Release Build) generates res/mainR.out and res/submit.cpp
  6. res/mainD.out #run debug excutable
  7. res/mainR.out #run release excutable

## Sample Code
``` cpp
#include "core/base.h"
signed main(){
	//Can get arbitrary tuple from stdin
	auto [n,m,k,x]=input<int,short,int,string>();
	//Can create and read dynamic array of arbitrary dimension
	//This creates n*m*k dynamic array, then read values from stdin
	auto a=input(ARR(n,m,k,0ll));
	//Can print an arbitrary tuple and dynamic array
	dbg(n,m,make_tuple(k,x),a);
}
```
## Sample Input
```
2 3 2 hi
1 2
3 4
5 6
0 0
1 1
2 2
```
## Sample Output
```
n,m,make_tuple(k,x),a;=
<  2,  3,
-<  2, hi,>,
-{
--(
---[  1,  2,],
---[  3,  4,],
---[  5,  6,],),
--(
---[  0,  0,],
---[  1,  1,],
---[  2,  2,],),},>
```

## Optional Settings: Testcase Download  
  1. Install <a href="https://addons.mozilla.org/en-US/firefox/addon/competitive-companion">CompetitiveCompanion</a> extension to your webbrowser  
  2. Install nodev14+ and expressjs
  3. Run 'node tool/tcsaver.js'
  4. Click the extension on webbrowser will download all examples on current page into ./test/*
  5. Run 'tool/tc.sh src/${fileBasenameNoExtension}D.out' will check all output automatically.

## Optional Settings: VSCode  
  TODO

## Limitation
  1. Don't use Subtyping-Polymorphism. (pslib assume this for simple code)
  2. #include must be located on top of source file. if you need to define(or whatever) something above the header, use core/config.h(or other headers) instead. (due to dependancy resolving logic)
  3. <a href="https://www.apache.org/licenses/LICENSE-2.0">Apache 2.0 License</a>
