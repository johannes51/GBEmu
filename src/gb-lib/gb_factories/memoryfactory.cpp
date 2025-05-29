#include "memoryfactory.h"

#include <algorithm>

#include "cartloader.h"
#include "mem/common/mirrorbank.h"
#include "mem/gbmemorymap.h"
#include "mem/ram/rambank.h"
#include "mem/rest/singleregisterbank.h"
#include "mem/rest/zerobank.h"

gb::MemoryFactory::MemoryFactory(
    IMemoryView& cartBanks, IoBankUP ioBank, std::span<uint8_t, std::dynamic_extent> buffer)
    : buffer_(buffer)
    , ptr_(buffer_.begin())
    , cartBanks_(cartBanks)
    , ioBank_(std::move(ioBank))
    , mem_(constructMemoryLayout())
{
}

auto gb::MemoryFactory::releaseVram() -> IMemoryViewUP { return std::move(vram_); }

auto gb::MemoryFactory::releaseOam() -> IMemoryViewUP { return std::move(oam_); }

auto gb::MemoryFactory::releaseMemory() -> IMemoryWordViewUP { return std::move(mem_); }

auto gb::MemoryFactory::getSize() -> size_t { return VRAM.size() + WRAM.size() + OAM.size() + IO.size() + HRAM.size(); }

auto gb::MemoryFactory::constructMemoryLayout() -> IMemoryWordViewUP
{
  vram_ = buildRamBank(VRAM);
  oam_ = buildRamBank(OAM);

  auto notUsed = std::make_unique<ZeroBank>(NOT_USED);

  auto wram = buildRamBank(WRAM);
  auto mirror = std::make_unique<MirrorBank>(MIRROR, WRAM, *wram);

  auto hram = buildRamBank(HRAM);

  auto ie = std::make_unique<SingleRegisterBank>(IE);

  return std::make_unique<GbMemoryMap>(cartBanks_, cartBanks_, *vram_, cartBanks_, std::move(wram), std::move(mirror),
      *oam_, std::move(notUsed), std::move(ioBank_), std::move(hram), std::move(ie));
}

auto gb::MemoryFactory::buildRamBank(MemoryArea area) -> IMemoryViewUP
{
  auto result = std::make_unique<RamBank>(area, std::span(ptr_, area.size()));
  std::advance(ptr_, area.size());
  return result;
}
