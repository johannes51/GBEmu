#include "gbmemorymap.h"

GbMemoryMap::GbMemoryMap(IMemoryView& rom0, IMemoryView& rom1, IMemoryView& vram, IMemoryView& extRam,
    IMemoryViewUP wram, IMemoryViewUP echoRam, IMemoryView& oam, IMemoryViewUP notUsed, IMemoryViewUP ioBank,
    IMemoryViewUP hram, IMemoryViewUP ie)
    : rom0_(rom0)
    , rom1_(rom1)
    , vram_(vram)
    , extRam_(extRam)
    , wram_(std::move(wram))
    , echoRam_(std::move(echoRam))
    , oam_(oam)
    , notUsed_(std::move(notUsed))
    , ioBank_(std::move(ioBank))
    , hram_(std::move(hram))
    , ie_(std::move(ie))
    , wordLoc_(*this, 0U)
{
}

auto GbMemoryMap::getLocation8(const address_type address) -> ILocation8&
{
  if (address <= Rom0Area.to) {
    return rom0_.getLocation8(address);
  } else if (address <= Rom1Area.to) {
    return rom1_.getLocation8(address);
  } else if (address <= VramArea.to) {
    return vram_.getLocation8(address);
  } else if (address <= ExtRamArea.to) {
    return extRam_.getLocation8(address);
  } else if (address <= Wram1Area.to) {
    return wram_->getLocation8(address);
  } else if (address <= MirrorUArea.to) {
    return echoRam_->getLocation8(address);
  } else if (address <= OamArea.to) {
    return oam_.getLocation8(address);
  } else if (address <= NotUsedArea.to) {
    return notUsed_->getLocation8(address);
  } else if (address <= IoArea.to) {
    return ioBank_->getLocation8(address);
  } else if (address <= HramArea.to) {
    return hram_->getLocation8(address);
  } else { // NOTE: address MUST be 0xFFFFU then!
    return ie_->getLocation8(IeAddress);
  }
}

auto GbMemoryMap::getLocation16(const address_type address) -> ILocation16&
{
  wordLoc_.setAddress(address);
  return wordLoc_;
}
