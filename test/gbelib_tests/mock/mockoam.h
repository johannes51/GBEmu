#ifndef MOCKOAM_H
#define MOCKOAM_H

#include "ppu/layer/oam.h"

class MockOam : public Oam {
public:
  explicit MockOam(std::vector<Object> objects = {})
      : Oam(nullptr)
      , objects_(std::move(objects))
  {
  }
  ~MockOam() override = default;

  std::vector<Object> getAll() override { return objects_; }

private:
  std::vector<Object> objects_;
};

#endif // MOCKOAM_H
