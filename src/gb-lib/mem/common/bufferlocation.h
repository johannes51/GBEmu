#ifndef BUFFERLOCATION_H
#define BUFFERLOCATION_H

#include "../ilocation8.h"

class BufferLocation : public ILocation8 {
public:
  explicit BufferLocation(uint8_t& buffer);
  virtual ~BufferLocation() = default;
  DISABLE_COPY_AND_MOVE(BufferLocation)

  const uint8_t& get() const override;
  BufferLocation& operator=(const uint8_t& rhs) override;

  void setBuffer(uint8_t& buffer);

private:
  uint8_t* buffer_;
};

#endif // BUFFERLOCATION_H
