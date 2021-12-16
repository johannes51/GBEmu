#include "gbchannel4.h"

GbChannel4::GbChannel4(IRegisterAdapterSP nr41, IRegisterAdapterSP nr42, IRegisterAdapterSP nr43,
    IRegisterAdapterSP nr44, IRegisterAdapterSP nr52)
{
  nr41.reset();
  nr42.reset();
  nr43.reset();
  nr44.reset();
  nr52.reset();
}
