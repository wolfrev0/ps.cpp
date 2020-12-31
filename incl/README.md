## Bag.h
  집합을 의미하며, 집합끼리의 Union이 O(1)로 효율적이다.
## Bipartite.h
  이분그래프
## Bucket.h
  원소의 최대크기가 n인 집합으로, Find가 O(1)로 효율적인 집합이다.
## Carr.h
  Circular Array
## Core.h
  ps코드를 간결하게 짜기 위해 자주 사용되는 상수들과 구문들이 있다.
## CumulQ.h
  역연산을 지원하는 f에 대해 누적값을 FIFO로 관리할 수 있다. rabin-karp 해싱 등에 사용한다.
## DirGraph.h
  Directed Graph이다. 위상정렬, SCC등을 할 수 있다.
## DPOpt.h
  CHT(Stack, Dynamic), KnuthOpt등의 DP 최적화 함수들이 있다.
## DST.h
  Dynamic Setment Tree
## DSTLazy.h
  Dynamic Segment Tree wit Lazy Propagation
## FastIO.h
  include만 해도 cin의 속도가 매우 빨라진다.
## Fenwick.h
  역연산이 존재하는 연산들에 대해 Segment Tree보다 더 빠르게 동작합니다.
## FFT.h
  Fast Fourier Transform
## Flow.h
  Maximum Flow, MCMF 등을 할 수 있다.
## Frac.h
  Fractional
## GccExts.h
  자주 쓰는 GCC Extension들이다.
## Graph.h
  가중치있는 유향그래프. dijkstra, floyd, spfa, MST 등이 가능하다.
## HashVal.h
  라빈카프 해싱을 도와준다.
## HeapSet.h
  집합의 최댓값만 필요할때 임의원소 추가/삭제가 효율적이다.
## HLD.h
  Heavy-Light Decompose
## Hungarian
  V^3 가중치 이분매칭. Bipartite.h에 통합될 예정
## LCA.h
  트리에서 Least Common Ancestor를 찾는다. Deprecated상태 (HLD의 lca함수를 권장함)
## LinAlgeGF2.h
  GF(2)에서의 선형대수학 관련 함수들
## LinAlge.h
  Z에서의 선형대수학 관련 함수들
## Line.h
  직선(도형)
## LinRec.h
  선형점화식을 푸는데 굉장히 유용한 Berlekamp Massey와 Kitamasa Method가 있다.
## List.h
  LinkedList with O(1) merge
## Mod.h
  자동으로 모듈러 처리해주는 정수
## Monoid
  주로 사용되는 연산들을 나타내며, SegmentTree류 자료구조를 정의할때 사용된다.
## MonoQ.h
  MonotonicQ. 슬라이딩윈도 하며 최소(최대)값을 구할 수 있습니다.
## NumberTheory.h
  정수론
## Polygon.h
  다각형 및 볼록다각형
## PrettyDebug.h
  디버깅 보조함수들
## PrettyIO.h
  IO 보조함수들
## PST.h
  Persistent Segment Tree
## PSTLazy.h
  Persistent Segment Tree with Lazy Propagation
## Range.h
  반열린구간
## Rect.h
  (Axis Aligned) 직사각형
## RootedTree.h
## Seg.h
  Segment Tree
## Seg2D.h
  2D Segment Tree
## SegBU.h
  Recursion-Free Segment Tree (Bottom Up Implementation)
## SegLazy.h
  Segment Tree with LazyPropagation
## SimpleGraph.h
  단순그래프(undirected & unweighted)
## SplayTree.h
## String.h
  문자열 관련 함수들. (kmp, suffix array, lcp, int to string, split, ...)
## Tree.h
## Trie.h
## UnionFind.h
## Vec2.h
  2D Vector
## XArr.h
  Extended Array. 설정한 offset만큼의 음수인덱스를 사용가능한 동적배열이다.
## Zip.h
  좌표압축
