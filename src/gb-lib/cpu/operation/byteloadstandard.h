#ifndef BYTE_LOAD_STANDARD_H
#define BYTE_LOAD_STANDARD_H

#include "singleop.h"

#include "cpu/registers/registersinterface.h"

class ByteLoadStandard final : public SingleOp<1> {
public:
  static constexpr auto BaseDuration = 1U;

  ByteLoadStandard(ByteRegister destRegister, ByteRegister srcRegister);
  ~ByteLoadStandard() override;

  void execute(RegistersInterface& registers, IMemoryWordView& memory) override;

private:
  ByteRegister destRegister_;
  ByteRegister srcRegister_;
};

#endif // BYTE_LOAD_STANDARD_H
