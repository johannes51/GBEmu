#include "gbmixer.h"

GbMixer::GbMixer(IRegisterAdapterSP nr12, IRegisterAdapterSP nr22, IRegisterAdapterSP nr32, IRegisterAdapterSP nr42,
    IRegisterAdapterSP nr50, IRegisterAdapterSP nr51, IRegisterAdapterSP nr52)
{
  nr12.reset();
  nr22.reset();
  nr32.reset();
  nr42.reset();
  nr50.reset();
  nr51.reset();
  nr52.reset();
}
