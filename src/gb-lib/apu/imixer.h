#ifndef IMIXER_H
#define IMIXER_H

#include <memory>

class IMixer {
public:
  virtual ~IMixer() = default;

  virtual std::pair<double, double> mix(double channel1, double channel2, double channel3, double channel4, double vin)
      = 0;

protected:
  IMixer() = default;
};

using IMixerUP = std::unique_ptr<IMixer>;

#endif // IMIXER_H
