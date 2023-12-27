#ifndef OAM_H
#define OAM_H

#include <memory>

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "object.h"

constexpr uint8_t NUM_OBJECTS = 40;

class Oam {
public:
  explicit Oam(IMemoryViewSP mem);
  virtual ~Oam() = default;

  virtual std::array<Object, NUM_OBJECTS> getAll();

private:
  static constexpr address_type OAM_BASE = 0xFE00;
  static constexpr address_type OAM_TOP = 0xFE9F;

  IMemoryViewSP mem_;
};

using OamUP = std::unique_ptr<Oam>;

#endif // OAM_H
