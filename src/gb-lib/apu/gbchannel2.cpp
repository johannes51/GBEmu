#include "gbchannel2.h"

GbChannel2::GbChannel2(const IRegisterAdapter& nr21, const IRegisterAdapter& nr22, const IRegisterAdapter& nr23,
    const IRegisterAdapter& nr24, IRegisterAdapter& nr52)
    : GbPulseChannel(nr21, nr22, nr23, nr24, nr52)
{
}
