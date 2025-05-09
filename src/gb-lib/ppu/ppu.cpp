#include "ppu.h"

#include "peripherals/gbinterrupthandler.h"
#include "ppu_constants.h"

Ppu::Ppu(IRendererSP renderer, IRegisterAdapterSP lcdc, IRegisterAdapterSP stat, IRegisterAdapterSP rIf,
    IRegisterAdapterSP ly, IRegisterAdapterSP lyc)
    : renderer_(std::move(renderer))
    , lcdc_(std::move(lcdc))
    , stat_(std::move(stat))
    , if_(std::move(rIf))
    , ly_(std::move(ly))
    , lyc_(std::move(lyc))
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

  ly_->set(currentLine_);
  stat_->setBit(LycLyCompareBit, currentLine_ == lyc_->get());

  bool isInterrupt = currentLine_ == lyc_->get();
  if (currentLine_ < LcdHeight) {
    if (currentColumn_ < Mode2Length) {
      stat_->setBit(PpuModeHigherBit, true); // Mode 2 = 0b10
      stat_->setBit(PpuModeLowerBit, false);
      isInterrupt |= lcdc_->testBit(Mode2IntBit);
    } else if (currentColumn_ < Mode2Length + Mode3MaxLength) {
      stat_->setBit(PpuModeHigherBit, true); // Mode 3 = 0b11
      stat_->setBit(PpuModeLowerBit, true);
    } else { // if (currentColumn_ < LcdWidth)
      stat_->setBit(PpuModeHigherBit, false); // Mode 0 = 0b00
      stat_->setBit(PpuModeLowerBit, false);
      isInterrupt |= lcdc_->testBit(Mode0IntBit);
    }
  } else {
    stat_->setBit(PpuModeHigherBit, false); // Mode 1 = 0b01
    stat_->setBit(PpuModeLowerBit, true);
    if (currentLine_ == LcdHeight) {
      if_->setBit(VBlankInterruptBit, true);
    }
  }
  if (isInterrupt) {
    if_->setBit(LcdInterruptBit, true);
  }

  if (lcdc_->testBit(LcdEnableBit) && currentLine_ < LcdHeight) {
    renderer_->render(buffer_, currentLine_);
  }
}

auto Ppu::getBuffer() const -> const GbPixelBuffer& { return buffer_; }
