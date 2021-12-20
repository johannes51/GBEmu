#ifndef MEMORYREGISTERADAPTER_H
#define MEMORYREGISTERADAPTER_H

#include "iregisteradapter.h"

#include "../imemoryview.h"

class MemoryRegisterAdapter : public IRegisterAdapter {
public:
  MemoryRegisterAdapter(IMemoryViewSP mem, address_type address);

  uint8_t get() const override;

  bool testBit(uint8_t pos) const override;

private:
  IMemoryViewSP mem_;
  address_type address_;
};

#endif // MEMORYREGISTERADAPTER_H
