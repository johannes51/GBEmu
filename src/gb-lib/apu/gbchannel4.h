#ifndef GBCHANNEL4_H
#define GBCHANNEL4_H

#include "channel.h"

#include <array>

#include "channel_util/envelope.h"
#include "channel_util/length.h"
#include "io/iobank.h"
#include "io/ioregister.h"
#include "io/iregisteradapter.h"

class GbChannel4 : public Channel {
public:
  GbChannel4(IoBank& io, IRegisterAdapter& nr52);

  void tickApuDiv(const FrameSequence sequence) override;
  void clock() override;

private:
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

  static constexpr std::pair<uint8_t, uint8_t> DivisorBits = { { 0U }, { 3U } };
  static constexpr std::pair<uint8_t, uint8_t> ShiftBits = { { 4U }, { 4U } };

  static constexpr uint8_t LsfrHighBit = 15U;
  static constexpr uint8_t LsfrLowBit = 7U;
  static constexpr uint8_t LsfrFeedBit1 = 0U;
  static constexpr uint8_t LsfrFeedBit2 = 1U;
  static constexpr uint8_t LsfrWidthBit = 3U;

  static constexpr address_type Nr40Adress = 0xFF1FU;

  IoRegister nr41_;
  IoRegister nr42_;
  IoRegister nr43_;
  IoRegister nr44_;

  Length len_;
  Envelope env_;

  uint16_t period_ = 0U;
  uint16_t lsfr_ = 0xFFU;

  void shift();
  void loadPeriod();
};

#endif // GBCHANNEL4_H
