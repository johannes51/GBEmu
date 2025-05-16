#ifndef FUSEDLOCATION16_H
#define FUSEDLOCATION16_H

#include "../wordlocationadapter.h"

#include "../location8.h"

class FusedLocation16 final : public WordLocationAdapter {
public:
  explicit FusedLocation16(std::unique_ptr<Location8> lower, std::unique_ptr<Location8> upper);

  const uint16_t& get() const override;
  void set(const uint16_t& value) override;

  bool hasLower() const;
  bool hasUpper() const;
  uint8_t lower() const;
  uint8_t upper() const;
  void setLower(std::unique_ptr<Location8>&& value);
  void setUpper(std::unique_ptr<Location8>&& value);

private:
  void reloadBuffer();

  std::unique_ptr<Location8> lower_;
  std::unique_ptr<Location8> upper_;
  uint16_t buffer_;
};

#endif // FUSEDLOCATION16_H
