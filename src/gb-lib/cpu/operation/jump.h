#ifndef JUMP_H
#define JUMP_H

#include <optional>

#include "location/location.h"
#include "operation.h"

enum class JumpType { Regular, Indirect, Call, Return, RetI, Reset };
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

  void showFlags(const FlagsView& flags) override;
  void nextOpcode(LocationUP opcode) override;
  bool isComplete() override;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  LocationUP param_;
  const JumpType type_;
  const TargetType target_;
  const Condition condition_;
  std::optional<bool> taken_;
};

#endif // JUMP_H
