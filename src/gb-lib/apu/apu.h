#ifndef APU_H
#define APU_H

#include <memory>
#include <vector>

#include "ichannel.h"
#include "imixer.h"
#include "peripherals/peripheral.h"

class Apu : public Peripheral {
public:
  Apu(std::vector<IChannelSP>&& channels, IMixerUP&& mixer);
  ~Apu() override = default;

  void clock() override;

private:
  std::vector<IChannelSP> channels_;
  IMixerUP mixer_;
};

#endif // APU_H
