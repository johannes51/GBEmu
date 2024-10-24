#ifndef PPU_H
#define PPU_H

#include "defines.h"
#include "ippu.h"
#include "irenderer.h"

class Ppu : public IPpu {
public:
  explicit Ppu(IRendererSP renderer);
  DISABLE_COPY_AND_MOVE(Ppu)
  ~Ppu() override = default;

  void clock() override;

  const IPixelBuffer& getBuffer() const;

private:
  IRendererSP renderer_;
  IPixelBuffer buffer_;
};

#endif // PPU_H
