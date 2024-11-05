#ifndef DAC_H
#define DAC_H

#include <cstdint>

class DAC {
public:
  DAC() = default;

  const double& getSample() const;

  void set(uint8_t digValue);

private:
  static constexpr double DigitalHalfScale = 7.5;

  double sample_ = 0.;
};

#endif // DAC_H
