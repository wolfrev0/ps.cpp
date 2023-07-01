# ps.cpp
Algorithm( and DataStructure) library for problem-solving written in modern c++. It resolves all header file dependancies and merge them into one file(build/sumit.cpp). It is header-only library.

## Interface
  1. [s,e) half opened range
  2. 0-based-index
  3. Support negative index (same as python) (only suppoerted in Arr&lt;T&gt; as of now)

## Getting Started
  Requirements: ubuntu(20.04+, fine in wsl), g++(10.3.0+)
``` bash
  git clone https://github.com/tuxedcat/ps.cpp
  cd ps.cpp
  tool/build_cmake.sh src/sample/helloworld.cpp Debug
  cat build/submit.cpp
  build/src/sample/helloworld.cpp/Debug/ps.cpp.out
```

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
  3. Run `node tool/tcsaver.js`
  4. Click the extension on webbrowser will download all examples on current page into `./test/*`
  5. Run `tool/tc.sh [executable file path]` will check all output automatically.

## VSCode  
You can use preset VSCode tasks. For more information, `.vscode/tasks.json`

## Limitation
  1. Due to dependancy resolving logic, #include must be located on top of source file.
  2. Don't use Subtyping-Polymorphism. (pslib assume this for simple code)
