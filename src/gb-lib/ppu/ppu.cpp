#include "ppu.h"

#include "peripherals/gbinterrupthandler.h"
#include "ppu_constants.h"

Ppu::Ppu(IRendererSP renderer, std::unordered_map<PpuRegisters, IRegisterAdapterUP>&& registers, IRegisterAdapter& rIf)
    : renderer_(std::move(renderer))
    , registers_(std::move(registers))
    , if_(rIf)
    , lcdc_(*registers_[PpuRegisters::LCDC])
    , stat_(*registers_[PpuRegisters::STAT])
    , ly_(*registers_[PpuRegisters::LY])
    , lyc_(*registers_[PpuRegisters::LYC])
{
}

void Ppu::clock()
{
  const auto enabled = lcdc_.testBit(LcdEnableBit);
  if (enabled) {
    currentColumn_ += DotsPerCycles;
    if (currentColumn_ >= LcdWidth) {
      currentColumn_ = 0U;
      ++currentLine_;
      if (currentLine_ >= LcdWithVBlankHeight) {
        currentLine_ = 0U;
      }
    }
    ly_.setByte(currentLine_);
    stat_.setBit(LycLyCompareBit, currentLine_ == lyc_.getByte());

    bool isInterrupt = currentLine_ == lyc_.getByte();
    if (currentLine_ < LcdHeight) {
      if (currentColumn_ < Mode2Length) {
        stat_.setBit(PpuModeHigherBit, true); // Mode 2 = 0b10
        stat_.setBit(PpuModeLowerBit, false);
        isInterrupt |= lcdc_.testBit(Mode2IntBit);

        renderer_->render(buffer_, currentLine_);
      } else if (currentColumn_ < Mode2Length + Mode3MaxLength) {
        stat_.setBit(PpuModeHigherBit, true); // Mode 3 = 0b11
        stat_.setBit(PpuModeLowerBit, true);
      } else { // if (currentColumn_ < LcdWidth)
        stat_.setBit(PpuModeHigherBit, false); // Mode 0 = 0b00
        stat_.setBit(PpuModeLowerBit, false);
        isInterrupt |= lcdc_.testBit(Mode0IntBit);
      }
    } else {
      stat_.setBit(PpuModeHigherBit, false); // Mode 1 = 0b01
      stat_.setBit(PpuModeLowerBit, true);
      if (currentLine_ == LcdHeight) {
        if_.setBit(VBlankInterruptBit, true);
      }
    }
    if (isInterrupt) {
      if_.setBit(LcdInterruptBit, true);
    }
  } else {
    currentLine_ = 0U;
    currentColumn_ = 0U;
  }
}

auto Ppu::getBuffer() const -> const GbPixelBuffer& { return buffer_; }
