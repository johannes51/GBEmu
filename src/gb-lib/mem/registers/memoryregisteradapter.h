#ifndef MEMORYREGISTERADAPTER_H
#define MEMORYREGISTERADAPTER_H

#include "iregisteradapter.h"

#include "../common//bufferlocation.h"
#include "../imemoryview.h"

class MemoryRegisterAdapter : public IRegisterAdapter {
public:
  explicit MemoryRegisterAdapter(ByteLocationAdapterUP bufferLocation);
  DISABLE_COPY_AND_MOVE(MemoryRegisterAdapter)

  const uint8_t& getByte() const override;
  void setByte(const uint8_t value) override;

  bool testBit(uint8_t pos) const override;
  void setBit(uint8_t pos, bool value) override;

private:
  ByteLocationAdapterUP bufferLocation_;
};

#endif // MEMORYREGISTERADAPTER_H
