# pslib (Problem Solving Library)
Algo & D.S. library for problem-solving written in Modern C++.

## Feature
  1. Balanced abstraction among flexibility, performance, code length, and readability.
  2. Resolve all headerfile dependancy and merge to one file. (just submit res/sumit.cpp file. That's all!)
  3. Various convenient tools. (pretty print debugger, testcase checker, etc...)

## Interface
  1. [s,e) half opened range
  2. 0-based-index
  3. Support negative index (same as python) (only suppoerted in Arr&lt;T&gt; as of now)

## Getting Started
  Requirements: ubuntu20.04+, c++20, g++
  1. git clone https://github.com/tuxedcat/pslib
  2. cd pslib
  3. cp src/tpl.cpp src/main.cpp
  4. source tool/build.sh src/main.cpp D #(Debug Build) generates res/mainD.out and res/submit.cpp
  5. source tool/build.sh src/main.cpp R #(Release Build) generates res/mainR.out and res/submit.cpp
  6. res/mainD.out (run debug excutable)
  7. res/mainR.out (run release excutable)

## Sample Code
``` cpp
#include "core/base.h"
signed main(){
	int n=5;
	auto arr=ARR(2,3,2,n,'#');//(2*3*2*n shaped 4D array)
	for(int i=0;i<2;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<2;k++)
				for(int l=0;l<n;l++)
					arr[i][j][k][l]='a'+i+j+k+l;;
	dbg(arr,n,mkt(3,"hi",'@'),Arr<int>(n,7));//ez debug
	print(1,'2',"3",string("4"),n,"hello?",endl);//ez print
}
```
## Sample Output (Debug)
```
arr,n,mkt(3,"hi",'@'),Arr<int>(n,7);=
<
-{
--(
---[
----{  a,  b,  c,  d,  e,},
----{  b,  c,  d,  e,  f,},],
---[
----{  b,  c,  d,  e,  f,},
----{  c,  d,  e,  f,  g,},],
---[
----{  c,  d,  e,  f,  g,},
----{  d,  e,  f,  g,  h,},],),
--(
---[
----{  b,  c,  d,  e,  f,},
----{  c,  d,  e,  f,  g,},],
---[
----{  c,  d,  e,  f,  g,},
----{  d,  e,  f,  g,  h,},],
---[
----{  d,  e,  f,  g,  h,},
----{  e,  f,  g,  h,  i,},],),},  5,
-<  3, hi,  @,>,
-{  7,  7,  7,  7,  7,},>
1 2 3 4 5 hello? 
```
## Sample Output (Release)
```
1 2 3 4 5 hello? 
```

## Optional Settings: Testcase Download  
  1. Install <a href="https://addons.mozilla.org/en-US/firefox/addon/competitive-companion">CompetitiveCompanion</a> extension to your webbrowser  
  2. Install nodev14+ and expressjs
  3. Run 'node tool/tcsaver.js'
  4. Click the extension on webbrowser will download all examples on current page into ./test/tc
  5. Run 'test/tc.sh src/${fileBasenameNoExtension}D.out' will check all output automatically.

## Optional Settings: VSCode  
  TODO

## Limitation
  1. Don't use Subtyping-Polymorphism. (pslib doesn't use virtual method due to performance issue)
  2. #include must be located on top of source file. if you need to define(or whatever) something above the header, use core/config.h(or other headers) instead. (due to dependancy resolving logic)
  3. License is <a href="https://www.apache.org/licenses/LICENSE-2.0">Apache License Version 2.0</a>