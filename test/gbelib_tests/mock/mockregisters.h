#ifndef MOCKREGISTERS_H
#define MOCKREGISTERS_H

#include "cpu/registersinterface.h"

#include <unordered_map>

class MockRegisters : public RegistersInterface {
public:
  MockRegisters();
  ~MockRegisters() override = default;

  RegisterUP get(ByteRegister registerName) override;
  RegisterUP get(WordRegister registerName) override;
  FlagsView& getFlags() override;
  const FlagsView& getFlags() const override;

private:
  std::unordered_map<WordRegister, uint16_t> regs_;
};

#endif // MOCKREGISTERS_H
