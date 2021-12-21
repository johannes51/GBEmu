#ifndef PALETTE_H
#define PALETTE_H

#include "mem/registers/iregisteradapter.h"

enum class Colors { White, LightGray, DarnkGray, Black };

class Palette {
public:
  explicit Palette(IRegisterAdapterSP bgp)
      : bgp_(std::move(bgp))
  {
  }

  Colors getColor(uint8_t index);

private:
  IRegisterAdapterSP bgp_;
};

#endif // PALETTE_H
