#ifndef FUSEDLOCATION16_H
#define FUSEDLOCATION16_H

#include "location16.h"

#include "location8.h"

class FusedLocation16 : public Location16 {
public:
  explicit FusedLocation16(Location8UP lower, Location8UP upper);

  uint16_t get() const;
  FusedLocation16& operator=(const uint16_t& rhs);

  bool hasLower() const;
  bool hasUpper() const;
  uint8_t lower() const;
  uint8_t upper() const;
  void setLower(Location8UP value);
  void setUpper(Location8UP value);

private:
  Location8UP lower_;
  Location8UP upper_;
};

#endif // FUSEDLOCATION16_H
