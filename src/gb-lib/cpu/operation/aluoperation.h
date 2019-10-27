#ifndef ALUOPERATION_H
#define ALUOPERATION_H

#include <optional>

#include "../registersinterface.h"
#include "location/location.h"
#include "operation.h"

enum class Source { Register, Immediate, Indirect };

enum class AluFunction { Xor };

class AluOperation final : public Operation {
public:
  AluOperation(AluFunction function, Source source);
  ~AluOperation();

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;

  void setRegister(ByteRegisters registerName);

private:
  uint cycles() override;
  void executeImpl(RegistersInterface& registers, IMemoryView& memory) override;

  Location<uint8_t> getSource(RegistersInterface& registers);

  AluFunction function_;
  Source source_;
  std::optional<ByteRegisters> register_;
  std::optional<Location<uint8_t>> immediate_;
};

#endif // ALUOPERATION_H
