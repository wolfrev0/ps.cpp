#include "Core.h"

using namespace std::chrono;

int main(int argc, char** argv) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(3);
  srand((u32)time(0));

  string path = "./";path+=argv[1];
  auto start = system_clock::now();
  system(path.c_str());
  auto end = system_clock::now();
  duration<f64> dur = end-start;
  cout<<"Runnging Time: "<<dur.count()<<'s'<<endl;

  return 0;
}