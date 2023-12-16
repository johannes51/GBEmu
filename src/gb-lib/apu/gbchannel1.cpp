#include "gbchannel1.h"

GbChannel1::GbChannel1(IRegisterAdapterSP nr10, IRegisterAdapterSP nr11, IRegisterAdapterSP nr12,
    IRegisterAdapterSP nr13, IRegisterAdapterSP nr14, IRegisterAdapterSP nr52)
    : nr10_(std::move(nr10))
    , nr11_(std::move(nr11))
    , nr12_(std::move(nr12))
    , nr13_(std::move(nr13))
    , nr14_(std::move(nr14))
    , nr52_(std::move(nr52))
{
}
