#include "apu.h"

Apu::Apu(std::vector<IChannelSP>&& channels, IMixerSP&& mixer)
    : channels_(std::move(channels))
    , mixer_(std::move(mixer))
{
}

void Apu::clock() { }