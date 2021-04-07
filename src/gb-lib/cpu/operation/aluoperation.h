#ifndef ALUOPERATION_H
#define ALUOPERATION_H

#include <optional>

#include "cpu/registersinterface.h"
#include "location/location.h"
#include "operation.h"

namespace ops {
struct OpResult;
}

enum class Source { Register, Immediate, Indirect, None };

enum class AluFunction { Add, Inc, Dec, Xor };

class AluOperation final : public Operation {
public:
  AluOperation(AluFunction function, Source source);
  ~AluOperation() override;

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;

  unsigned int cycles(const RegistersInterface& registers) override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

  void setRegister(ByteRegister registerName);

private:
  Location<uint8_t> getSource(RegistersInterface& reg, IMemoryView& mem);
  static void apply(FlagsView& flags, const ops::OpResult& result);

  const AluFunction function_;
  const Source source_;
  std::optional<ByteRegister> register_;
  std::optional<Location<uint8_t>> immediate_;
};

#endif // ALUOPERATION_H
