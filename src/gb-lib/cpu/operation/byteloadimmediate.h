#ifndef BYTE_LOAD_IMMEDIATE_H
#define BYTE_LOAD_IMMEDIATE_H

#include <optional>

#include "operation.h"

#include "cpu/registersinterface.h"
#include "location/location8.h"

class ByteLoadImmediate final : public Operation {
public:
  explicit ByteLoadImmediate(ByteRegister destRegister);
  explicit ByteLoadImmediate(WordRegister destRegister);
  ~ByteLoadImmediate() override;
  DISABLE_COPY_AND_MOVE(ByteLoadImmediate)

  void nextOpcode(Location8UP opcode) override;
  bool isComplete() override;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  ByteRegister destRegister_;
  bool indirect_;
  Location8UP immediate_;
};

#endif // BYTE_LOAD_IMMEDIATE_H
