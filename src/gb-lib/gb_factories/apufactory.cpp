#include "apufactory.h"

#include "apu/apu.h"
#include "apu/gbchannel1.h"
#include "apu/gbchannel2.h"
#include "apu/gbchannel3.h"
#include "apu/gbchannel4.h"
#include "apu/gbmixer.h"

auto ApuFactory::constructApu() -> std::unique_ptr<Apu>
{
  auto result = std::make_unique<Apu>();

  result->addChannel(std::make_unique<GbChannel1>(ioBank_, result->getNr52()));
  result->addChannel(std::make_unique<GbChannel2>(ioBank_, result->getNr52()));
  result->addChannel(std::make_unique<GbChannel3>(ioBank_, result->getNr52(), waveRam_));
  result->addChannel(std::make_unique<GbChannel4>(ioBank_, result->getNr52()));

  result->setMixer(std::make_unique<GbMixer>(ioBank_));

  return result;
}
