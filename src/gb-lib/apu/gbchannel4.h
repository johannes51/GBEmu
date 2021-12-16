#ifndef GBCHANNEL4_H
#define GBCHANNEL4_H

#include "ichannel.h"

#include "mem/registers/iregisteradapter.h"

class GbChannel4 : public IChannel {
public:
  GbChannel4(IRegisterAdapterSP nr41, IRegisterAdapterSP nr42, IRegisterAdapterSP nr43, IRegisterAdapterSP nr44,
      IRegisterAdapterSP nr52);
};

#endif // GBCHANNEL4_H
