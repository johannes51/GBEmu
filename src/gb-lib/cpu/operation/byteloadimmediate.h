#ifndef BYTE_LOAD_IMMEDIATE_H
#define BYTE_LOAD_IMMEDIATE_H

#include <optional>

#include "operation.h"

#include "cpu/registers/registersinterface.h"
#include "mem/rest/variablelocation.h"

class ByteLoadImmediate final : public Operation {
public:
  explicit ByteLoadImmediate(ByteRegister destRegister);
  explicit ByteLoadImmediate(WordRegister destRegister);
  ~ByteLoadImmediate() override;
  DISABLE_COPY_AND_MOVE(ByteLoadImmediate)

  void nextOpcode(const ILocation8& opcode) override;
  bool isComplete() override;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryWordView& memory) override;

private:
  ByteRegister destRegister_;
  bool indirect_;
  std::unique_ptr<ILocation8> immediate_;
};

#endif // BYTE_LOAD_IMMEDIATE_H
