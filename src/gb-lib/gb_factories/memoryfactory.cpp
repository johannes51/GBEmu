#include "memoryfactory.h"

#include <algorithm>

#include "cartloader.h"
#include "mem/common/memorymanifold.h"
#include "mem/common/mirrorbank.h"
#include "mem/ram/rambank.h"
#include "mem/registers/iobank.h"
#include "mem/registers/singleregisterbank.h"
#include "mem/rest/nullbank.h"

gb::MemoryFactory::MemoryFactory(CartLoaderUP romLoader, std::vector<uint8_t>& buffer)
    : loader_(std::move(romLoader))
    , buffer_(buffer)
    , ptr_(buffer_.begin())
    , mem_(constructMemoryLayout())
{
}

auto gb::MemoryFactory::getIoBank() -> IoBank* { return ioBank_; }

auto gb::MemoryFactory::getIeBank() -> SingleRegisterBank* { return ieBank_; }

auto gb::MemoryFactory::releaseMemory() -> IMemoryViewUP { return std::move(mem_); }

auto gb::MemoryFactory::constructMemoryLayout() -> IMemoryViewUP
{
  auto manifold = std::make_unique<MemoryManifold>();

  for (const auto& bankManager : buildCartBanks()) {
    manifold->addSubManager(bankManager);
  }

  manifold->addSubManager(buildRamBank(VRAM));
  auto wram0 = buildRamBank(WRAM0);
  auto wram1 = buildRamBank(WRAM1);
  manifold->addSubManager(wram0);
  manifold->addSubManager(wram1);
  manifold->addSubManager(std::make_shared<MirrorBank>(MIRROR_L, WRAM0, std::move(wram0)));
  manifold->addSubManager(std::make_shared<MirrorBank>(MIRROR_U, WRAM1, std::move(wram1)));
  manifold->addSubManager(buildRamBank(OAM));
  manifold->addSubManager(std::make_shared<NullBank>(NOT_USED));
  auto ioBankSP = buildIoBank(IO);
  ioBank_ = ioBankSP.get();
  manifold->addSubManager(std::move(ioBankSP));
  manifold->addSubManager(buildRamBank(HRAM));
  auto ieBankSP = std::make_shared<SingleRegisterBank>(IE);
  ieBank_ = ieBankSP.get();
  manifold->addSubManager(std::move(ieBankSP));

  return manifold;
}

auto gb::MemoryFactory::buildRamBank(MemoryArea area) -> IMemoryManagerSP
{
  auto result = std::make_shared<RamBank>(area, std::span(ptr_, area.size()));
  std::advance(ptr_, area.size());
  return result;
}

auto gb::MemoryFactory::buildIoBank(MemoryArea area) -> std::shared_ptr<IoBank>
{
  auto result = std::make_shared<IoBank>(area, std::span(ptr_, area.size()));
  std::advance(ptr_, area.size());
  return result;
}

auto gb::MemoryFactory::buildCartBanks() -> std::vector<IMemoryManagerSP>
{
  const auto cartSize = loader_->calculateNeccessarySize();
  const auto fullSize = cartSize + VRAM.size() + WRAM0.size() + WRAM1.size() + OAM.size() + IO.size() + HRAM.size();
  buffer_.resize(fullSize);
  ptr_ = buffer_.begin();
  std::vector<IMemoryManagerSP> result {};
  if (loader_) {
    result = loader_->constructBanks(std::span { buffer_ }.subspan(0, cartSize));
    std::advance(ptr_, cartSize);
  }
  return result;
}
