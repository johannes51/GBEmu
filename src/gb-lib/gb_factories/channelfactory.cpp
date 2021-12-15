#include "channelfactory.h"

#include "apu/gbchannel1.h"
#include "apu/gbchannel2.h"
#include "apu/gbchannel3.h"
#include "apu/gbchannel4.h"
#include "mem/registers/memoryregisteradapter.h"

std::vector<IChannelSP> ChannelFactory::constructChannels()
{
  auto ch1 = std::make_shared<GbChannel1>(std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0),
      std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0), std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0),
      std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0), std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0));
  auto ch2 = std::make_shared<GbChannel2>(std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0),
      std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0), std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0),
      std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0));
  auto ch3 = std::make_shared<GbChannel3>(std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0),
      std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0), std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0),
      std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0), std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0));
  auto ch4 = std::make_shared<GbChannel4>(std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0),
      std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0), std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0),
      std::make_shared<MemoryRegisterAdapter>(ioBank_, 0x0));

  return { std::move(ch1), std::move(ch2), std::move(ch3), std::move(ch4) };
}
