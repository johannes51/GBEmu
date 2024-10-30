#include "apu.h"

Apu::Apu(IMixerUP&& mixer)
    : mixer_(std::move(mixer))
{
}

void Apu::clock() { }
