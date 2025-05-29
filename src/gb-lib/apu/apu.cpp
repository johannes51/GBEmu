#include "apu.h"

#include "util/helpers.h"

Apu::Apu()
    : mixer_()
    , channels_()
    , divApu_()
    , currentSample_({ 0., 0. })
{
  fs_.isTick(divApu_.getByte());
}

void Apu::clock()
{
  if (!mixer_) {
    throw std::invalid_argument("Mixer not set.");
  }
  if (fs_.isTick(divApu_.getByte())) {
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

auto Apu::getDivApu() -> IRegisterAdapter& { return divApu_; }

auto Apu::getNr52() -> IRegisterAdapter& { return nr52_; }

void Apu::addChannel(ChannelUP channel)
{
  for (auto& channelElem : channels_) {
    if (!channelElem) {
      channelElem = std::move(channel);
      break;
    }
  }
  if (channel) {
    throw std::logic_error("Tried to add more than 4 channels.");
  }
}

void Apu::setMixer(IMixerUP mixer) { mixer_ = std::move(mixer); }
