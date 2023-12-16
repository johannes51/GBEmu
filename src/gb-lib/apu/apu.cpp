#include "apu.h"

Apu::Apu(IMixerSP&& mixer)
    : mixer_(std::move(mixer))
{
}

void Apu::clock() { }
