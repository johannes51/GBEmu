#ifndef BYTE_LOAD_INDIRECT_H
#define BYTE_LOAD_INDIRECT_H

#include "singleop.h"

#include "cpu/registers/registersinterface.h"

class ByteLoadIndirect final : public SingleOp<2> {
public:
  enum class Direction { Register, Indirect };
  enum class Post { Increment, Decrement, None };

  ByteLoadIndirect(
      Direction direction, ByteRegister directRegister, WordRegister indirectRegister, Post postAction = Post::None);
  ~ByteLoadIndirect();

  void execute(RegistersInterface& registers, IMemoryWordView& memory) override;

private:
  const Direction direction_;
  ByteRegister directRegister_ = ByteRegister::None;
  WordRegister indirectRegister_ = WordRegister::None;
  Post postAction_ = Post::None;
  std::unique_ptr<ILocation8> immediate_;
};

#endif // BYTE_LOAD_INDIRECT_H
