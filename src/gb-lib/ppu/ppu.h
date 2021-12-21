#ifndef PPU_H
#define PPU_H

#include "irenderer.h"
#include "peripherals/peripheral.h"

class Ppu : public Peripheral {
public:
  explicit Ppu(IRendererSP renderer);

  void clock() override;

private:
  IRendererSP renderer_;
};

#endif // PPU_H
