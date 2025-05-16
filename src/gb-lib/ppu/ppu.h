#ifndef PPU_H
#define PPU_H

#include <unordered_map>

#include "defines.h"
#include "gb_factories/ppuregisterfactory.h"
#include "ippu.h"
#include "mem/registers/iregisteradapter.h"

class Ppu : public IPpu {
public:
  explicit Ppu(
      IRendererSP renderer, std::unordered_map<PpuRegisters, IRegisterAdapterUP>&& registers, IRegisterAdapter& rIf);
  DISABLE_COPY_AND_MOVE(Ppu)
  ~Ppu() override = default;

  void clock() override;

  const GbPixelBuffer& getBuffer() const override;

private:
  IRendererSP renderer_;
  GbPixelBuffer buffer_ = GbPixelBuffer {};
  std::unordered_map<PpuRegisters, IRegisterAdapterUP> registers_;
  IRegisterAdapter& if_;

  const IRegisterAdapter& lcdc_;
  IRegisterAdapter& stat_;
  IRegisterAdapter& ly_;
  const IRegisterAdapter& lyc_;

  uint16_t currentLine_ = 0U;
  uint16_t currentColumn_ = 0U;
};

#endif // PPU_H
