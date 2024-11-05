#ifndef MOCKMIXER_H
#define MOCKMIXER_H

#include "apu/imixer.h"

class MockMixer : public IMixer {
public:
  MockMixer() = default;

  std::pair<double, double> mix(double channel1, double channel2, double channel3, double channel4, double vin) override
  {
    (void)channel1;
    (void)channel2;
    (void)channel3;
    (void)channel4;
    (void)vin;
    return { 0., 1. };
  }

  static IMixerUP make() { return std::make_unique<MockMixer>(); }
};

#endif // MOCKMIXER_H
