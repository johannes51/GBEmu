#ifndef BYTEARITHMETICDECODER_H
#define BYTEARITHMETICDECODER_H

#include "instructiondecoder.h"

#include "cpu/id/opcodeview.h"
#include "mem/ilocation8.h"

enum class ByteAluFunction;
enum class ByteRegister;

class ByteArithmeticDecoder : public InstructionDecoder {
public:
  ByteArithmeticDecoder() = default;

  OperationUP decode(const ILocation8& opcodeLocation) const override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static OperationUP incDec(const OpcodeView& opcode);
  static OperationUP bulkArithmetic(const OpcodeView& opcode);
  static OperationUP immediate(const OpcodeView& opcode);

  static ByteRegister sourceRegister(const OpcodeView& opcode);
  static ByteAluFunction bulkFunction(const OpcodeView& opcode);
  static ByteAluFunction immediateFunction(const OpcodeView& opcode);
};

#endif // BYTEARITHMETICDECODER_H
