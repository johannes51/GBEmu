#ifndef DAC_H
#define DAC_H

#include <cstdint>

class DAC {
public:
  DAC();

  const double& getSample() const;

  void set(uint8_t digValue);

private:
  double sample_ = 0.;
};

#endif // DAC_H
