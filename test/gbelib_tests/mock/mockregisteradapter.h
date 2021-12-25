#ifndef MOCKREGISTERADAPTER_H
#define MOCKREGISTERADAPTER_H

#include "mem/registers/iregisteradapter.h"

class MockRegisterAdapter : public IRegisterAdapter {
public:
  uint8_t get() const override { return 0; }
  bool testBit(uint8_t pos) const override
  {
    (void)pos;
    return false;
  }
  static std::shared_ptr<IRegisterAdapter> make() { return std::make_shared<MockRegisterAdapter>(); }
};

#endif // MOCKREGISTERADAPTER_H
