#ifndef BYTE_LOAD_IMMEDIATE_H
#define BYTE_LOAD_IMMEDIATE_H

#include <optional>

#include "operation.h"

#include "cpu/registersinterface.h"
#include "location/location.h"

class ByteLoadImmediate final : public Operation {
public:
  explicit ByteLoadImmediate(ByteRegister destRegister);
  explicit ByteLoadImmediate(WordRegister destRegister);
  ~ByteLoadImmediate() override;
  DISABLE_COPY_AND_MOVE(ByteLoadImmediate)

  void nextOpcode(LocationUP opcode) override;
  bool isComplete() override;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  ByteRegister destRegister_;
  bool indirect_;
  LocationUP immediate_;
};

#endif // BYTE_LOAD_IMMEDIATE_H
