#ifndef JUMP_H
#define JUMP_H

#include "operation.h"

enum class JumpType { Direct, Relative };

class Jump final : public Operation {
public:
  Jump(JumpType type);
  ~Jump();

  void nextOpcode(LocationUP<uint8_t> opcode) override;
  bool isComplete() override;

private:
  uint cycles() override;
  void executeImpl() override;

  LocationUP<uint16_t> operand_;
};

#endif // JUMP_H
