#pragma once
#include "Tree.h"

struct SimpleTree: public Tree<int>{
  SimpleTree(int n=0):Tree(n){}

  void add_edge(int s, int e) {
    Tree<int>::add_edge(s, e, 1);
  }
};