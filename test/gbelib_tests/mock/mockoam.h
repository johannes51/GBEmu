#ifndef MOCKTILEMAP_H
#define MOCKTILEMAP_H

#include "ppu/layer/oam.h"

class MockOam : public Oam {
public:
  MockOam()
      : Oam(nullptr)
  {
  }
  ~MockOam() override = default;

  std::array<Object, 40> getAll() override { return { 0 }; }
};

#endif // MOCKTILEMAP_H
