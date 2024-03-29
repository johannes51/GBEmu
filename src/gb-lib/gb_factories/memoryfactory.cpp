#include "memoryfactory.h"

#include <algorithm>

#include "cartloader.h"
#include "mem/memorymanifold.h"
#include "mem/mirrorbank.h"
#include "mem/nullbank.h"
#include "mem/rambank.h"
#include "mem/registerbank.h"

gb::MemoryFactory::MemoryFactory(RomLoaderUP&& romLoader)
    : loader_(std::move(romLoader))
    , ioBank_()
{
}

auto gb::MemoryFactory::constructMemoryLayout() -> IMemoryViewSP
{
  auto manifold = std::make_shared<MemoryManifold>();

  for (const auto& bankManager : buildCartBanks()) {
    manifold->addSubManager(bankManager);
  }

  manifold->addSubManager(buildRamBank(VRAM));
  auto wram0 = buildRamBank(WRAM0);
  auto wram1 = buildRamBank(WRAM1);
  manifold->addSubManager(wram0);
  manifold->addSubManager(wram1);
  manifold->addSubManager(buildMirrorBank(MIRROR_L, WRAM0, wram0));
  manifold->addSubManager(buildMirrorBank(MIRROR_U, WRAM1, wram1));
  manifold->addSubManager(buildRamBank(OAM));
  manifold->addSubManager(buildNullBank(NOT_USED));
  manifold->addSubManager(buildRamBank(HRAM));
  manifold->addSubManager(buildIe());

  auto ioManager = std::make_shared<RamBank>(IO);
  manifold->addSubManager(ioManager); // TODO: This is just a fake-out, actually implement!
  ioBank_ = ioManager;

  return manifold;
}

auto gb::MemoryFactory::buildRamBank(MemoryArea area) -> IMemoryManagerSP { return std::make_shared<RamBank>(area); }

auto gb::MemoryFactory::buildMirrorBank(MemoryArea mirrorArea, MemoryArea originArea, IMemoryManagerSP origin)
    -> IMemoryManagerSP
{
  return std::make_shared<MirrorBank>(mirrorArea, originArea, std::move(origin));
}

auto gb::MemoryFactory::buildNullBank(MemoryArea area) -> IMemoryManagerSP { return std::make_shared<NullBank>(area); }

auto gb::MemoryFactory::buildCartBanks() -> std::vector<IMemoryManagerSP>
{
  std::vector<IMemoryManagerSP> result {};
  if (loader_) {
    result = loader_->constructBanks();
  }
  return result;
}

auto gb::MemoryFactory::buildIe() -> IMemoryManagerSP { return std::make_shared<RegisterBank>(IE); }
