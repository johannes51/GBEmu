#ifndef FIXEDMASKIOREGISTER_H
#define FIXEDMASKIOREGISTER_H

#include "ioregister.h"

#include "util/helpers.h"

template <uint8_t Mask> class FixedMaskIoRegister : public IoRegister {
public:
  explicit FixedMaskIoRegister(const uint8_t initial = 0U)
      : IoRegister(initial)
  {
  }

  FixedMaskIoRegister& operator=(const uint8_t& rhs) override;

  void setByte(uint8_t value) override;
  void setBit(uint8_t pos, bool value) override;
};

template <uint8_t Mask> inline FixedMaskIoRegister<Mask>& FixedMaskIoRegister<Mask>::operator=(const uint8_t& rhs)
{
  IoRegister::operator=(rhs | Mask);
  return *this;
}

template <uint8_t Mask> inline void FixedMaskIoRegister<Mask>::setByte(uint8_t value)
{
  IoRegister::setByte(value | Mask);
}

template <uint8_t Mask> inline void FixedMaskIoRegister<Mask>::setBit(uint8_t pos, bool value)
{
  if (value || hlp::checkBit(Mask, pos)) {
    IoRegister::setBit(pos, true);
  } else {
    IoRegister::setBit(pos, false);
  }
}

#endif // FIXEDMASKIOREGISTER_H
