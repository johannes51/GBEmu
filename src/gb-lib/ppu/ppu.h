#ifndef PPU_H
#define PPU_H

#include "defines.h"
#include "ippu.h"

class Ppu : public IPpu {
public:
  explicit Ppu(IRendererSP renderer);
  DISABLE_COPY_AND_MOVE(Ppu)
  ~Ppu() override = default;

  void clock() override;

  const GbPixelBuffer& getBuffer() const override;

private:
  IRendererSP renderer_;
  GbPixelBuffer buffer_;

  uint8_t currentLine_ = 0U;
  uint8_t currentColumn_ = 0U;
};

#endif // PPU_H
