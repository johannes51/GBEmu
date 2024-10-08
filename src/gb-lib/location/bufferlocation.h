#ifndef BUFFERLOCATION_H
#define BUFFERLOCATION_H

#include "location.h"

#include "mem/bufferbank.h"

class BufferLocation : public Location {
public:
  virtual ~BufferLocation() = default;
  DISABLE_COPY_AND_MOVE(BufferLocation)

  const uint8_t& getByte() const override;
  const uint16_t& getWord() const override;
  Location& operator=(const uint8_t& rhs) override;
  Location& operator=(const uint16_t& rhs) override;

protected:
  BufferLocation(Type type, BufferBank& area, address_type start);

private:
  BufferBank& area_;
  address_type start_;
};

#endif // BUFFERLOCATION_H
