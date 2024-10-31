#ifndef FALLINGEDGEDETECTOR_H
#define FALLINGEDGEDETECTOR_H

template <class T, const T ZeroVal = T { 0 }> class FallingEdgeDetector {
public:
  explicit FallingEdgeDetector(const T initial = ZeroVal)
      : lastVal_(initial)
  {
  }

  bool isFallingEdge(const T currentVal)
  {
    const auto res = (currentVal == ZeroVal) && (lastVal_ != ZeroVal);
    lastVal_ = currentVal;
    return res;
  }

private:
  T lastVal_;
};

#endif // FALLINGEDGEDETECTOR_H
