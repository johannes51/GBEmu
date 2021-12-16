#include "channelfactory.h"

#include "apu/gbchannel1.h"
#include "apu/gbchannel2.h"
#include "apu/gbchannel3.h"
#include "apu/gbchannel4.h"
#include "mem/registers/memoryregisteradapter.h"

auto ChannelFactory::constructChannels() -> std::vector<IChannelSP>
{
  auto ch1 = std::make_shared<GbChannel1>(registerFactory_.get(ApuRegisters::NR10),
      registerFactory_.get(ApuRegisters::NR11), registerFactory_.get(ApuRegisters::NR12),
      registerFactory_.get(ApuRegisters::NR13), registerFactory_.get(ApuRegisters::NR14));
  auto ch2
      = std::make_shared<GbChannel2>(registerFactory_.get(ApuRegisters::NR21), registerFactory_.get(ApuRegisters::NR22),
          registerFactory_.get(ApuRegisters::NR23), registerFactory_.get(ApuRegisters::NR24));
  auto ch3 = std::make_shared<GbChannel3>(registerFactory_.get(ApuRegisters::NR30),
      registerFactory_.get(ApuRegisters::NR31), registerFactory_.get(ApuRegisters::NR32),
      registerFactory_.get(ApuRegisters::NR33), registerFactory_.get(ApuRegisters::NR34));
  auto ch4
      = std::make_shared<GbChannel4>(registerFactory_.get(ApuRegisters::NR41), registerFactory_.get(ApuRegisters::NR42),
          registerFactory_.get(ApuRegisters::NR43), registerFactory_.get(ApuRegisters::NR44));

  return { std::move(ch1), std::move(ch2), std::move(ch3), std::move(ch4) };
}
