#include "gbchannel2.h"

GbChannel2::GbChannel2(IRegisterAdapterSP nr21, IRegisterAdapterSP nr22, IRegisterAdapterSP nr23,
    IRegisterAdapterSP nr24, IRegisterAdapterSP nr52)
{
  nr21.reset();
  nr22.reset();
  nr23.reset();
  nr24.reset();
  nr52.reset();
}
