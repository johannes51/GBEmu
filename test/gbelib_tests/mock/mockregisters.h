#ifndef MOCKREGISTERS_H
#define MOCKREGISTERS_H

#include "cpu/registers/registersinterface.h"

#include <unordered_map>

#include "mockflags.h"

#include "cpu/registers/register16.h"

class MockRegisters : public RegistersInterface {
public:
  MockRegisters();
  ~MockRegisters() override = default;

  ILocation8& get(ByteRegister registerName) override;
  ILocation16& get(WordRegister registerName) override;

  FlagsView& getFlags() override;
  const FlagsView& getFlags() const override;

private:
  std::unordered_map<WordRegister, uint16_t> regs_;
  MockFlags flags_;
  std::unique_ptr<Register16> reg_;
};

#endif // MOCKREGISTERS_H
