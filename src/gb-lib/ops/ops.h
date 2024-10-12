#ifndef OPS_H
#define OPS_H

namespace ops {

enum class FlagResult {
  Set,
  Reset,
  NoChange,
};

class OpResult {
public:
  OpResult()
      : OpResult(FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange)
  {
  }
  OpResult(FlagResult z, FlagResult n, FlagResult h, FlagResult c)
      : z(z)
      , n(n)
      , h(h)
      , c(c)
  {
  }

  bool operator==(const OpResult& other) const
  {
    return (z == other.z) && (n == other.n) && (h == other.h) && (c == other.c);
  }

  FlagResult z;
  FlagResult n;
  FlagResult h;
  FlagResult c;
};

} // namespace ops

#endif // OPS_H
