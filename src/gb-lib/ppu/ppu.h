#ifndef PPU_H
#define PPU_H

#include <unordered_map>

#include "defines.h"
#include "io/iobank.h"
#include "io/ioregister.h"
#include "io/iregisteradapter.h"
#include "ippu.h"

class Ppu : public IPpu {
public:
  explicit Ppu(IoBank& io, IRegisterAdapter& rIf, IMemoryViewUP vram, IMemoryViewUP oam);
  DISABLE_COPY_AND_MOVE(Ppu)
  ~Ppu() override = default;

  void clock() override;

  void setRenderer(IRendererUP renderer);
  IRegisterAdapter& getLcdc();
  IRegisterAdapter& getScx();
  IRegisterAdapter& getScy();
  IRegisterAdapter& getWx();
  IRegisterAdapter& getWy();
  IRegisterAdapter& getBgp();
  IRegisterAdapter& getObp0();
  IRegisterAdapter& getObp1();

  const GbPixelBuffer& getBuffer() const override;

private:
  IRendererUP renderer_;
  GbPixelBuffer buffer_ = GbPixelBuffer {};
  IRegisterAdapter& if_;

  IMemoryViewUP vram_;
  IMemoryViewUP oam_;

  IoRegister lcdc_;
  IoRegister stat_;
  IoRegister scx_;
  IoRegister scy_;
  IoRegister wx_;
  IoRegister wy_;
  IoRegister bgp_;
  IoRegister obp0_;
  IoRegister obp1_;
  IoRegister ly_;
  IoRegister lyc_;

  uint16_t currentLine_ = 0U;
  uint16_t currentColumn_ = 0U;
};

#endif // PPU_H
