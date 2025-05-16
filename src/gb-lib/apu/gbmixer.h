#ifndef GBMIXER_H
#define GBMIXER_H

#include "imixer.h"

#include "mem/registers/iregisteradapter.h"

class GbMixer : public IMixer {
public:
  GbMixer(const IRegisterAdapter& nr50, const IRegisterAdapter& nr51);

  std::pair<double, double> mix(
      double channel1, double channel2, double channel3, double channel4, double vin) override;

private:
  static constexpr uint8_t channel1Right = 0U;
  static constexpr uint8_t channel1Left = 4U;
  static constexpr uint8_t channel2Right = 1U;
  static constexpr uint8_t channel2Left = 5U;
  static constexpr uint8_t channel3Right = 2U;
  static constexpr uint8_t channel3Left = 6U;
  static constexpr uint8_t channel4Right = 3U;
  static constexpr uint8_t channel4Left = 7U;

  static constexpr uint8_t vinRight = 3U;
  static constexpr uint8_t vinLeft = 7U;

  const IRegisterAdapter& nr50_;
  const IRegisterAdapter& nr51_;
};

#endif // GBMIXER_H
