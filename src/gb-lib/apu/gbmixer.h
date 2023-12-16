#ifndef GBMIXER_H
#define GBMIXER_H

#include "imixer.h"

#include <array>

#include "ichannel.h"
#include "mem/registers/iregisteradapter.h"

class GbMixer : public IMixer {
public:
  GbMixer(IRegisterAdapterSP nr12, IRegisterAdapterSP nr22, IRegisterAdapterSP nr32, IRegisterAdapterSP nr42,
      IRegisterAdapterSP nr50, IRegisterAdapterSP nr51, IRegisterAdapterSP nr52, std::array<IChannelSP, 4> channels);

private:
  IRegisterAdapterSP nr12_;
  IRegisterAdapterSP nr22_;
  IRegisterAdapterSP nr32_;
  IRegisterAdapterSP nr42_;
  IRegisterAdapterSP nr50_;
  IRegisterAdapterSP nr51_;
  IRegisterAdapterSP nr52_;
  std::array<IChannelSP, 4> channels_;
};

#endif // GBMIXER_H
