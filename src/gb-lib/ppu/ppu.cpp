#include "ppu.h"

Ppu::Ppu(IRendererSP renderer)
    : renderer_(std::move(renderer))
    , buffer_()
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
  renderer_->render(buffer_, currentLine_);
}

auto Ppu::getBuffer() const -> const GbPixelBuffer& { return buffer_; }
