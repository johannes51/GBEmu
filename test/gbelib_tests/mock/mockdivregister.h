#ifndef MOCKDIVREGISTER_H
#define MOCKDIVREGISTER_H

#include <gmock/gmock.h>

#include "mem/registers/divregister.h"

class MockDivRegister : public DivRegister {
public:
  MOCK_METHOD(uint8_t, get, (), (const, override));
  MOCK_METHOD(void, set, (uint8_t), (override));
  MOCK_METHOD(bool, testBit, (uint8_t), (const, override));
  MOCK_METHOD(void, setBit, (uint8_t, bool), (override));

  MOCK_METHOD(void, clock, (), (override));

  MOCK_METHOD(bool, testBitSystemTimer, (uint8_t), (const, override));

  static std::shared_ptr<::testing::StrictMock<MockDivRegister>> make()
  {
    return std::make_shared<::testing::StrictMock<MockDivRegister>>();
  }

  explicit MockDivRegister()
      : DivRegister(IMemoryViewSP {})
  {
  }
};

#endif // MOCKDIVREGISTER_H
