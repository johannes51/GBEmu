#ifndef LOAD_H
#define LOAD_H

#include <optional>

#include "operation.h"

#include "../registersinterface.h"
#include "location/location.h"

enum class Destination { Register8, Register16, ImmediateIndirect, RegisterIndirect };

enum class Source { Immediate, Register, ImmediateIndirect, RegisterIndirect };

class Load final : public Operation {
public:
  Load(Destination destination, Source source);
  ~Load();

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;

  uint cycles() override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

  void setDestination(ByteRegisters destRegister);
  void setDestination(WordRegisters destRegister);
  void setSource(ByteRegisters srcRegister);
  void setSource(WordRegisters srcRegister);

private:
  std::optional<Location<uint8_t>> immediate8_;
  std::optional<Location<uint16_t>> immediate16_;
  Destination destination_;
  Source source_;
  std::optional<ByteRegisters> destRegister8_;
  std::optional<ByteRegisters> srcRegister8_;
  std::optional<WordRegisters> destRegister16_;
  std::optional<WordRegisters> srcRegister16_;
};

#endif // LOAD_H
