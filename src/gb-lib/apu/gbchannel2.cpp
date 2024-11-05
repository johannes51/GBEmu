#include "gbchannel2.h"

GbChannel2::GbChannel2(IRegisterAdapterSP nr21, IRegisterAdapterSP nr22, IRegisterAdapterSP nr23,
    IRegisterAdapterSP nr24, IRegisterAdapterSP nr52)
    : GbPulseChannel(std::move(nr21), std::move(nr22), std::move(nr23), std::move(nr24), std::move(nr52))
{
}
