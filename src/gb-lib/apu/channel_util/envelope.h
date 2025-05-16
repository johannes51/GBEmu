#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "mem/registers/iregisteradapter.h"

class Envelope {
public:
  explicit Envelope(const IRegisterAdapter& nrX2);

  void clock();
  uint8_t vol() const;

private:
  void readCounter();
  void moveVol();
  uint8_t readVolume() const;

  static constexpr uint8_t MaxVolume = 0xFU;
  static constexpr std::pair<uint8_t, uint8_t> CounterBits = { { 0U }, { 3U } };

  const IRegisterAdapter& nrX2_;
  uint8_t volume_;
  uint8_t counter_ = 0U;
};

#endif // ENVELOPE_H
