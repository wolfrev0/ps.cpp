# Interface
  1. [s, e) half opened range
  2. 0-based index
  3. Support negative index (same as python)

# Getting Started
1. git clone https://github.com/0xc0def/algolib  
2. cd algolib  
3. Make a file at ./incl/core/config.h and write the text below.  
#define INT64 1  // MLE?  
#define INTERACTIVE 0  
#define COUT_FP_PREC 12  
// #define TESTCASE  
4. cp src/tpl.cpp src/main.cpp //main.cpp에 템플릿코드 복사  
5. source build.sh src/main.cpp //실행파일 a.out과 병합된코드 submit.cpp가 생성된다. (디버그빌드)  
6. source build.sh src/main.cpp R //실행파일 a.out과 병합된코드 submitcpp가 생성된다. (릴리즈 빌드) 
