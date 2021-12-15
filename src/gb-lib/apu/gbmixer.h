#ifndef GBMIXER_H
#define GBMIXER_H

#include "imixer.h"

#include <array>

#include "ichannel.h"
#include "mem/registers/iregisteradapter.h"

class GbMixer : public IMixer {
public:
  GbMixer(std::array<IChannel*, 4>&& channels, IRegisterAdapterSP&& registers);

private:
  std::array<IChannel*, 4> channels_;
  IRegisterAdapterSP registers_;
};

#endif // GBMIXER_H
