#include "gbchannel2.h"

GbChannel2::GbChannel2(IoBank& io, IRegisterAdapter& nr52)
    : GbPulseChannel(io, Nr20Adress, nr52)
{
}
