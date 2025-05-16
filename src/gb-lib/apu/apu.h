#ifndef APU_H
#define APU_H

#include <array>

#include "channel.h"
#include "channel_util/framesequencer.h"
#include "defines.h"
#include "gb_factories/apuregisterfactory.h"
#include "iapu.h"
#include "imixer.h"

class Apu : public IApu {
public:
  Apu(IMixerUP mixer, const std::array<ChannelSP, 4U>& channels,
      std::unordered_map<ApuRegisters, IRegisterAdapterUP>&& registers, IRegisterAdapterUP divApu);
  DISABLE_COPY_AND_MOVE(Apu)
  ~Apu() override = default;

  void clock() override;

  const std::pair<double, double>& currentSample() override;

private:
  IMixerUP mixer_;
  std::array<ChannelSP, 4U> channels_;
  std::unordered_map<ApuRegisters, IRegisterAdapterUP> registers_;
  IRegisterAdapterUP divApu_;
  FrameSequencer fs_;

  std::pair<double, double> currentSample_;
};

#endif // APU_H
