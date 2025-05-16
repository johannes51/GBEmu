#ifndef GB_PALETTE_H
#define GB_PALETTE_H

#include "mem/registers/iregisteradapter.h"

enum class GbColors { White, LightGray, DarkGray, Black };

class GbPalette {
public:
  explicit GbPalette(const IRegisterAdapter& bgp)
      : bgp_(bgp)
  {
  }

  GbColors getColor(uint8_t index);

private:
  const IRegisterAdapter& bgp_;
};

#endif // PALETTE_H
