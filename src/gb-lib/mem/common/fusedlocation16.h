#ifndef FUSEDLOCATION16_H
#define FUSEDLOCATION16_H

#include "../ilocation16.h"

#include "../ilocation8.h"

class FusedLocation16 final : public ILocation16 {
public:
  explicit FusedLocation16(ILocation8* lower, ILocation8* upper);

  const uint16_t& get() const override;
  FusedLocation16& operator=(const uint16_t& rhs) override;

  bool hasLower() const;
  bool hasUpper() const;
  uint8_t lower() const;
  uint8_t upper() const;
  void setLower(ILocation8* value);
  void setUpper(ILocation8* value);

  static FusedLocation16 construct(ILocation8* lower, ILocation8* upper);

private:
  void reloadBuffer();

  ILocation8* lower_;
  ILocation8* upper_;
  uint16_t buffer_;
};

#endif // FUSEDLOCATION16_H
