#ifndef IREGISTERADAPTER_H
#define IREGISTERADAPTER_H

#include <memory>

#include "defines.h"

class IRegisterAdapter {
public:
  virtual ~IRegisterAdapter() = default;
  DISABLE_COPY_AND_MOVE(IRegisterAdapter)

  virtual uint8_t get() const = 0;
  virtual void set(uint8_t value) = 0;

  virtual bool testBit(uint8_t pos) const = 0;
  virtual void setBit(uint8_t pos, bool value) = 0;

protected:
  IRegisterAdapter() = default;
};

using IRegisterAdapterSP = std::shared_ptr<IRegisterAdapter>;

#endif // IREGISTERADAPTER_H
