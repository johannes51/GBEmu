#ifndef IREGISTERADAPTER_H
#define IREGISTERADAPTER_H

#include <memory>

#include "defines.h"

class IRegisterAdapter {
public:
  virtual ~IRegisterAdapter() = default;
  DISABLE_COPY_AND_MOVE(IRegisterAdapter)

  virtual const uint8_t& getByte() const = 0;
  virtual void setByte(uint8_t value) = 0;

  virtual bool testBit(uint8_t pos) const = 0;
  virtual void setBit(uint8_t pos, bool value) = 0;

protected:
  IRegisterAdapter() = default;
};

#endif // IREGISTERADAPTER_H
