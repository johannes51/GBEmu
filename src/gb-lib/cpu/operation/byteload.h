#ifndef BYTE_LOAD_H
#define BYTE_LOAD_H

#include <optional>

#include "operation.h"

#include "cpu/registersinterface.h"
#include "location/location.h"

class ByteLoad final : public Operation {
public:
  enum class Destination { Register, RegisterIndirect, ImmediateIndirect };
  enum class Source { Immediate, Register, RegisterIndirect, ImmediateIndirect };
  enum class Post { Increment, Decrement, None };
  static constexpr auto BaseDuration = 1U;

  ByteLoad(Destination destination, Source source, bool zeroPage = false);
  ~ByteLoad();

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;

  unsigned int cycles(const RegistersInterface& registers) override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

  void setDestination(ByteRegisters destRegister);
  void setDestination(WordRegisters destRegister);
  void setSource(ByteRegisters srcRegister);
  void setSource(WordRegisters srcRegister);
  void setPostAction(Post postAction);

private:
  const Destination destination_;
  const Source source_;
  ByteRegisters destRegister8_ = ByteRegisters::None;
  ByteRegisters srcRegister8_ = ByteRegisters::None;
  WordRegisters destRegister16_ = WordRegisters::None;
  WordRegisters srcRegister16_ = WordRegisters::None;
  Post postAction_ = Post::None;
  std::optional<Location<uint8_t>> immediate8_ = std::nullopt;
  std::optional<Location<uint16_t>> immediate16_ = std::nullopt;
  bool zeroPage_;
};

#endif // BYTE_LOAD_H
