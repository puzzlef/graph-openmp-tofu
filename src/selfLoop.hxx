#pragma once
#include "duplicate.hxx"




// HAS SELF-LOOP
// -------------

template <class G, class K>
inline bool hasSelfLoop(const G& x, K u) {
  return x.hasEdge(u, u);
}




// SELF-LOOPS
// ----------

template <class G, class F>
inline void selfLoopForEach(const G& x, F fn) {
  x.forEachVertexKey([&](auto u) { if (hasSelfLoop(x, u)) fn(u); });
}
template <class G>
inline auto selfLoops(const G& x) {
  using K = typename G::key_type; vector<K> a;
  selfLoopForEach(x, [&](auto u) { a.push_back(u); });
  return a;
}
template <class G>
inline auto selfLoopCount(const G& x) {
  using K = typename G::key_type; K a = 0;
  selfLoopForEach(x, [&](auto u) { ++a; });
  return a;
}




// SELF-LOOP
// ---------

template <class G, class E, class FT>
void selfLoopU(G& a, const E& w, FT ft) {
  a.forEachVertexKey([&](auto u) { if (ft(u)) a.addEdge(u, u, w); });
  a.update();
}
template <class G, class E, class FT>
auto selfLoop(const G& x, const E& w, FT ft) {
  auto a = duplicate(x); selfLoopU(a, w, ft);
  return a;
}
