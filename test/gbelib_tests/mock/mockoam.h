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

  std::vector<Object> getAll() override { return {}; }
};

#endif // MOCKTILEMAP_H
