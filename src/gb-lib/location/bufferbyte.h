#ifndef BUFFERBYTE_H
#define BUFFERBYTE_H

#include "locationbyte.h"

class BufferByte : public LocationByte {
public:
  virtual ~BufferByte() = default;
  DISABLE_COPY_AND_MOVE(BufferByte)

  uint8_t get() const override;
  virtual void set(const uint8_t& value) override;

protected:
  BufferByte(uint8_t& reference);

private:
  uint8_t& reference_;
};

#endif // BUFFERBYTE_H
