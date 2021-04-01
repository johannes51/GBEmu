#ifndef JUMP_H
#define JUMP_H

#include <optional>

#include "location/location.h"
#include "operation.h"

enum class JumpType { Absolute, Relative };
enum class Condition { None, Z, NZ, C, NC };

class Jump final : public Operation {
public:
  Jump(JumpType type, Condition condition);
  ~Jump();

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;

  unsigned int cycles(const RegistersInterface& registers) override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  std::optional<Location<uint8_t>> lower_;
  std::optional<Location<uint8_t>> upper_;
  const JumpType type_;
  Condition condition_;
};

#endif // JUMP_H
