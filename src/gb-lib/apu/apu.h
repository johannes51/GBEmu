#ifndef APU_H
#define APU_H

#include <array>

#include "channel.h"
#include "defines.h"
#include "iapu.h"
#include "imixer.h"

class Apu : public IApu {
public:
  Apu(IMixerUP&& mixer, const std::array<ChannelSP, 4U>& channels, IRegisterAdapterSP divApu);
  DISABLE_COPY_AND_MOVE(Apu)
  ~Apu() override = default;

  void clock() override;

  const std::pair<double, double>& currentSample() override;

private:
  IMixerUP mixer_;
  std::array<ChannelSP, 4U> channels_;
  IRegisterAdapterSP divApu_;
  uint8_t oldDivApu_;

  std::pair<double, double> currentSample_;
};

#endif // APU_H
