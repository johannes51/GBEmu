#ifndef WORD_LOAD_H
#define WORD_LOAD_H

#include <optional>

#include "operation.h"

#include "cpu/registersinterface.h"
#include "location/location.h"

class WordLoad final : public Operation {
public:
  enum class Destination { Register, ImmediateIndirect, RegisterIndirect };
  enum class Source { Immediate, Register, RegisterImmediate };
  static constexpr auto BaseDuration = 3U;
  static constexpr auto ImmediateIndirectDuration = 5U;
  static constexpr auto RegisterImmediateDuration = 3U;

  WordLoad(Destination destination, Source source);
  ~WordLoad();

  void nextOpcode(LocationUP opcode) override;
  bool isComplete() override;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

  void setDestination(WordRegister destRegister);
  void setSource(WordRegister srcRegister);

private:
  const Destination destination_;
  const Source source_;
  WordRegister destRegister_ = WordRegister::None;
  WordRegister srcRegister_ = WordRegister::None;
  LocationUP immediate_ = nullptr;
};

#endif // WORD_LOAD_H
