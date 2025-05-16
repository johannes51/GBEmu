#ifndef OAM_H
#define OAM_H

#include <memory>
#include <vector>

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "object.h"

constexpr uint8_t NUM_OBJECTS = 40;

class Oam {
public:
  explicit Oam(IMemoryView& mem);
  virtual ~Oam() = default;

  virtual std::vector<Object> getAll();

private:
  static constexpr address_type OAM_BASE = 0xFE00;
  static constexpr address_type OAM_TOP = 0xFE9F;

  IMemoryView& mem_;
};

using OamUP = std::unique_ptr<Oam>;

#endif // OAM_H
