#include "gbmixer.h"

#include "util/helpers.h"

GbMixer::GbMixer(IRegisterAdapterSP nr50, IRegisterAdapterSP nr51)
    : nr50_(std::move(nr50))
    , nr51_(std::move(nr51))
{
  if (!nr51_) {
    throw std::invalid_argument("Audio registers not set.");
  }
}

auto GbMixer::mix(
    double channel1, double channel2, double channel3, double channel4, double vin) -> std::pair<double, double>
{
  auto result = std::pair<double, double> { 0., 0. };
  if (nr51_->testBit(channel1Right)) {
    result.first += channel1;
  }
  if (nr51_->testBit(channel2Right)) {
    result.first += channel2;
  }
  if (nr51_->testBit(channel3Right)) {
    result.first += channel3;
  }
  if (nr51_->testBit(channel4Right)) {
    result.first += channel4;
  }
  if (nr51_->testBit(channel1Left)) {
    result.second += channel1;
  }
  if (nr51_->testBit(channel2Left)) {
    result.second += channel2;
  }
  if (nr51_->testBit(channel3Left)) {
    result.second += channel3;
  }
  if (nr51_->testBit(channel4Left)) {
    result.second += channel4;
  }

  if (nr50_->testBit(vinRight)) {
    result.first += vin;
  }
  if (nr50_->testBit(vinLeft)) {
    result.second += vin;
  }

  result.first *= hlp::getBits(nr50_->get(), 0U, 3U);
  result.second *= hlp::getBits(nr50_->get(), 4U, 3U);

  return result;
}
