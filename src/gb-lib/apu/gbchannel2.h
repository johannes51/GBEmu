#ifndef GBCHANNEL2_H
#define GBCHANNEL2_H

#include "ichannel.h"

#include "mem/registers/iregisteradapter.h"

class GbChannel2 : public IChannel {
public:
  GbChannel2(IRegisterAdapterSP nr21, IRegisterAdapterSP nr22, IRegisterAdapterSP nr23, IRegisterAdapterSP nr24);
};

#endif // GBCHANNEL2_H
