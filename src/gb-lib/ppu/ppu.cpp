#include "ppu.h"

Ppu::Ppu(IRendererSP renderer, IRegisterAdapterSP lcdc, IRegisterAdapterSP ly)
    : renderer_(std::move(renderer))
    , lcdc_(std::move(lcdc))
    , ly_(ly)
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
    ly_->set(currentLine_);
  }
  if (lcdc_->testBit(LcdEnableBit) && currentLine_ < LcdHeight) {
    renderer_->render(buffer_, currentLine_);
  }
}

auto Ppu::getBuffer() const -> const GbPixelBuffer& { return buffer_; }
