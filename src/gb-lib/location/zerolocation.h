#ifndef ZEROLOCATION_H
#define ZEROLOCATION_H

#include "location.h"

class ZeroLocation final : public Location {
public:
  ZeroLocation()
      : Location(Type::Both)
  {
  }
  DISABLE_COPY_AND_MOVE(ZeroLocation)

  const uint8_t& getByte() const override;
  const uint16_t& getWord() const override;
  Location& operator=(const uint8_t& rhs) override;
  Location& operator=(const uint16_t& rhs) override;

private:
  static std::array<uint8_t, 2> zero_;
};

#endif // ZEROLOCATION_H
