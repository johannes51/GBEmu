#ifndef MBC_H
#define MBC_H

#include "mem/imemoryview.h"

#include "defines.h"

class Mbc : public IMemoryView {
public:
  DISABLE_COPY_AND_MOVE(Mbc)
  ~Mbc() override = default;

  virtual void handleWrite(const address_type address, const uint8_t value) = 0;

protected:
  explicit Mbc() { }
};

#endif // MBC_H
