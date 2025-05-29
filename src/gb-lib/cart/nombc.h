#ifndef NOMBC_H
#define NOMBC_H

#include "mbc.h"

class NoMbc final : public Mbc {
public:
  explicit NoMbc(IMemoryViewUP rom0, IMemoryViewUP rom1);
  DISABLE_COPY_AND_MOVE(NoMbc)
  ~NoMbc() override = default;

  ILocation8& getLocation8(const address_type address) override;

  void handleWrite(const address_type address, const uint8_t value) override;

private:
  IMemoryViewUP rom0_;
  IMemoryViewUP rom1_;
};

#endif // NOMBC_H
