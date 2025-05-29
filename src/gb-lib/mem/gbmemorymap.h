#ifndef GBMEMORYMAP_H
#define GBMEMORYMAP_H

#include "imemorywordview.h"

#include "common/bytewriterlocation16.h"
#include "mem_defines.h"

class GbMemoryMap : public IMemoryWordView {
public:
  explicit GbMemoryMap(IMemoryView& rom0, IMemoryView& rom1, IMemoryView& vram, IMemoryView& extRam, IMemoryViewUP wram,
      IMemoryViewUP echoRam, IMemoryView& oam, IMemoryViewUP notUsed, IMemoryViewUP ioBank, IMemoryViewUP hram,
      IMemoryViewUP ie);

  ILocation8& getLocation8(const address_type address) override;
  ILocation16& getLocation16(const address_type address) override;

private:
  IMemoryView& rom0_;
  IMemoryView& rom1_;
  IMemoryView& vram_;
  IMemoryView& extRam_;
  IMemoryViewUP wram_;
  IMemoryViewUP echoRam_;
  IMemoryView& oam_;
  IMemoryViewUP notUsed_;
  IMemoryViewUP ioBank_;
  IMemoryViewUP hram_;
  IMemoryViewUP ie_;

  ByteWriterLocation16 wordLoc_;
};

#endif // GBMEMORYMAP_H
