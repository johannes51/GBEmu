#ifndef IOREGISTER_H
#define IOREGISTER_H

#include "iregisteradapter.h"

#include "mem/ilocation8.h"

class IoRegister : public IRegisterAdapter, public ILocation8 {
public:
  explicit IoRegister(uint8_t initial = 0U);
  DISABLE_COPY_AND_MOVE(IoRegister)

  const uint8_t& get() const override;
  IoRegister& operator=(const uint8_t& rhs) override;

  const uint8_t& getByte() const override;
  void setByte(uint8_t value) override;

  bool testBit(uint8_t pos) const override;
  void setBit(uint8_t pos, bool value) override;

protected:
  uint8_t value_;
};

#endif // IOREGISTER_H
