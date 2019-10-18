#ifndef REGISTER_FLAGS_H
#define REGISTER_FLAGS_H

#include <cstddef>


enum RegisterFlags : std::size_t
{
  A, F,
  B, C,
  D, E,
  H, L,
  SPu, SPl,
  PCu, PCl,
  SIZE
};

#endif // REGISTER_FLAGS_H
