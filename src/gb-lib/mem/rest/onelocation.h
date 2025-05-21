#ifndef ONELOCATION_H
#define ONELOCATION_H

#include "mem/bytelocationadapter.h"

#include "defines.h"

class OneLocation final : public ByteLocationAdapter {
public:
  OneLocation() = default;
  DISABLE_COPY_AND_MOVE(OneLocation)
  ~OneLocation() override;

  const uint8_t& get() const override;
  void set(const uint8_t& value) override;

  static ByteLocationAdapterUP copy();

private:
  static uint8_t one_;
};

#endif // ONELOCATION_H
