#ifndef BUFFERLOCATION_H
#define BUFFERLOCATION_H

#include "location8.h"

#include "mem/bufferbank.h"

class BufferLocation : public Location8 {
public:
  virtual ~BufferLocation() = default;
  DISABLE_COPY_AND_MOVE(BufferLocation)

  const uint8_t& get() const override;
  BufferLocation& operator=(const uint8_t& rhs) override;

protected:
  BufferLocation(BufferBank& area, address_type start);

private:
  BufferBank& area_;
  address_type start_;
};

#endif // BUFFERLOCATION_H
