#ifndef BUFFERLOCATION_H
#define BUFFERLOCATION_H

#include "../location8.h"

#include "bufferbank.h"

class BufferLocation : public ByteLocationAdapter {
public:
  explicit BufferLocation(uint8_t& buffer);
  virtual ~BufferLocation() = default;
  DISABLE_COPY_AND_MOVE(BufferLocation)

  const uint8_t& get() const override;
  void set(const uint8_t& value) override;

private:
  uint8_t& buffer_;
};

#endif // BUFFERLOCATION_H
