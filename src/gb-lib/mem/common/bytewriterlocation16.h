#ifndef BYTEWRITERLOCATION16_H
#define BYTEWRITERLOCATION16_H

#include "../ilocation16.h"

#include "../imemoryview.h"
#include "defines.h"

class ByteWriterLocation16 : public ILocation16 {
public:
  explicit ByteWriterLocation16(IMemoryView& byteView, address_type address);
  DISABLE_COPY_AND_MOVE(ByteWriterLocation16)
  ~ByteWriterLocation16() override = default;

  const uint16_t& get() const override;
  ByteWriterLocation16& operator=(const uint16_t& rhs) override;

  void setAddress(address_type value);

private:
  IMemoryView& byteView_;
  address_type address_;
  mutable uint16_t buffer_;
};

#endif // BYTEWRITERLOCATION16_H
