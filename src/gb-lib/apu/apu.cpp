#include "apu.h"

#include "util/helpers.h"

Apu::Apu(IMixerUP mixer, const std::array<ChannelSP, 4U>& channels,
    std::unordered_map<ApuRegisters, IRegisterAdapterUP>&& registers, IRegisterAdapterUP divApu)
    : mixer_(std::move(mixer))
    , channels_(channels)
    , registers_(std::move(registers))
    , divApu_(std::move(divApu))
    , currentSample_({ 0., 0. })
{
  if (!divApu_) {
    throw std::invalid_argument("DIV-APU not provided.");
  }
  if (!mixer_) {
    throw std::invalid_argument("Mixer not set.");
  }
  for (auto& ch : channels_) {
    if (!ch) {
      throw std::invalid_argument("Channel not set.");
    }
  };
  fs_.isTick(divApu_->getByte());
}

void Apu::clock()
{
  if (fs_.isTick(divApu_->getByte())) {
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
