#include "ppu.h"

Ppu::Ppu(IRendererSP renderer, IRegisterAdapterSP lcdc)
    : renderer_(std::move(renderer))
    , lcdc_(std::move(lcdc))
{
}

void Ppu::clock()
{
  currentColumn_ += DotsPerCycles;
  if (currentColumn_ >= LcdWidth) {
    currentColumn_ = 0U;
    ++currentLine_;
    if (currentLine_ >= LcdWithVBlankHeight) {
      currentLine_ = 0U;
    }
  }
  if (lcdc_->testBit(LcdEnableBit) && currentLine_ < LcdHeight) {
    renderer_->render(buffer_, currentLine_);
  }
}

auto Ppu::getBuffer() const -> const GbPixelBuffer& { return buffer_; }
