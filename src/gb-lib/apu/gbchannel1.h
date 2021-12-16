#ifndef GBCHANNEL1_H
#define GBCHANNEL1_H

#include "ichannel.h"

#include "mem/registers/iregisteradapter.h"

class GbChannel1 : public IChannel {
public:
  GbChannel1(IRegisterAdapterSP nr10, IRegisterAdapterSP nr11, IRegisterAdapterSP nr12, IRegisterAdapterSP nr13,
      IRegisterAdapterSP nr14, IRegisterAdapterSP nr52);
};

#endif // GBCHANNEL1_H
