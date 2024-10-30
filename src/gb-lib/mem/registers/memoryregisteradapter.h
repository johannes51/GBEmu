#ifndef MEMORYREGISTERADAPTER_H
#define MEMORYREGISTERADAPTER_H

#include "iregisteradapter.h"

#include "../imemoryview.h"

class MemoryRegisterAdapter : public IRegisterAdapter {
public:
  MemoryRegisterAdapter(IMemoryViewSP mem, address_type address);
  DISABLE_COPY_AND_MOVE(MemoryRegisterAdapter)

  uint8_t get() const override;
  void set(uint8_t value) override;

  bool testBit(uint8_t pos) const override;
  void setBit(uint8_t pos, bool value) override;

private:
  IMemoryViewSP mem_;
  address_type address_;
};

#endif // MEMORYREGISTERADAPTER_H
