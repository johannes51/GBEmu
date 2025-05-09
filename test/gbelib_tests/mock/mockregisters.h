#ifndef MOCKREGISTERS_H
#define MOCKREGISTERS_H

#include "mockflags.h"

#include "cpu/registersinterface.h"

#include <unordered_map>

class MockRegisters : public RegistersInterface {
public:
  MockRegisters();
  ~MockRegisters() override = default;

  Register8UP get(ByteRegister registerName) override;
  Register16UP get(WordRegister registerName) override;
  FlagsView& getFlags() override;
  const FlagsView& getFlags() const override;

private:
  std::unordered_map<WordRegister, uint16_t> regs_;
  MockFlags flags_;
};

#endif // MOCKREGISTERS_H
