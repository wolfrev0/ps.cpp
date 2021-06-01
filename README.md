# Interface
  1. [s, e) half opened range
  2. 0-based index
  3. Support negative index (same as python)

# Getting Started
git clone https://github.com/0xc0def/algolib  
cd algolib  
-------------------------------------
아래 내용으로 ./incl/core/config.h 을 생성
#define INT64 1  // MLE?
#define INTERACTIVE 0
#define COUT_FP_PREC 12
// #define TESTCASE
-------------------------------------
cp src/tpl.cpp src/main.cpp //main.cpp에 템플릿코드 복사  
source build.sh src/main.cpp //실행파일 a.out과 병합된코드 submit.cpp가 생성된다. (디버그빌드)  
source build.sh src/main.cpp R //실행파일 a.out과 병합된코드 submitcpp가 생성된다. (릴리즈 빌드) 
