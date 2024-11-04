#ifndef GBMIXER_H
#define GBMIXER_H

#include "imixer.h"

#include "mem/registers/iregisteradapter.h"

class GbMixer : public IMixer {
public:
  GbMixer(IRegisterAdapterSP nr50, IRegisterAdapterSP nr51);

  std::pair<double, double> mix(double channel1, double channel2, double channel3, double channel4, double vin);

private:
  IRegisterAdapterSP nr50_;
  IRegisterAdapterSP nr51_;
};

#endif // GBMIXER_H
