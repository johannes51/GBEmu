#include "ppu.h"

Ppu::Ppu(IRendererSP renderer)
    : renderer_(std::move(renderer))
    , buffer_()
{
}

void Ppu::clock()
{
  constexpr auto CYCLES_PER_FRAME = 1000000 / 60;
  static uint32_t i = 0;
  if (i >= CYCLES_PER_FRAME) {
    i = 0;
    renderer_->render(buffer_);
  } else {
    ++i;
  }
}

auto Ppu::getBuffer() const -> const GbPixelBuffer& { return buffer_; }
