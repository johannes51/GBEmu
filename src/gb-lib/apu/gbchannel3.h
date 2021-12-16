#ifndef GBCHANNEL3_H
#define GBCHANNEL3_H

#include "ichannel.h"

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"

class GbChannel3 : public IChannel {
public:
  GbChannel3(IRegisterAdapterSP nr30, IRegisterAdapterSP nr31, IRegisterAdapterSP nr32, IRegisterAdapterSP nr33,
      IRegisterAdapterSP nr34, IRegisterAdapterSP nr52, IMemoryViewSP waveRam);
};

#endif // GBCHANNEL3_H
