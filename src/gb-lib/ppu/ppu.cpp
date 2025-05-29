#include "ppu.h"

#include "peripherals/gbinterrupthandler.h"
#include "ppu_constants.h"

constexpr address_type LcdcAddress = 0xFF40U;
constexpr uint8_t LcdcInitial = 0x91U;
constexpr address_type StatAddress = 0xFF41U;
constexpr uint8_t StatInitial = 0x85U;
constexpr address_type ScxAddress = 0xFF43U;
constexpr address_type ScyAddress = 0xFF42U;
constexpr address_type WxAddress = 0xFF4BU;
constexpr address_type WyAddress = 0xFF4AU;
constexpr address_type BgpAddress = 0xFF47U;
constexpr uint8_t BgpInitial = 0xFCU;
constexpr address_type Obp0Address = 0xFF48U;
constexpr address_type Obp1Address = 0xFF49U;
constexpr uint8_t ObpInitial = 0xFFU;
constexpr address_type LyAddress = 0xFF44U;
constexpr address_type LycAddress = 0xFF45U;

Ppu::Ppu(IoBank& io, IRegisterAdapter& rIf, IMemoryViewUP vram, IMemoryViewUP oam)
    : renderer_(nullptr)
    , if_(rIf)
    , vram_(std::move(vram))
    , oam_(std::move(oam))
    , lcdc_(LcdcInitial)
    , stat_(StatInitial)
    , scx_()
    , scy_()
    , wx_()
    , wy_()
    , bgp_(BgpInitial)
    , obp0_(ObpInitial)
    , obp1_(ObpInitial)
    , ly_()
    , lyc_()
{
  io.registerRegister(LcdcAddress, &lcdc_);
  io.registerRegister(StatAddress, &stat_);
  io.registerRegister(ScxAddress, &scx_);
  io.registerRegister(ScyAddress, &scy_);
  io.registerRegister(WxAddress, &wx_);
  io.registerRegister(WyAddress, &wy_);
  io.registerRegister(BgpAddress, &bgp_);
  io.registerRegister(Obp0Address, &obp0_);
  io.registerRegister(Obp1Address, &obp1_);
  io.registerRegister(LyAddress, &ly_);
  io.registerRegister(LycAddress, &lyc_);
}

void Ppu::clock()
{
  const auto enabled = lcdc_.testBit(LcdEnableBit);
  if (enabled) {
    auto drawNextLine = false;
    currentColumn_ += DotsPerCycles;
    if (currentColumn_ >= LcdWidth) {
      currentColumn_ = 0U;
      ++currentLine_;
      if (currentLine_ >= LcdWithVBlankHeight) {
        currentLine_ = 0U;
      }
      drawNextLine = true;
    }
    ly_.setByte(currentLine_);
    stat_.setBit(LycLyCompareBit, currentLine_ == lyc_.getByte());

    bool isInterrupt = currentLine_ == lyc_.getByte();
    if (currentLine_ < LcdHeight) {
      if (currentColumn_ < Mode2Length) {
        stat_.setBit(PpuModeHigherBit, true); // Mode 2 = 0b10
        stat_.setBit(PpuModeLowerBit, false);
        isInterrupt |= lcdc_.testBit(Mode2IntBit);

        if (drawNextLine) {
          renderer_->render(buffer_, currentLine_);
        }
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

void Ppu::setRenderer(IRendererUP renderer) { renderer_ = std::move(renderer); }

auto Ppu::getLcdc() -> IRegisterAdapter& { return lcdc_; }

auto Ppu::getScx() -> IRegisterAdapter& { return scx_; }

auto Ppu::getScy() -> IRegisterAdapter& { return scy_; }

auto Ppu::getWx() -> IRegisterAdapter& { return wx_; }

auto Ppu::getWy() -> IRegisterAdapter& { return wy_; }

auto Ppu::getBgp() -> IRegisterAdapter& { return bgp_; }

auto Ppu::getObp0() -> IRegisterAdapter& { return obp0_; }

auto Ppu::getObp1() -> IRegisterAdapter& { return obp1_; }

auto Ppu::getBuffer() const -> const GbPixelBuffer& { return buffer_; }
