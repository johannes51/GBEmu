#include "gbmixer.h"

#include "util/helpers.h"

GbMixer::GbMixer(IoBank& io)
{
  io.registerRegister(Nr50Address + 0U, &nr50_);
  io.registerRegister(Nr50Address + 1U, &nr51_);
}

auto GbMixer::mix(
    double channel1, double channel2, double channel3, double channel4, double vin) -> std::pair<double, double>
{
  auto result = std::pair<double, double> { 0., 0. };
  if (nr51_.testBit(channel1Right)) {
    result.first += channel1;
  }
  if (nr51_.testBit(channel2Right)) {
    result.first += channel2;
  }
  if (nr51_.testBit(channel3Right)) {
    result.first += channel3;
  }
  if (nr51_.testBit(channel4Right)) {
    result.first += channel4;
  }
  if (nr51_.testBit(channel1Left)) {
    result.second += channel1;
  }
  if (nr51_.testBit(channel2Left)) {
    result.second += channel2;
  }
  if (nr51_.testBit(channel3Left)) {
    result.second += channel3;
  }
  if (nr51_.testBit(channel4Left)) {
    result.second += channel4;
  }

  if (nr50_.testBit(vinRight)) {
    result.first += vin;
  }
  if (nr50_.testBit(vinLeft)) {
    result.second += vin;
  }

  result.first *= hlp::getBits(nr50_.getByte(), 0U, 3U);
  result.second *= hlp::getBits(nr50_.getByte(), 4U, 3U);

  return result;
}
