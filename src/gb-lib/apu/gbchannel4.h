#ifndef GBCHANNEL4_H
#define GBCHANNEL4_H

#include "channel.h"

#include <array>

#include "channel_util/envelope.h"
#include "channel_util/length.h"
#include "mem/registers/iregisteradapter.h"

class GbChannel4 : public Channel {
public:
  GbChannel4(IRegisterAdapterSP nr41, IRegisterAdapterSP nr42, IRegisterAdapterSP nr43, IRegisterAdapterSP nr44,
      IRegisterAdapterSP nr52);

  void tickApuDiv(const uint8_t frameSequencerStep) override;
  void clock() override;

private:
  IRegisterAdapterSP nr43_;

  Length len_;
  Envelope env_;

  uint16_t period_ = 0U;
  uint16_t lsfr_ = 0xFFU;

  static constexpr std::array<uint8_t, 8U> DivisorTable = {
    8U,
    16U,
    32U,
    48U,
    64U,
    80U,
    96U,
    112U,
  };

  void shift();
  void loadPeriod();
};

#endif // GBCHANNEL4_H
