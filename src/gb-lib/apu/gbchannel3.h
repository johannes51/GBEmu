#ifndef GBCHANNEL3_H
#define GBCHANNEL3_H

#include "ichannel.h"

#include "mem/registers/iregisteradapter.h"

class GbChannel3 : public IChannel {
public:
  GbChannel3(IRegisterAdapterSP nr30, IRegisterAdapterSP nr31, IRegisterAdapterSP nr32, IRegisterAdapterSP nr33,
      IRegisterAdapterSP nr34);
};

#endif // GBCHANNEL3_H
