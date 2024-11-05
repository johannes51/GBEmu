#include "apu.h"

#include "util/helpers.h"

Apu::Apu(IMixerUP&& mixer, const std::array<ChannelSP, 4U>& channels, IRegisterAdapterSP divApu)
    : mixer_(std::move(mixer))
    , channels_(channels)
    , divApu_(std::move(divApu))
    , currentSample_({ 0., 0. })
{
  if (!mixer_) {
    throw std::invalid_argument("Mixer not set.");
  }
  if (!divApu_) {
    throw std::invalid_argument("Register not set.");
  }
  for (auto& ch : channels_) {
    if (!ch) {
      throw std::invalid_argument("Channel not set.");
    }
  };
  fs_.isTick(divApu_->get());
}

void Apu::clock()
{
  if (fs_.isTick(divApu_->get())) {
    const auto seq = fs_.get();
    for (auto& ch : channels_) {
      ch->tickApuDiv(seq);
    };
  }
  for (auto& ch : channels_) {
    ch->clock();
  };
  currentSample_ = mixer_->mix(
      channels_[0]->getSample(), channels_[1]->getSample(), channels_[2]->getSample(), channels_[3]->getSample(), 0.);
}

auto Apu::currentSample() -> const std::pair<double, double>& { return currentSample_; }
