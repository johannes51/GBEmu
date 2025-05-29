#ifndef BYTE_LOAD_ODDBALL_H
#define BYTE_LOAD_ODDBALL_H

#include "operation.h"

#include <optional>

#include "cpu/registers/registersinterface.h"

class ByteLoadOddball final : public Operation {
public:
  enum class Direction { Register, Indirect };
  enum class Indirection { RegisterC, ImmediateStandard, ImmediateZeroPage };

  ByteLoadOddball(Direction direction, Indirection indirection);
  ~ByteLoadOddball();

  void nextOpcode(const ILocation8& opcode) override;
  bool isComplete() override;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryWordView& memory) override;

private:
  const Direction direction_;
  const Indirection indirection_;
  std::unique_ptr<ILocation8> immediateL_;
  std::unique_ptr<ILocation8> immediateH_;
};

#endif // BYTE_LOAD_ODDBALL_H
