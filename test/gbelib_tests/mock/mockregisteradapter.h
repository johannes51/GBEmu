#ifndef MOCKREGISTERADAPTER_H
#define MOCKREGISTERADAPTER_H

#include "io/iregisteradapter.h"

#include "util/helpers.h"

class MockRegisterAdapter : public IRegisterAdapter {
public:
  explicit MockRegisterAdapter(uint8_t initial)
      : value_(initial)
  {
  }

  auto getByte() const -> const uint8_t& override { return value_; }
  void setByte(uint8_t value) override { value_ = value; }
  auto testBit(uint8_t pos) const -> bool override { return hlp::checkBit(value_, pos); }
  void setBit(uint8_t pos, bool value) override
  {
    auto temp = getByte();
    if (value) {
      hlp::setBit(temp, pos);
    } else {
      hlp::clearBit(temp, pos);
      ;
    }
    setByte(temp);
  }

  static std::unique_ptr<IRegisterAdapter> make(uint8_t initial = 0U)
  {
    return std::make_unique<MockRegisterAdapter>(initial);
  }

private:
  uint8_t value_;
};

#endif // MOCKREGISTERADAPTER_H
