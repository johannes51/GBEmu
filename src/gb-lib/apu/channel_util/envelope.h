#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "mem/registers/iregisteradapter.h"

class Envelope {
public:
  explicit Envelope(IRegisterAdapterSP nrX2);

  void clock();
  uint8_t vol();

private:
  IRegisterAdapterSP nrX2_;
  uint8_t counter_ = 0U;
  uint8_t volume_ = 0U;

  void readCounter();
  void moveVol();
  uint8_t readVolume() const;
};

#endif // ENVELOPE_H
