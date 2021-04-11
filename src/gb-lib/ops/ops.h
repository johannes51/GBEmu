#ifndef OPS_H
#define OPS_H

namespace ops {

struct OpResult {
  OpResult(int z, int n, int h, int c)
      : z(z)
      , n(n)
      , h(h)
      , c(c)
  {
  }
  int z;
  int n;
  int h;
  int c;
};

} // namespace ops

#endif // OPS_H
