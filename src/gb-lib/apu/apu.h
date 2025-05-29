#ifndef APU_H
#define APU_H

#include <array>

#include "channel.h"
#include "channel_util/framesequencer.h"
#include "defines.h"
#include "iapu.h"
#include "imixer.h"
#include "io/fixedmaskioregister.h"
#include "io/ioregister.h"

class Apu : public IApu {
public:
  explicit Apu();
  DISABLE_COPY_AND_MOVE(Apu)
  ~Apu() override = default;

  void clock() override;

  const std::pair<double, double>& currentSample() override;

  IRegisterAdapter& getDivApu();
  IRegisterAdapter& getNr52();

  void addChannel(ChannelUP channel);
  void setMixer(IMixerUP mixer);

private:
  IMixerUP mixer_;
  std::array<ChannelUP, 4U> channels_;
  FixedMaskIoRegister<0b01110000U> nr52_;
  IoRegister divApu_;
  FrameSequencer fs_;

  std::pair<double, double> currentSample_;
};

#endif // APU_H
