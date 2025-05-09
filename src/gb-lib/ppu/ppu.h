#ifndef PPU_H
#define PPU_H

#include "defines.h"
#include "ippu.h"
#include "mem/registers/iregisteradapter.h"

class Ppu : public IPpu {
public:
  explicit Ppu(IRendererSP renderer, IRegisterAdapterSP lcdc, IRegisterAdapterSP stat, IRegisterAdapterSP rIf,
      IRegisterAdapterSP ly, IRegisterAdapterSP lyc);
  DISABLE_COPY_AND_MOVE(Ppu)
  ~Ppu() override = default;

  void clock() override;

  const GbPixelBuffer& getBuffer() const override;

private:
  IRendererSP renderer_;
  GbPixelBuffer buffer_ = GbPixelBuffer {};
  IRegisterAdapterSP lcdc_;
  IRegisterAdapterSP stat_;
  IRegisterAdapterSP if_;
  IRegisterAdapterSP ly_;
  IRegisterAdapterSP lyc_;

  uint16_t currentLine_ = 0U;
  uint16_t currentColumn_ = 0U;
};

#endif // PPU_H
