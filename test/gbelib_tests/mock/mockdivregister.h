#ifndef MOCKDIVREGISTER_H
#define MOCKDIVREGISTER_H

#include <gmock/gmock.h>

#include "mock/mockiobank.h"

#include "mem/registers/divregister.h"

class MockDivRegister : public DivRegister {
public:
  MOCK_METHOD(const uint8_t&, getByte, (), (const, override));
  MOCK_METHOD(void, setByte, (uint8_t), (override));
  MOCK_METHOD(bool, testBit, (uint8_t), (const, override));
  MOCK_METHOD(void, setBit, (uint8_t, bool), (override));

  MOCK_METHOD(void, clock, (), (override));

  MOCK_METHOD(bool, testBitSystemTimer, (uint8_t), (const, override));

  static std::shared_ptr<::testing::StrictMock<MockDivRegister>> make()
  {
    return std::make_shared<::testing::StrictMock<MockDivRegister>>();
  }

  explicit MockDivRegister()
      : DivRegister(b_)
  {
  }

private:
  static MockIoBank b_;
};

#endif // MOCKDIVREGISTER_H
