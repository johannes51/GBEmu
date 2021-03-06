#ifndef ALUOPERATION_H
#define ALUOPERATION_H

#include <optional>

#include "../registersinterface.h"
#include "location/location.h"
#include "operation.h"

enum class Source { Register, Immediate, Indirect, None };

enum class AluFunction { Dec, Xor };

class AluOperation final : public Operation {
public:
  AluOperation(AluFunction function, Source source);
  ~AluOperation() override;

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;

  unsigned int cycles() override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

  void setRegister(ByteRegisters registerName);

private:
  Location<uint8_t> getSource(RegistersInterface& registers);

  const AluFunction function_;
  const Source source_;
  std::optional<ByteRegisters> register_;
  std::optional<Location<uint8_t>> immediate_;
};

#endif // ALUOPERATION_H
