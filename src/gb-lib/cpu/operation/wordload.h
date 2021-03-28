#ifndef WORD_LOAD_H
#define WORD_LOAD_H

#include <optional>

#include "operation.h"

#include "../registersinterface.h"
#include "location/location.h"

class WordLoad final : public Operation {
public:
  enum class Destination { Register, ImmediateIndirect, RegisterIndirect };
  enum class Source { Immediate, Register };
  static constexpr auto BaseDuration = 3U;
  static constexpr auto ImmediateIndirectDuration = 5U;

  WordLoad(Destination destination, Source source);
  ~WordLoad();

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;

  unsigned int cycles() override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

  void setDestination(WordRegisters destRegister);
  void setSource(WordRegisters srcRegister);

private:
  const Destination destination_;
  const Source source_;
  WordRegisters destRegister_ = WordRegisters::None;
  WordRegisters srcRegister_ = WordRegisters::None;
  std::optional<Location<uint8_t>> immediate8_ = std::nullopt;
  std::optional<Location<uint16_t>> immediate16_ = std::nullopt;
};

#endif // WORD_LOAD_H
