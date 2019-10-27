#ifndef JUMP_H
#define JUMP_H

#include <optional>

#include "location/location.h"
#include "operation.h"

enum class JumpType { Direct, Relative };

class Jump final : public Operation {
public:
  Jump(JumpType type);
  ~Jump();

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;

private:
  uint cycles() override;
  void executeImpl(RegistersInterface& registers, IMemoryView& memory) override;

  std::optional<Location<uint8_t>> lower_;
  std::optional<Location<uint8_t>> upper_;
  JumpType type_;
};

#endif // JUMP_H
