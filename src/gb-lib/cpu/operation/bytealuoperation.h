#ifndef BYTEALUOPERATION_H
#define BYTEALUOPERATION_H

#include "operation.h"

#include <optional>

#include "../registers/registersinterface.h"

namespace ops {
struct OpResult;
}

enum class Source { Register, Immediate, Indirect, None };

enum class ByteAluFunction { Add, AddCarry, Sub, SubCarry, Inc, Dec, And, Or, Xor, Cp };

class ByteAluOperation final : public Operation {
public:
  ByteAluOperation(ByteAluFunction function, Source source);
  ~ByteAluOperation() override = default;

  void nextOpcode(const ILocation8& opcode) override;
  bool isComplete() override;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryWordView& memory) override;

  void setRegister(ByteRegister registerName);

private:
  ILocation8& getSource(RegistersInterface& reg, IMemoryView& mem);

  const ByteAluFunction function_;
  const Source source_;
  std::optional<ByteRegister> register_;
  std::unique_ptr<ILocation8> immediate_;
};

#endif // BYTEALUOPERATION_H
