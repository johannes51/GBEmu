#ifndef MEM_DEFINES_H
#define MEM_DEFINES_H

#include <cstdint>

using address_type = uint16_t;
using size_t = std::size_t;

struct MemoryArea {
  constexpr size_t size() const { return (to - from) + 1U; }

  address_type from;
  address_type to;
};

inline bool operator<(const MemoryArea& lhs, const MemoryArea& rhs) { return lhs.from < rhs.from; }
inline bool operator==(const MemoryArea& lhs, const MemoryArea& rhs)
{
  return lhs.from == rhs.from && lhs.to == rhs.to;
}

constexpr size_t MemSize = 0x10000U;

constexpr MemoryArea Rom0Area { .from = 0x0000U, .to = 0x3FFFU };
constexpr MemoryArea Rom1Area = { .from = 0x4000U, .to = 0x7FFFU };
constexpr MemoryArea VramArea = { .from = 0x8000U, .to = 0x9FFFU };
constexpr MemoryArea ExtRamArea = { .from = 0xA000U, .to = 0xBFFFU };
constexpr MemoryArea Wram0Area = { .from = 0xC000U, .to = 0xCFFFU };
constexpr MemoryArea Wram1Area = { .from = 0xD000U, .to = 0xDFFFU };
constexpr MemoryArea MirrorLArea = { .from = 0xE000U, .to = 0xEFFFU };
constexpr MemoryArea MirrorUArea = { .from = 0xF000U, .to = 0xFDFFU };
constexpr MemoryArea OamArea = { .from = 0xFE00U, .to = 0xFE9FU };
constexpr MemoryArea NotUsedArea = { .from = 0xFEA0U, .to = 0xFEFFU };
constexpr MemoryArea IoArea = { .from = 0xFF00U, .to = 0xFF7FU };
constexpr MemoryArea HramArea = { .from = 0xFF80U, .to = 0xFFFEU };
constexpr address_type IeAddress = 0xFFFFU;

#endif // MEM_DEFINES_H
