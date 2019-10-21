#ifndef LOCATIONIMPL_H
#define LOCATIONIMPL_H

#include <stdint.h>

#include "location_defines.h"

class LocationImpl {
public:
  uint8_t getByte() const;
  uint16_t getWord() const;

  void setByte(uint8_t value);
  void setWord(uint16_t value);

protected:
  LocationImpl(LocationByteUP lower, LocationByteUP upper);

private:
  static constexpr uint8_t BYTE_SIZE = 8;
  static constexpr uint8_t LOWER_MASK = 0xFFu;
  static constexpr uint16_t UPPER_MASK = 0xFF00u;

  LocationByteUP lower_;
  LocationByteUP upper_;
};

#endif // LOCATIONIMPL_H
