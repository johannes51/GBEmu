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
  if (nr51_->testBit(0U)) {
    result.first += channel1;
  }
  if (nr51_->testBit(1U)) {
    result.first += channel2;
  }
  if (nr51_->testBit(2U)) {
    result.first += channel3;
  }
  if (nr51_->testBit(3U)) {
    result.first += channel4;
  }
  if (nr51_->testBit(4U)) {
    result.second += channel1;
  }
  if (nr51_->testBit(5U)) {
    result.second += channel2;
  }
  if (nr51_->testBit(6U)) {
    result.second += channel3;
  }
  if (nr51_->testBit(7U)) {
    result.second += channel4;
  }

  if (nr50_->testBit(3U)) {
    result.first += vin;
  }
  if (nr50_->testBit(7U)) {
    result.second += vin;
  }

  result.first *= hlp::getBits(nr50_->get(), 0U, 3U);
  result.second *= hlp::getBits(nr50_->get(), 4U, 3U);

  return result;
}
