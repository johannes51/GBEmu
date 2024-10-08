#ifndef BYTE_LOAD_ODDBALL_H
#define BYTE_LOAD_ODDBALL_H

#include "operation.h"

#include "cpu/registersinterface.h"

class ByteLoadOddball final : public Operation {
public:
  enum class Direction { Register, Indirect };
  enum class Indirection { RegisterC, ImmediateStandard, ImmediateZeroPage };

  ByteLoadOddball(Direction direction, Indirection indirection);
  ~ByteLoadOddball();

  void nextOpcode(LocationUP opcode) override;
  bool isComplete() override;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  const Direction direction_;
  const Indirection indirection_;
  LocationUP immediate_;
};

#endif // BYTE_LOAD_ODDBALL_H
