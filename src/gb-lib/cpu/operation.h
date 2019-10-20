#ifndef OPERATION_H
#define OPERATION_H

#include <stdint.h>


class Operation
{
public:
  Operation();

  bool nextOpcode(const uint8_t opcode);

private:
};

#endif // OPERATION_H
