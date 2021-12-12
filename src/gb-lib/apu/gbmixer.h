#ifndef GBMIXER_H
#define GBMIXER_H

#include "imixer.h"

#include <array>

#include "ichannel.h"
#include "mem/registers/iregisteradapter.h"

class GbMixer : public IMixer {
public:
  GbMixer(std::array<IChannel*, 4>&& channels, IRegisterAdapterUP&& registers);

private:
  std::array<IChannel*, 4> channels_;
  IRegisterAdapterUP registers_;
};

#endif // GBMIXER_H
