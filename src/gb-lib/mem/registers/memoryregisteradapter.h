#ifndef MEMORYREGISTERADAPTER_H
#define MEMORYREGISTERADAPTER_H

#include "iregisteradapter.h"

#include "../imemoryview.h"

class MemoryRegisterAdapter : public IRegisterAdapter {
public:
  MemoryRegisterAdapter(IMemoryViewSP mem, address_type address);

private:
  IMemoryViewSP mem_;
  address_type address_;
};

#endif // MEMORYREGISTERADAPTER_H
