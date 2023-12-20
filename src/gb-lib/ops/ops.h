#ifndef OPS_H
#define OPS_H

namespace ops {

enum class FlagResult {
  Set,
  Reset,
  NoChange,
};

struct OpResult {
  OpResult(FlagResult z, FlagResult n, FlagResult h, FlagResult c)
      : z(z)
      , n(n)
      , h(h)
      , c(c)
  {
  }
  FlagResult z;
  FlagResult n;
  FlagResult h;
  FlagResult c;
};

} // namespace ops

#endif // OPS_H
