#include "gbchannel1.h"

GbChannel1::GbChannel1(IRegisterAdapterSP nr10, IRegisterAdapterSP nr11, IRegisterAdapterSP nr12,
    IRegisterAdapterSP nr13, IRegisterAdapterSP nr14, IRegisterAdapterSP nr52)
{
  nr10.reset();
  nr11.reset();
  nr12.reset();
  nr13.reset();
  nr14.reset();
  nr52.reset();
}