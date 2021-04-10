#ifndef JUMP_H
#define JUMP_H

#include <optional>

#include "location/location.h"
#include "operation.h"

enum class JumpType { Regular, Call, Return, RetI };
enum class TargetType { Absolute, Relative };
enum class Condition { None, Z, NZ, C, NC };

class Jump final : public Operation {
public:
  static constexpr auto TakenJump = 4;
  static constexpr auto SkippedJump = 3;
  static constexpr auto TakenCall = 6;
  static constexpr auto SkippedCall = 3;
  static constexpr auto TakenReturn = 5;
  static constexpr auto SkippedReturn = 2;
  static constexpr auto NormalReturn = 4;

  Jump(JumpType type, TargetType target, Condition condition);
  ~Jump();

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;

  unsigned cycles(const RegistersInterface& registers) override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  bool taken(const FlagsView& flags) const;

  std::optional<Location<uint8_t>> lower_;
  std::optional<Location<uint8_t>> upper_;
  const JumpType type_;
  const TargetType target_;
  const Condition condition_;
};

#endif // JUMP_H
