#ifndef ZEROLOCATION_H
#define ZEROLOCATION_H

#include "../bytelocationadapter.h"
#include "../wordlocationadapter.h"
#include "defines.h"

class ZeroByteLocation final : public ByteLocationAdapter {
public:
  ZeroByteLocation() = default;
  DISABLE_COPY_AND_MOVE(ZeroByteLocation)
  ~ZeroByteLocation() override = default;

  const uint8_t& get() const override;
  void set(const uint8_t&) override;

  static ByteLocationAdapterUP copy();

private:
  static uint8_t zero_;
};

class ZeroWordLocation final : public WordLocationAdapter {
public:
  ZeroWordLocation() = default;
  DISABLE_COPY_AND_MOVE(ZeroWordLocation)
  ~ZeroWordLocation() override = default;

  const uint16_t& get() const override;
  void set(const uint16_t& value) override;

  static WordLocationAdapterUP copy();

private:
  static uint16_t zero_;
};

#endif // ZEROLOCATION_H
