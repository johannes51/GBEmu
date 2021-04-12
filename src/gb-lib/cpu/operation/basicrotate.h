#ifndef BASICROTATE_H
#define BASICROTATE_H

#include "singleop.h"

enum class RotateDirection { Right, Left };

class BasicRotate : public SingleOp<1> {
public:
  BasicRotate(const RotateDirection& direction, bool throughCarry);

  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  RotateDirection direction_;
  bool throughCarry_;
};

#endif // BASICROTATE_H
