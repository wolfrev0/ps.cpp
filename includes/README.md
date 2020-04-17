## Bag.h
  집합을 의미하며, 집합끼리의 Union이 O(1)로 효율적이다.
## Bipartite.h
  이분매칭
## Bucket.h
  원소의 최대크기가 n인 집합으로, Find가 O(1)로 효율적인 집합이다.
## Carr.h
  Circular Array
## Core.h
  ps코드를 간결하게 짜기 위해 자주 사용되는 상수들과 구문들이 있다.
## CumulQ.h
  역연산을 지원하는 f에 대해 누적값을 FIFO로 관리할 수 있다. rabin-karp 해싱 등에 사용한다.
## DPOpt.h
  CHT(Stack, Dynamic), KnuthOpt등의 DP 최적화 함수들이 있다.
## DirGraph.h
  Directed Graph이다. 위상정렬, SCC등을 할 수 있다.
## FFT.h
  Fast Fourier Transform
## FastIO.h
  include하면 cin의 속도가 매우 향상됩니다.
## Fenwick.h
  역연산이 존재하는 연산들에 대해 Segment Tree보다 더 빠르게 동작합니다. (시간복잡도는 동일)
## FlowGraph.h
  Maximum Flow(kruskal), MCMF 등을 할 수 있습니다. dinic은 지원예정
## Frac.h
  Fractional
## GccExts.h
  자주 쓰는 GCC Extension들이다.
## Graph.h
  가중치있는 방향그래프를 나타냅니다. dijkstra, floyd, spfa, MST 등을 구할 수 있습니다.
## HLD.h
  주어지는 트리를 Heavy-Light Decompose하여 저장합니다.
## Line.h
  직선(도형)을 나타냅니다.
## List.h
  LinkedList with O(1) merge
## Mat.h
  Matrix
## MatGF2.h
  Matrix in galois field 2
## MergeSortTree.h
## Mod.h
  Modular Number입니다. a mod m을 나타냅니다.
## MonoQ.h
  슬라이딩윈도 하며 최소(최대)값을 구할 수 있습니다.
## NumberTheory.h
  정수론 관련 함수들입니다.
## Polygon.h
  다각형을 나타냅니다. area, is intersect, Convex Hull등을 구할 수 있습니다.
## Range.h
  수직선상의 한 구간 [s,e)를 나타냅니다.
## Rect.h
  직사각형을 나타냅니다.
## RootedTree.h
  루트있는 트리를 나타냅니다.
## SegTree.h
  Segment Tree
## SegTree2D.h
  이차원 Segment Tree입니다.
## SegTreeCommutative.h
  교환법칙이 성립하는 값에 대해 좀 더 빠르게 동작하는 Segment Tree입니다.
## SegTreeLazy.h
  구간update가 가능한 Segment Tree입니다.
## SimpleGraph.h
  단순그래프(undirected & unweighted)를 나타냅니다.
## SimpleTree.h
  단순트리(unrooted & unweighted)를 나타냅니다.
## SplayTree.h
## String.h
  문자열 관련 함수(kmp, suffix array, lcp, int to string, split)들이 있습니다.
## Tree.h
  diameter등을 구할 수 있습니다.
## UnionFind.h
  서로소집합
## Vec2.h
  2차원벡터를 나타냅니다.
## XArr.h
  Extended Array. 인자로 넘겨주는 offset만큼의 음수인덱스까지 사용할 수 있습니다.
## XSet.h
  Extended Set. GCC확장기능을 사용하여 order_of_key, find_by_order등을 사용할 수 있습니다.
## Zip.h
  좌표압축
