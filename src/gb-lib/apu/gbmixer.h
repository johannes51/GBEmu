#ifndef GBMIXER_H
#define GBMIXER_H

#include "imixer.h"

#include <array>

#include "ichannel.h"
#include "mem/registers/iregisteradapter.h"

class GbMixer : public IMixer {
public:
  GbMixer(IRegisterAdapterSP nr12, IRegisterAdapterSP nr22, IRegisterAdapterSP nr32, IRegisterAdapterSP nr42,
      IRegisterAdapterSP nr50, IRegisterAdapterSP nr51, IRegisterAdapterSP nr52);
};

#endif // GBMIXER_H
