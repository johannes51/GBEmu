#include "gbmixer.h"

GbMixer::GbMixer(IRegisterAdapterSP nr12, IRegisterAdapterSP nr22, IRegisterAdapterSP nr32, IRegisterAdapterSP nr42,
    IRegisterAdapterSP nr50, IRegisterAdapterSP nr51, IRegisterAdapterSP nr52, std::array<IChannelSP, 4> channels)
    : nr12_(std::move(nr12))
    , nr22_(std::move(nr22))
    , nr32_(std::move(nr32))
    , nr42_(std::move(nr42))
    , nr50_(std::move(nr50))
    , nr51_(std::move(nr51))
    , nr52_(std::move(nr52))
    , channels_(std::move(channels))
{
}
