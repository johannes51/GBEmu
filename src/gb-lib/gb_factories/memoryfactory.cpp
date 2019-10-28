#include "memoryfactory.h"

#include <algorithm>

#include "cartloader.h"
#include "mem/memorymanifold.h"
#include "mem/mirrorbank.h"
#include "mem/nullbank.h"
#include "mem/rambank.h"

gb::MemoryFactory::MemoryFactory(RomLoaderUP&& romLoader)
    : loader_(std::move(romLoader))
{
}

IMemoryViewSP gb::MemoryFactory::constructMemoryLayout()
{
  auto manifold = std::make_shared<MemoryManifold>();

  for (const auto& bankManager : buildCartBanks()) {
    manifold->addSubManager(bankManager);
  }

  auto wram0 = buildRamBank(WRAM0);
  auto wram1 = buildRamBank(WRAM1);
  manifold->addSubManager(wram0);
  manifold->addSubManager(wram1);
  manifold->addSubManager(buildMirrorBank(MIRROR_L, WRAM0, wram0));
  manifold->addSubManager(buildMirrorBank(MIRROR_U, WRAM1, wram1));
  manifold->addSubManager(buildNullBank(NOT_USED));
  manifold->addSubManager(buildRamBank(HRAM));

  return manifold;
}

IMemoryManagerSP gb::MemoryFactory::buildRamBank(MemoryArea area) { return std::make_shared<RamBank>(area); }

IMemoryManagerSP gb::MemoryFactory::buildMirrorBank(
    MemoryArea mirrorArea, MemoryArea originArea, IMemoryManagerSP origin)
{
  return std::make_shared<MirrorBank>(mirrorArea, originArea, std::move(origin));
}

IMemoryManagerSP gb::MemoryFactory::buildNullBank(MemoryArea area) { return std::make_shared<NullBank>(area); }

std::vector<IMemoryManagerSP> gb::MemoryFactory::buildCartBanks()
{
  std::vector<IMemoryManagerSP> result {};
  if (loader_) {
    result = loader_->constructBanks();
  }
  return result;
}
