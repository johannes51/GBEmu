#ifndef MOCKBYTELOCATIONADAPTER_H
#define MOCKBYTELOCATIONADAPTER_H

#include "mem/bytelocationadapter.h"

class MockByteLocationAdapter : public ByteLocationAdapter {
public:
  MockByteLocationAdapter(const uint8_t initial)
      : buffer_(initial)
  {
  }

  const uint8_t& get() const override { return buffer_; }
  void set(const uint8_t& value) override { buffer_ = value; }

  static ByteLocationAdapterUP make(const uint8_t& initial = 0U)
  {
    return std::make_unique<MockByteLocationAdapter>(initial);
  }

private:
  uint8_t buffer_;
};

#endif // MOCKBYTELOCATIONADAPTER_H
