#include "apu.h"

Apu::Apu(std::vector<IChannelUP>&& channels, IMixerUP&& mixer)
    : channels_(std::move(channels))
    , mixer_(std::move(mixer))
{
}

void Apu::clock() { }
