#include "gbchannel3.h"

GbChannel3::GbChannel3(IRegisterAdapterSP nr30, IRegisterAdapterSP nr31, IRegisterAdapterSP nr32,
    IRegisterAdapterSP nr33, IRegisterAdapterSP nr34, IRegisterAdapterSP nr52, IMemoryViewSP waveRam)
{
  nr30.reset();
  nr31.reset();
  nr32.reset();
  nr33.reset();
  nr34.reset();
  nr52.reset();
  waveRam.reset();
}
