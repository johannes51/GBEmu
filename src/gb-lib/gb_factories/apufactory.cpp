#include "apufactory.h"

#include "apu/apu.h"
#include "apu/gbchannel1.h"
#include "apu/gbchannel2.h"
#include "apu/gbchannel3.h"
#include "apu/gbchannel4.h"
#include "apu/gbmixer.h"
#include "apuregisterfactory.h"

auto ApuFactory::constructApu() -> IApuUP
{
  ApuRegisterFactory a { ioBank_ };
  auto ch1 = std::make_shared<GbChannel1>(a.get(ApuRegisters::NR10), a.get(ApuRegisters::NR11),
      a.get(ApuRegisters::NR12), a.get(ApuRegisters::NR13), a.get(ApuRegisters::NR14), a.get(ApuRegisters::NR52));
  auto ch2 = std::make_shared<GbChannel2>(a.get(ApuRegisters::NR21), a.get(ApuRegisters::NR22),
      a.get(ApuRegisters::NR23), a.get(ApuRegisters::NR24), a.get(ApuRegisters::NR52));
  auto ch3
      = std::make_shared<GbChannel3>(a.get(ApuRegisters::NR30), a.get(ApuRegisters::NR31), a.get(ApuRegisters::NR32),
          a.get(ApuRegisters::NR33), a.get(ApuRegisters::NR34), a.get(ApuRegisters::NR52), waveRam_);
  auto ch4 = std::make_shared<GbChannel4>(a.get(ApuRegisters::NR41), a.get(ApuRegisters::NR42),
      a.get(ApuRegisters::NR43), a.get(ApuRegisters::NR44), a.get(ApuRegisters::NR52));

  auto mixer = std::make_unique<GbMixer>(a.get(ApuRegisters::NR50), a.get(ApuRegisters::NR51));

  return std::make_unique<Apu>(std::move(mixer),
      std::array<ChannelSP, 4U> { std::move(ch1), std::move(ch2), std::move(ch3), std::move(ch4) }, a.getAll(),
      std::move(div_apu_));
}
