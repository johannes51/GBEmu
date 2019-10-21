#ifndef BUFFERBYTE_H
#define BUFFERBYTE_H

#include "locationbyte.h"

class BufferByte : public LocationByte {
public:
  virtual ~BufferByte() = default;

  virtual uint8_t operator*() override;
  virtual LocationByte &operator<<(const uint8_t &value) override;

protected:
  BufferByte(uint8_t &reference);

private:
  uint8_t &reference_;
};

#endif // BUFFERBYTE_H
