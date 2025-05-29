#include "gbchannel4.h"

#include "util/helpers.h"

GbChannel4::GbChannel4(IoBank& io, IRegisterAdapter& nr52)
    : Channel(nr52)
    , len_(nr41_, nr44_)
    , env_(nr42_)
{
  io.registerRegister(Nr40Adress + 1U, &nr41_);
  io.registerRegister(Nr40Adress + 2U, &nr42_);
  io.registerRegister(Nr40Adress + 3U, &nr43_);
  io.registerRegister(Nr40Adress + 4U, &nr44_);
  loadPeriod();
}

void GbChannel4::clock()
{
  if (--period_ == 0U) {
    shift();
    loadPeriod();
  }
}

void GbChannel4::tickApuDiv(const FrameSequence sequence)
{
  switch (sequence) {
  case FrameSequence::Phase0:
  case FrameSequence::Phase2:
  case FrameSequence::Phase4:
  case FrameSequence::Phase6:
    len_.clock();
    if (len_.isRunOut()) {
      disable();
    }
    break;
  default:
    break;
  }
}

void GbChannel4::shift()
{
  const auto newBit = (hlp::checkBit(lsfr_, LsfrFeedBit1) ^ hlp::checkBit(lsfr_, LsfrFeedBit2)) == 1U;
  hlp::writeBit(lsfr_, LsfrHighBit, newBit);
  if (nr43_.testBit(LsfrWidthBit)) {
    hlp::writeBit(lsfr_, LsfrLowBit, newBit);
  }
  lsfr_ >>= 1U;
  dac_.set((lsfr_ & 1U) * env_.vol());
}

void GbChannel4::loadPeriod()
{
  period_ = DivisorTable[hlp::getBits(nr43_.getByte(), DivisorBits.first, DivisorBits.second)]
      << hlp::getBits(nr43_.getByte(), ShiftBits.first, ShiftBits.second);
}
