#ifndef MOCKREGISTERADAPTER_H
#define MOCKREGISTERADAPTER_H

#include "mem/registers/iregisteradapter.h"

#include "util/helpers.h"

class MockRegisterAdapter : public IRegisterAdapter {
public:
  explicit MockRegisterAdapter(uint8_t initial)
      : value_(initial)
  {
  }

  auto get() const -> uint8_t override { return value_; }
  void set(uint8_t value) override { value_ = value; }
  auto testBit(uint8_t pos) const -> bool override { return hlp::checkBit(value_, pos); }
  void setBit(uint8_t pos, bool value) override
  {
    auto temp = get();
    if (value) {
      hlp::setBit(temp, pos);
    } else {
      hlp::clearBit(temp, pos);
      ;
    }
    set(temp);
  }

  static std::shared_ptr<IRegisterAdapter> make(uint8_t initial = 0U)
  {
    return std::make_shared<MockRegisterAdapter>(initial);
  }

private:
  uint8_t value_;
};

#endif // MOCKREGISTERADAPTER_H
